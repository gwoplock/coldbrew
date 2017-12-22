cmake_minimum_required(VERSION 3.2.2)
project(coldbrew)

set(CMAKE_C_STANDARD 99)

add_definitions(-DDEV)

set(SOURCE_FILES src/main.c src/commandLine/CommandlineParser.h src/commandLine/CommandLineParser.c
        src/utils/stringMinip.h src/utils/stringMinip.c src/utils/print.c src/utils/print.h)

#if we need hashmap string->int stuff uncomment the line below
#set(SOURCE_FILES ${SOURCE_FILES} src/hashMap/hash_map_string_int.h src/hashMap/hash_map_string_int.c src/hashMap/hash.h src/hashMap/hash.c)

add_executable(coldbrew ${SOURCE_FILES})

target_link_libraries(coldbrew m)
