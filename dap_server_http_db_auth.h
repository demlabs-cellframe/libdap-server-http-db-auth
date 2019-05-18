/*
 * Authors:
 * Dmitriy A. Gearasimov <gerasimov.dmitriy@demlabs.net>
 * Aleksandr Lysikov <alexander.lysikov@demlabs.net>
 * DeM Labs Inc.   https://demlabs.net
 * Kelvin Project https://github.com/kelvinblockchain
 * Copyright  (c) 2019
 * All rights reserved.

 This file is part of DAP (Deus Applications Prototypes) the open source project

 DAP (Deus Applicaions Prototypes) is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 DAP is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with any DAP based project.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

// Parse a_service_key from service client
bool dap_server_http_db_auth_parse_service_key(const char *a_service_key, char **a_addr_base58, char **a_sign_hash);
// Create new service_key
char* dap_server_http_db_auth_create_service_key(const char *a_wallet_name);

// Create new key hash
char* dap_server_http_db_auth_create_key_hash(const char *a_wallet_name, char **a_addr_base58);
// Checking service_key from service client
bool dap_server_http_db_auth_check_key(char *a_addr_base58, const char *a_sign_hash_str);

