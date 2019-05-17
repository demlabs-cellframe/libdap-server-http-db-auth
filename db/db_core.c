/*
 Copyright (c) 2017-2018 (c) Project "DeM Labs Inc" https://github.com/demlabsinc
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

#include <string.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include "dap_common.h"
#include "db_core.h"
#define LOG_TAG "db"

mongoc_client_t *mongo_client = NULL,
                *traffick_track_db_client = NULL;

int db_core_init(const char *db_path)
{
    mongoc_init();

    mongo_client = mongoc_client_new (db_path);
    traffick_track_db_client = mongoc_client_new (db_path);
    log_it(L_DEBUG, "Checking connection to database...");
    if(!mongoc_client_get_server_status(mongo_client, NULL, NULL, NULL))
    {
        log_it(L_ERROR, "Can't connect to database");
        return -1;
    }

    return 0;
}

void db_core_deinit()
{
    if(mongo_client)
        mongoc_client_destroy(mongo_client);
    if(traffick_track_db_client)
         mongoc_client_destroy(traffick_track_db_client);

    mongoc_cleanup ();
}

void db_core_refresh()
{

}


int db_input_validation(const char * str)
{
        // The compiler will stack "multiple" "strings" "end" "to" "end"
        // into "multiplestringsendtoend", so we don't need one giant line.
        static const char *nospecial="0123456789"
                "abcdefghijklmnopqrstuvwxyz"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                ".=@?_!#$%";

        while(*str) // Loop until (*url) == 0.  (*url) is about equivalent to url[0].
        {
                // Can we find the character at *url in the string 'nospecial'?
                // If not, it's a special character and we should return 0.
                if(strchr(nospecial, *str) == NULL) return(0);
                str++; // Jump to the next character.  Adding one to a pointer moves it ahead one element.
        }

        return(1); // Return 1 for success.
}
