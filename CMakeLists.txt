cmake_minimum_required(VERSION 3.29)
project(record C)

set(CMAKE_C_STANDARD 11)

add_executable(record main.c
        record.c
        record.h
        global.h
        global.c
        menu.h
        menu.c
        file.h
        file.c
        maincontrol.h
        maincontrol.c)
