cmake_minimum_required(VERSION 2.8)
project (dap_db)
  
set(DB_SRCS db_core.c  db_http.c  db_http_file.c)

add_library(${PROJECT_NAME} STATIC ${DB_SRCS})

target_link_libraries(dap_db
    dap_core dap_crypto
    dap_http_server dap_enc_server
    ${BSON_LIBRARIES} ${MONGO_LIBRARIES})

target_include_directories(dap_db
    INTERFACE .
    PUBLIC ${BSON_INCLUDE_DIRS} ${MONGO_INCLUDE_DIRS})
