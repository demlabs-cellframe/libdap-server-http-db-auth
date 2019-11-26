/*
 * Authors:
 * Dmitriy A. Gearasimov <naeper@demlabs.net>
 * CellFrame       https://cellframe.net
 * DeM Labs Inc.   https://demlabs.net
 * Copyright  (c) 2017-2019
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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "dap_client.h"
#include "dap_common.h"
#include "dap_config.h"

#ifdef _WIN32
#include "registry.h"
#endif

#include "dap_defines.h"

#include "db_auth.h"

static void s_help(const char * a_app_name)
{
    printf ("\t%s tool. Usage:\n\n", a_app_name);
    printf("\tGet password hash\n");
    printf("%s password_hash <Password>\n",a_app_name);
    exit(-1);
}

int main(int argc, const char * argv[])
{
#ifdef _WIN32
    dap_sprintf(s_sys_dir_path, "%s/%s", regGetUsrPath(), DAP_APP_NAME);
    l_sys_dir_path_len = strlen(s_sys_dir_path);
#endif

    //    set_default_locale();
    //    command_execution_string = shell_script_filename = (char *) NULL;

    memcpy(s_sys_dir_path + l_sys_dir_path_len, SYSTEM_CONFIGS_DIR, sizeof(SYSTEM_CONFIGS_DIR) );
    dap_common_init( DAP_APP_NAME " Console interface", NULL );
    dap_log_level_set( L_CRITICAL );
    dap_config_init( s_sys_dir_path );
    memset(s_sys_dir_path + l_sys_dir_path_len, '\0', MAX_PATH - l_sys_dir_path_len);

    if((g_config = dap_config_open(DAP_APP_NAME)) == NULL) {
        printf("Can't init general configurations " DAP_APP_NAME ".cfg\n");
        exit(-1);
    }

    if (argc<2 ){
        fprintf(stderr, "Have only %d params but need 2 at least.", argc);
        s_help(argv[0]);
    }

    if ( strcmp(argv[1],"password_hash")==0 ){
        if ( argc < 3){
            fprintf(stderr, "Have only %d params but need 3 at least for command \"password_hash\". Need password string to produce password hash!", argc);
            s_help( argv[0]);
        }
        const char * l_password = argv[2];
        char * l_passwd_hash = dap_server_db_hash_password_b64 ( l_password);
        if( l_passwd_hash){
            printf( "%s",l_passwd_hash);
            DAP_DELETE( l_passwd_hash);
        }else
            fprintf(stderr, "Can't produce hash from \"%s\"",l_password);
    }else{
        fprintf(stderr, "Unknown command \"%s\"", argv[1]);
        s_help( argv[0] );
    }
    return 0;

}

