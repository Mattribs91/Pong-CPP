cmake_minimum_required(VERSION 3.10)
project(Pong_C++ C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------------
# Sources et En-têtes
# ----------------------------------------------------------------------
set(SOURCES
        src/main.cpp
        src/Moteur.cpp
        src/Image.cpp
        src/Balle.cpp
        include/Balle.h
        src/Raquette.cpp
        include/Raquette.h
)

set(HEADERS
        include/Image.h
        include/Moteur.h
        src/Balle.cpp
        include/Balle.h
        src/Raquette.cpp
        include/Raquette.h
)

add_executable(Pong_C++ ${SOURCES} ${HEADERS}
        src/Balle.cpp
        include/Balle.h
        src/Raquette.cpp
        include/Raquette.h)
target_include_directories(Pong_C++ PRIVATE include)

# ----------------------------------------------------------------------
# Détection de la Plateforme et Configuration
# ----------------------------------------------------------------------

if(APPLE)
    # --- Configuration macOS (Homebrew via CLion) ---
    message(STATUS "Configuration pour macOS...")

    # Chemins standard Homebrew
    set(HOMEBREW_PATH /opt/homebrew)
    if(NOT EXISTS ${HOMEBREW_PATH})
        set(HOMEBREW_PATH /usr/local) # Pour les Mac Intel
    endif()

    find_library(SDL2_LIBRARY SDL2 PATHS ${HOMEBREW_PATH}/lib REQUIRED)
    find_library(SDL2_IMAGE_LIBRARY SDL2_image PATHS ${HOMEBREW_PATH}/lib REQUIRED)

    # On cherche le dossier qui contient SDL.h (ex: .../include/SDL2)
    find_path(SDL2_INCLUDE_DIR SDL.h PATH_SUFFIXES SDL2 PATHS ${HOMEBREW_PATH}/include REQUIRED)
    find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h PATH_SUFFIXES SDL2 PATHS ${HOMEBREW_PATH}/include REQUIRED)

    target_include_directories(Pong_C++ PRIVATE ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
    target_link_libraries(Pong_C++ PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

elseif(WIN32)
    # --- Configuration Windows (MinGW / Local) ---
    message(STATUS "Configuration pour Windows...")

    # On suppose que le dossier SDL2 est à la racine du projet
    set(LOCAL_SDL2_PATH "${CMAKE_SOURCE_DIR}/SDL2")

    # Inclusions : on ajoute le dossier include/SDL2 pour pouvoir faire #include <SDL.h>
    target_include_directories(Pong_C++ PRIVATE "${LOCAL_SDL2_PATH}/include/SDL2")
    target_include_directories(Pong_C++ PRIVATE "${LOCAL_SDL2_PATH}/include")

    # Recherche des librairies dans SDL2/lib
    find_library(SDL2_LIB NAMES SDL2 libSDL2 PATHS "${LOCAL_SDL2_PATH}/lib" NO_DEFAULT_PATH)
    find_library(SDL2_MAIN_LIB NAMES SDL2main libSDL2main PATHS "${LOCAL_SDL2_PATH}/lib" NO_DEFAULT_PATH)
    find_library(SDL2_IMAGE_LIB NAMES SDL2_image libSDL2_image PATHS "${LOCAL_SDL2_PATH}/lib" NO_DEFAULT_PATH)

    if(NOT SDL2_LIB OR NOT SDL2_MAIN_LIB OR NOT SDL2_IMAGE_LIB)
        message(FATAL_ERROR "Bibliothèques SDL2 introuvables dans ${LOCAL_SDL2_PATH}/lib")
    endif()

    # Linkage : mingw32 est nécessaire sous Windows avec MinGW
    target_link_libraries(Pong_C++ PRIVATE mingw32 ${SDL2_MAIN_LIB} ${SDL2_LIB} ${SDL2_IMAGE_LIB})

    # Ajout du flag -mwindows pour eviter la console en mode Release si besoin
    # target_link_options(Projet_Algo PRIVATE -mwindows)

    # Copie des DLLs si présentes dans bin/ (pour l'exécution)
    file(GLOB DLL_FILES "${LOCAL_SDL2_PATH}/bin/*.dll")
    if(DLL_FILES)
        add_custom_command(TARGET Pong_C++ POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${DLL_FILES}
                $<TARGET_FILE_DIR:Pong_C++>
        )
    endif()

else()
    # --- Configuration Linux / Autre ---
    message(STATUS "Configuration pour Linux/Unix...")
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    target_include_directories(Pong_C++ PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(Pong_C++ PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif()

# ----------------------------------------------------------------------
# Copie des Assets (Commun)
# ----------------------------------------------------------------------
add_custom_command(TARGET Pong_C++ POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Pong_C++>/assets
)
#