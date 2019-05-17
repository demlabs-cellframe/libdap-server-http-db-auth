#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utlist.h"

#include "dap_common.h"

#include "dap_client_remote.h"
#include "dap_http_client.h"
#include "dap_http_simple.h"

#include "db_http.h"

#include "../auth/db_auth.h"
#include "http_status_code.h"

#include "dap_enc_http.h"

#define LOG_TAG "db_http"

#define LAST_USE_KEY(key) ((rsa_key_t*)key->internal)->last_time_use_key

void db_http_proc(dap_http_simple_t * cl_st, void * arg );

int db_http_init()
{
    log_it(L_NOTICE, "Init content manager");
    return 0;
}

void db_http_deinit()
{
    log_it(L_NOTICE, "Deinit content manager");
}


void db_http_add_proc(struct dap_http * sh, const char * url)
{
    dap_http_simple_proc_add(sh,url,1000000,db_http_proc);
}

/**
 * @brief content_proc Process content list request
 * @param sh HTTP simple client instance
 * @param arg Return if ok
 */
void db_http_proc(dap_http_simple_t * cl_st, void * arg )
{
    http_status_code_t * return_code = (http_status_code_t*)arg;
    enc_http_delegate_t * dg;
    strcpy(cl_st->reply_mime,"application/octet-stream");

    dg=enc_http_request_decode(cl_st);
    if(dg){
        if(strcmp(dg->url_path,"auth")==0){
            db_auth_http_proc(dg, arg);
        } else {

            if(dg->url_path)
                log_it(L_ERROR,"Wrong DB request %s",dg->url_path);
            else
                log_it(L_ERROR,"Wrong DB request: nothing after / ");

            *return_code = Http_Status_BadRequest;
        }

        enc_http_reply_encode(cl_st,dg);
        enc_http_delegate_delete(dg);
    }else{
        *return_code = Http_Status_Unauthorized;
        log_it(L_WARNING,"No KeyID in the request");
    }
}

