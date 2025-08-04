cmake_minimum_required(VERSION 3.24)
project(sakora)

# -Wfloat-equal
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic -Wimplicit-fallthrough -Wsequence-point -Wswitch-unreachable -Wstringop-truncation -Wbool-compare -Wtautological-compare -Wshadow=global -Wpointer-arith -Wpointer-compare -Wcast-align -Wcast-qual -Wwrite-strings -Wdangling-else -Wlogical-op -Wconversion -Werror")

file(GLOB SRC_FILES "main.cpp"
                    "Fronetend/Condole/*.h"
                    "Frontend/Console/*.cpp"
                    "Error/*.h"
                    "Error/*.cpp"
                    "Frontend/Lexer/*.h"
                    "Frontend/Lexer/*.cpp"
                    "Frontend/Parser/*.h"
                    "Frontend/Parser/*.cpp"
                    "Frontend/Generator/*.h"
                    "Frontend/Generator/*.cpp"
                    "Backend/*.h"
                    "Backend/*.cpp"
                    "Backend/env/type/*.h"
                    "Backend/env/type/*.cpp"
                    "Backend/env/*.h"
                    "Backend/env/*.cpp"
                    "Backend/vm/*.cpp"
                    "Backend/vm/*.h"
                    )
        
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} )