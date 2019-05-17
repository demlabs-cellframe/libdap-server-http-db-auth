cmake_minimum_required(VERSION 3.0)
project (dap_auth)
  
set(AUTH_SRCS db_auth.c)

add_library(${PROJECT_NAME} STATIC ${AUTH_SRCS})

target_link_libraries(dap_auth dap_core
    dap_crypto dap_http_server dap_enc_server
    dap_stream ${MONGO_LIBRARIES})

target_include_directories(dap_auth
    INTERFACE .
    PRIVATE ${MONGO_INCLUDE_DIRS})
