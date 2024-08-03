cmake_minimum_required(VERSION 3.28)
project(chttp C)

set(CMAKE_C_STANDARD 11)

add_executable(chttp src/main.c
        include/server.h
        src/server.c
        include/request_handler.h
        src/request_handler.c
        include/response.h
        src/response.c
        include/file_utils.h
        src/file_utils.c
        include/messages.h
        src/messages.c
        include/logger.h
        src/logger.c)
