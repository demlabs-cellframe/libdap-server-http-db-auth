#include <db_auth.h>

int dap_server_http_db_auth_check_key(uint8_t *key)
{
    exist_user_in_db("da");
}
