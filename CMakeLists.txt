cmake_minimum_required(VERSION 3.16)

project(PongProject VERSION 1.0 LANGUAGES CXX)

# Standard C++17 (nécessaire notamment pour std::clamp utilisé dans Ball.cpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Recherche de la bibliothèque OpenCV installée sur le système
find_package(OpenCV REQUIRED)

# Déclaration explicite des fichiers d'en-tête (.hpp)
set(HEADERS
    include/Screen.hpp
    include/Ball.hpp
    # include/Joueur.hpp
    # include/JoueurMachine.hpp
)

# Déclaration explicite des fichiers sources (.cpp)
set(SOURCES
    src/main.cpp
    src/Screen.cpp
    src/Ball.cpp
    # src/Joueur.cpp
    # src/JoueurMachine.cpp
)

# Création de l'exécutable
add_executable(pong ${SOURCES} ${HEADERS})

# Indique au compilateur où trouver les .hpp (permet d'écrire #include "Screen.hpp")
target_include_directories(pong PRIVATE include ${OpenCV_INCLUDE_DIRS})

# Liaison avec les bibliothèques OpenCV
target_link_libraries(pong PRIVATE ${OpenCV_LIBS})