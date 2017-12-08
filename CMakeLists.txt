cmake_minimum_required(VERSION 3.2.2)
project(coldbrew)

set(CMAKE_C_STANDARD 99)

target_link_libraries(project_name m)

set(SOURCE_FILES src/main.c src/commandLine/CommandlineParser.h src/commandLine/CommandLineParser.c src/hashMap/hash_map_string_int.h src/hashMap/hash_map_string_int.c src/hashMap/hash.h src/hashMap/hash.c)
add_executable(coldbrew ${SOURCE_FILES})
