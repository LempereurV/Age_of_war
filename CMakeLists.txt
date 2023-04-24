
cmake_minimum_required(VERSION 3.4)
project(Ageofwar)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

find_package(Imagine REQUIRED)

add_executable(Ageofwar main.cpp
    personnage.cpp liste.cpp
    tourelle.h theorique.h interface.h pratique.h)
ImagineUseModules(Ageofwar Graphics)


