cmake_minimum_required(VERSION 3.16)


project( 
    Greeter
    VERSION "1.0"
    HOMEPAGE_URL "https://ww.studyplan.dev"
    DESCRIPTION "A program that says hello to people"
)
if(DEFINED PROJECT_VERSION)
    message(STATUS "Configuring Greeter Version: ${PROJECT_VERSION}")
else()
    message(FATAL_ERROR " Project version must be specified")
endif()
add_subdirectory(greeter) #libary
add_subdirectory(app) #The executable

