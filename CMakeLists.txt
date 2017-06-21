cmake_minimum_required(VERSION 3.7)
project(SP3)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        main.c
        SPArrayList.h
        SPFIARGame.c
        SPFIARGame.h
        SPMainAux.c
        SPMainAux.h
        SPMiniMaxNode.c
        SPMiniMaxNode.h
        SPArrayList.c
        SPFIARParser.c
        SPFIARParser.h
        SPMiniMax.c
        SPMiniMax.h)
add_executable(SP3 ${SOURCE_FILES})