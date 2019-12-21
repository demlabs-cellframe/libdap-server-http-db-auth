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
#include "dap_strfuncs.h"

#ifdef _WIN32
#include "registry.h"
#endif

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

    //    set_default_locale();
    //    command_execution_string = shell_script_filename = (char *) NULL;
    dap_set_appname("http_db_auth_tool");
#ifdef DAP_OS_LINUX
    g_sys_dir_path = dap_strdup_printf("/opt/%s",dap_get_appname() );
#elif _WIN32
    dap_sprintf(s_sys_dir_path, "%s/%s", regGetUsrPath(), dap_get_appname() );
#endif
    g_sys_dir_path_len = strlen(g_sys_dir_path);

    char * l_app_title = dap_strdup_printf("%s console interface",dap_get_appname());

    char * l_config_path = dap_strdup_printf("%s/etc", g_sys_dir_path);

    dap_common_init( l_app_title, NULL );
    dap_log_level_set( L_CRITICAL );
    dap_config_init( g_sys_dir_path );

    if((g_config = dap_config_open(dap_get_appname())) == NULL) {
        printf("Can't init general configurations %s.cfg\n",dap_get_appname());
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

