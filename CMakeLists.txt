cmake_minimum_required(VERSION 3.0)
project (dap_server_http_db_auth)
  
file(GLOB DAP_SERVER_HTTP_DB_AUTH_SOURCES src/*.c)
file(GLOB DAP_SERVER_HTTP_DB_AUTH_HEADERS include/*.h)

add_library(${PROJECT_NAME} STATIC ${DAP_SERVER_HTTP_DB_AUTH_SOURCES} ${DAP_SERVER_HTTP_DB_AUTH_HEADERS})
add_executable(${PROJECT_NAME}_tool ${DAP_SERVER_HTTP_DB_AUTH_SOURCES} ${DAP_SERVER_HTTP_DB_AUTH_HEADERS} dap_server_http_db_auth_tool.c )

target_link_libraries(${PROJECT_NAME} dap_crypto dap_stream dap_server_http_db )
target_link_libraries(${PROJECT_NAME}_tool dap_crypto dap_stream dap_server_http_db )

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

target_include_directories(${PROJECT_NAME}_tool PRIVATE include)
target_include_directories(${PROJECT_NAME}_tool PRIVATE src)

INSTALL(TARGETS ${PROJECT_NAME}_tool DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
INSTALL(
    DIRECTORY scripts/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/sbin
    FILES_MATCHING PATTERN "*" PATTERN "*"
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    )
