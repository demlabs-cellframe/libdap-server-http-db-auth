cmake_minimum_required(VERSION 3.0)
project (dap_server_http_db_auth)
  
set(AUTH_SRCS db_auth.c)

add_library(${PROJECT_NAME} STATIC ${AUTH_SRCS})

target_link_libraries(${PROJECT_NAME} dap_core
    dap_crypto dap_http_server dap_enc_server
    dap_stream dap_http_server_db )

