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
        estetica.c
        estetica.h
        ANSI-color-codes.h
        utilita.c
        utilita.h
        carteCfu.c
        carteCfu.h
        carteOstacolo.c
        carteOstacolo.h
        carteEffetto.c
        carteEffetto.h
        log.c
        log.h
        salvataggio.c
        salvataggio.h
        carteIstantanee.c
        carteIstantanee.h
        interfaccia.c
        interfaccia.h)
