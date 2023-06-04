cmake_minimum_required(VERSION 3.4)
project(Ageofwar)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?

find_package(Imagine REQUIRED)

add_executable(Ageofwar
                                    main.cpp
    theorique.h     pratique.h      personnage.cpp
    interface.h                     interface.cpp
    adversaire.h                    adversaire.cpp)

ImagineUseModules(Ageofwar Graphics)
ImagineUseModules(Ageofwar Images)

# Objectifs : {☐, ☑}
#      ☑ • Gérer le timing d'apparition
#      ☐ • Barre de vie des bases
#      ☐ • Barres de génération des images pour ne pas recharger tout le fond + menu à chaque fois
#      ☐ • Barre de vie des pélos
#      ☐ • Avancer les pélos
#      ☐ • Faire les bastons
#      ☐ • Faire le spécial : pluie de météorites
#      ☐ • Faire les taches de sang
