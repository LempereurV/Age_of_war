
cmake_minimum_required(VERSION 3.4)
project(Ageofwar)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

find_package(Imagine REQUIRED)

add_executable(Ageofwar main.cpp
    personnage.cpp
    theorique.h pratique.h
    tourelle.h tourelle.cpp
    interface.h interface.cpp
    adversaire.h adversaire.cpp)

ImagineUseModules(Ageofwar Graphics)
ImagineUseModules(Ageofwar Images)

