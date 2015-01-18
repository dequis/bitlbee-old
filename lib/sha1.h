
#ifndef _SHA1_H_
#define _SHA1_H_

#include <glib.h>
#include <gmodule.h>

#define sha1_hash_size 20

typedef struct SHA1Context {
	GChecksum *gchecksum;
} sha1_state_t;

G_MODULE_EXPORT void sha1_init(sha1_state_t *);
G_MODULE_EXPORT void sha1_append(sha1_state_t *, const guint8 *, unsigned int);
G_MODULE_EXPORT void sha1_finish(sha1_state_t *, guint8 digest[sha1_hash_size]);
G_MODULE_EXPORT void sha1_hmac(const char *key_, size_t key_len, const char *payload, size_t payload_len, guint8 digest[sha1_hash_size]);
G_MODULE_EXPORT char *sha1_random_uuid( sha1_state_t * context );

#endif
