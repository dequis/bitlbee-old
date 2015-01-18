#include "sha1.h"
#include <string.h>
#include <stdio.h>


void sha1_init(sha1_state_t *ctx)
{
	ctx->gchecksum = g_checksum_new(G_CHECKSUM_SHA1);
}

void sha1_append(sha1_state_t *ctx, const guint8 * message_array, guint len)
{
	g_checksum_update(ctx->gchecksum, message_array, len);
}

void sha1_finish(sha1_state_t *ctx, guint8 digest[sha1_hash_size])
{
	gsize digest_len = sha1_hash_size;
	g_checksum_get_digest(ctx->gchecksum, digest, &digest_len);
	g_checksum_free(ctx->gchecksum);
}

#define HMAC_BLOCK_SIZE 64

/* BitlBee addition: */
void sha1_hmac(const char *key_, size_t key_len, const char *payload, size_t payload_len, guint8 digest[sha1_hash_size])
{
	sha1_state_t sha1;
	guint8 hash[sha1_hash_size];
	guint8 key[HMAC_BLOCK_SIZE+1];
	int i;
	
	if( key_len == 0 )
		key_len = strlen( key_ );
	if( payload_len == 0 )
		payload_len = strlen( payload );
	
	/* Create K. If our current key is >64 chars we have to hash it,
	   otherwise just pad. */
	memset( key, 0, HMAC_BLOCK_SIZE + 1 );
	if( key_len > HMAC_BLOCK_SIZE )
	{
		sha1_init( &sha1 );
		sha1_append( &sha1, (guint8*) key_, key_len );
		sha1_finish( &sha1, key );
	}
	else
	{
		memcpy( key, key_, key_len );
	}
	
	/* Inner part: H(K XOR 0x36, text) */
	sha1_init( &sha1 );
	for( i = 0; i < HMAC_BLOCK_SIZE; i ++ )
		key[i] ^= 0x36;
	sha1_append( &sha1, key, HMAC_BLOCK_SIZE );
	sha1_append( &sha1, (const guint8*) payload, payload_len );
	sha1_finish( &sha1, hash );
	
	/* Final result: H(K XOR 0x5C, inner stuff) */
	sha1_init( &sha1 );
	for( i = 0; i < HMAC_BLOCK_SIZE; i ++ )
		key[i] ^= 0x36 ^ 0x5c;
	sha1_append( &sha1, key, HMAC_BLOCK_SIZE );
	sha1_append( &sha1, hash, sha1_hash_size );
	sha1_finish( &sha1, digest );
}

/* I think this follows the scheme described on:
   http://en.wikipedia.org/wiki/Universally_unique_identifier#Version_4_.28random.29
   My random data comes from a SHA1 generator but hey, it's random enough for
   me, and RFC 4122 looks way more complicated than I need this to be.
   
   Returns a value that must be free()d. */
char *sha1_random_uuid( sha1_state_t * context )
{
	guint8 dig[sha1_hash_size];
	char *ret = g_new0( char, 40 ); /* 36 chars + \0 */
	int i, p;
	
	sha1_finish(context, dig);
	for( p = i = 0; i < 16; i ++ )
	{
		if( i == 4 || i == 6 || i == 8 || i == 10 )
			ret[p++] = '-';
		if( i == 6 )
			dig[i] = ( dig[i] & 0x0f ) | 0x40;
		if( i == 8 )
			dig[i] = ( dig[i] & 0x30 ) | 0x80;
		
		sprintf( ret + p, "%02x", dig[i] );
		p += 2;
	}
	ret[p] = '\0';
	
	return ret;
}
