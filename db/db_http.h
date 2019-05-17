#ifndef _DB_HTTP_H_
#define _DB_HTTP_H_

#include "dap_enc_ks.h"
#include "dap_enc_key.h"

int db_http_init(void);
void db_http_deinit(void);
void db_http_add_proc(struct dap_http * sh, const char * url);
#endif
