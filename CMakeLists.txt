cmake_minimum_required(VERSION 3.0)
project (dap_server_http_db_auth)
  
file(GLOB DAP_SERVER_HTTP_DB_AUTH_SOURCES src/*.c)
file(GLOB DAP_SERVER_HTTP_DB_AUTH_HEADERS include/*.h)

add_library(${PROJECT_NAME} STATIC ${DAP_SERVER_HTTP_DB_AUTH_SOURCES} ${DAP_SERVER_HTTP_DB_AUTH_HEADERS})

target_link_libraries(${PROJECT_NAME} dap_crypto dap_stream dap_server_http_db )

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

