/*
 Copyright (c) 2017-2019 (c) Project "DeM Labs Inc" https://github.com/demlabsinc
  All rights reserved.

 This file is part of DAP (Deus Applications Prototypes) the open source project

    DAP (Deus Applicaions Prototypes) is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DAP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with any DAP based project.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <stdint.h>
#include <pthread.h>
#include "uthash.h"

#include "dap_enc_http.h"
#include "dap_http_client.h"
#include "dap_client_remote.h"
#define DB_AUTH_HASH_LENGTH 64

typedef struct db_auth_info{
    char cookie[65];
    char id[27];
    char first_name[1024];
    char last_name[1024];
    char email[1024];
    char user[256];
    char password[1024];
    char pkey[4096];
    time_t auth_date;

    /* pointer on low-level client only for read! */
    const dap_http_client_t * dap_http_client;

    UT_hash_handle hh; // makes this structure hashable with UTHASH library
} db_auth_info_t;




int db_auth_init(const char* db_name);
void db_auth_deinit(void);

void db_auth_set_callbacks(dap_enc_http_callback_t a_callback_success);

db_auth_info_t* db_auth_info_by_cookie(const char * cookie);
db_auth_info_t* db_search_cookie_in_db(const char * cookie);

int db_auth_login(const char* login, const char* password,
                              const char* domain, db_auth_info_t** ai);

db_auth_info_t * db_auth_register(const char *user,const char *password,
                                         const char *domain, const char * first_name,
                                         const char* last_name, const char * email,
                                         const char * device_type, const char *app_version,
                                         const char *hostaddr, const char *sys_uuid);

db_auth_info_t * db_auth_register_channel(const char* name_channel, const char* domain,
                                                 const char* password);
bool exist_user_in_db(const char* user);
bool db_auth_user_change_password(const char* user, const char* password,
                                  const char* new_password);

bool db_auth_change_password(const char *user, const char* new_password);

bool check_user_password(const char* user, const char* password);

unsigned char* dap_server_db_hash_password(const char* a_password);
char* dap_server_db_hash_password_b64(const char* a_password);

void db_auth_http_proc(enc_http_delegate_t *dg, void * arg);

void db_auth_traffic_track_callback(dap_server_t *srv);

/// Check user data for correct input.
/// @param before_parsing Line size before parsing.
/// @param after_parsing Line size after parsing.
/// @return Returns true if user data is entered correctly
/// (there are 2 separator spaces), otherwise false.
inline bool check_user_data_for_space(size_t before_parsing, size_t after_parsing);
