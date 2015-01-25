#ifndef _MD5_H
#define _MD5_H

#include <glib.h>
#include <gmodule.h>

typedef guchar md5_byte_t;
typedef struct MD5Context {
	GChecksum *gchecksum;
} md5_state_t;

G_MODULE_EXPORT void md5_init(struct MD5Context *context);
G_MODULE_EXPORT void md5_append(struct MD5Context *context, const md5_byte_t *buf, unsigned int len);
G_MODULE_EXPORT void md5_finish(struct MD5Context *context, md5_byte_t digest[16]);
G_MODULE_EXPORT void md5_digest_keep(struct MD5Context *context, md5_byte_t digest[16]);

#endif
