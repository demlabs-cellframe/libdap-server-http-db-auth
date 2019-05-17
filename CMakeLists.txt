cmake_minimum_required(VERSION 2.8)
project (dap_server_http_db_auth)

# fix implicit declaration warnings
add_definitions ("-D_GNU_SOURCE")

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra")

 
find_package(PkgConfig)
pkg_check_modules(MONGO REQUIRED libmongoc-1.0)
pkg_check_modules(BSON REQUIRED libbson-1.0)

add_subdirectory(db)
add_subdirectory(auth)


file(GLOB FILE_SOURCES *.c)
file(GLOB FILE_HEADERS *.h)

add_library(${PROJECT_NAME} STATIC ${FILE_SOURCES} ${FILE_HEADERS})

target_link_libraries(${PROJECT_NAME} dap_crypto dap_auth dap_db)
target_include_directories(${PROJECT_NAME} INTERFACE .)


#set(${PROJECT_NAME}_DEFINITIONS CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE)
#
#set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)