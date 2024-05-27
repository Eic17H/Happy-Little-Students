cmake_minimum_required(VERSION 3.27)
project(Happy_Little_Students C)

set(CMAKE_C_STANDARD 99)

add_executable(Happy_Little_Students main.c
        tipi.h
        letturaFile.c
        letturaFile.h
        costanti.h
        turno.c
        turno.h
        input.c
        input.h
        estetica.c
        estetica.h
        ANSI-color-codes.h
        utilita.c
        utilita.h)
