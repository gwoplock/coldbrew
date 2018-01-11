cmake_minimum_required(VERSION 3.2.2)
project(coldbrew)

set(CMAKE_C_STANDARD 99)

add_definitions(-DDEV)

set(SOURCE_FILES src/main.c src/commandLine/CommandlineParser.h src/commandLine/CommandLineParser.c
        src/utils/stringManip.h src/utils/stringManip.c src/utils/IO/print.c src/utils/IO/print.h src/Commands/Install.c
        src/Commands/Install.h src/build_parser/coldbrew/scriptHandler.c src/build_parser/coldbrew/scriptHandler.h
        src/utils/IO/temporaryFiles.c src/utils/IO/temporaryFiles.h src/build_parser/package/pkginfo.c
        src/build_parser/package/pkginfo.h src/utils/IO/fileIO.c src/utils/IO/fileIO.h src/build_parser/package/srcinfo.c
        src/build_parser/package/srcinfo.h)

#if we need hashmap string->int stuff uncomment the line below
#set(SOURCE_FILES ${SOURCE_FILES} src/hashMap/hash_map_string_int.h src/hashMap/hash_map_string_int.c src/hashMap/hash.h src/hashMap/hash.c)

set(SOURCE_FILES ${SOURCE_FILES} src/utils/IO/http.c src/utils/IO/http.h)

#if we need zlib compression stuff uncomment the line below
#set(SOURCE_FILES ${SOURCE_FILES} src/utils/compression.c src/utils/compression.h)

#curl
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

#zlib
#find_package(ZLIB REQUIRED)

add_executable(coldbrew ${SOURCE_FILES})

#cmath linking
target_link_libraries(coldbrew m)

#curl linking
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(coldbrew ${CURL_LIBRARIES})

#zlib linking
#include_directories( ${ZLIB_INCLUDE_DIRS} )
target_link_libraries( coldbrew ${ZLIB_LIBRARIES} )