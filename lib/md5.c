#include "md5.h"

/* Creates a new GChecksum in ctx */
void md5_init(struct MD5Context *ctx)
{
	ctx->gchecksum = g_checksum_new(G_CHECKSUM_MD5);
}

/* Wrapper for g_checksum_update */
void md5_append(struct MD5Context *ctx, const md5_byte_t *buf, unsigned int len)
{
	g_checksum_update(ctx->gchecksum, buf, len);
}

/* Wrapper for g_checksum_get_digest
 * Also takes care of g_checksum_free(), since it can't be reused anyway
 * (the GChecksum is closed after get_digest) */
void md5_finish(struct MD5Context *ctx, md5_byte_t digest[16])
{
	gsize digest_len = 16;
	g_checksum_get_digest(ctx->gchecksum, digest, &digest_len);
	g_checksum_free(ctx->gchecksum);
}

/* Variant of md5_finish that copies the GChecksum
 * before it enters the "closed" state */
void md5_digest_keep(struct MD5Context *ctx, md5_byte_t digest[16])
{
	GChecksum *copy = g_checksum_copy(ctx->gchecksum);
	md5_finish(ctx, digest);
	ctx->gchecksum = copy;
}
