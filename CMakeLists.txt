cmake_minimum_required(VERSION 3.0)

project(eggcc)

include_directories(inc)

set(eggccSources
    src/keywords.cpp
    src/lex.cpp
    src/split.cpp
    src/main.cpp
    )

add_executable( eggcc ${eggccSources} )

if( MSVC )
if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
    message("\nYou are running a cmake version lower than 3.6.0, you have to set 'eggcc' as the Startup project manually.\n")
else()
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT eggcc )
endif()
endif()
