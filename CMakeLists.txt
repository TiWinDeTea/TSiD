cmake_minimum_required(VERSION 2.8.9)

#project configuration
project(TSiD)
set(EXECUTABLE_OUTPUT_PATH build/)

#include SFML
include_directories(D:/CloudStation/Programmation/C++/SFML-2.3.2-windows-gcc-4.8.1-tdm-32-bit/include)
link_directories(D:/CloudStation/Programmation/C++/SFML-2.3.2-windows-gcc-4.8.1-tdm-32-bit/lib)

#Génération de la liste des fichiers sources
file(
    GLOB_RECURSE
    source_files
    src/server0/*
    src/common/*

)

#executable declaration
add_executable(
    server0
    ${source_files}
)

#Configuration of link edition
target_link_libraries(
    server0
    sfml-system
    sfml-network
)