# ---- Configuration de CMake pour le projet ----
# Choix de la version minimale de cmake
cmake_minimum_required(VERSION 3.0)

# On définit un répertoire contenant les macros et fonctions spécifiques au projet
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Un fichier de définitions de macros cmake (print, recherche de fichiers ...)
include(MyTools)

# Fixe une valeur par defaut pour le mode de construction
# Si build_type n'est pas explicitement fixé à l'appel de cmake, on choisit Release.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# Quelques options d'activation/désactivation des dépendances
option(WITH_FFTW "Recherche de fftw, defaut = OFF" OFF)
option(WITH_MKL "utilisation de la bibliotheque mkl, defaut = OFF" OFF)
option(WITH_BOOST "utilisation de la boost, defaut = OFF" OFF)
option(WITH_DOCUMENTATION "Generation de la documentation. Defaut = OFF" OFF)

# --- Déclaration du projet, choix des langages ---
# --> création implicite d'un certains nombres de variables
# donc CMAKE_BINARY_DIR et CMAKE_SOURCE_DIR
project(NomDuSoft CXX Fortran C)

# ---- Config pour le fortran ---
# Définition du répertoire qui va contenir les modules fortran :
set(CMAKE_Fortran_MODULE_DIRECTORY ${CMAKE_BINARY_DIR}/Modules)
# et ajout de ce répertoire dans les chemins d'include :
include_directories(${CMAKE_Fortran_MODULE_DIRECTORY})

# --- Recherche des dépendances ---
set(EXTERNAL_LIBS)
# EXTERNAL_LIBS = listes des dépendances (chemin absolu)

# Boost
if(WITH_BOOST)
  find_package(Boost REQUIRED)
  if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(HAS_BOOST 1) # pour config.hpp
  endif()
endif()
# FFTW
if(WITH_FFTW)
  find_package(FFTW REQUIRED)
  include_directories(${FFTW_INCLUDE_DIRS})
  set(HAS_FFTW 1) # pour config.hpp
  list(APPEND EXTERNAL_LIBS ${FFTW_LIBRARIES})
endif()

# MKL
if(WITH_MKL)
  #find_package(MKL REQUIRED)
  set(MKL_INCLUDE_DIRS $ENV{mkl_DIR})
  include_directories(${MKL_INCLUDE_DIRS})
  SET(CMAKE_CXX_FLAGS "-mkl ${CMAKE_CXX_FLAGS}")
  set(HAS_MKL 1) # pour config.hpp
endif()

# --- Génération de tools_config.hpp ---
# Le contenu de ce fichier dépendra des dépendances trouvées
# si HAS_XXX est vrai (1), cmakedefine HAS_XXX deviendra ' #define HAS_XXX '
if(EXISTS ${CMAKE_SOURCE_DIR}/config.hpp.cmake)
  configure_file(${CMAKE_SOURCE_DIR}/config.hpp.cmake tools_config.hpp)
  # on ajoute le répertoire contenant le fichier header généré à l'option '-I'
  include_directories(${CMAKE_BINARY_DIR})
endif()

# ---- Recupération des fichiers sources et entêtes ----
# La liste des répertoires contentant les sources pour la librairie
# est sauvée dans la variables NomDuSoft_SRC_DIRS
set(NomDuSoft_SRC_DIRS
  ${CMAKE_SOURCE_DIR}/src/tools/
  src/tools/mkl
  )

if(HAS_FFTW)
  # Ajout des src pour fftw si fftw est présent sur le système
  list(APPEND NomDuSoft_SRC_DIRS
    src/tools/fft
    )
endif()

# On balaie les répertoires de NomDuSoft_SRC_DIRS pour lister tous les fichiers
# à compiler, et on crée une variable contenant la liste de ces fichiers
# (NomDuSoft_SRC pour les sources, NomDuSoft_HEADERS pour les headers)
get_sources(${NomDuSoft_SRC_DIRS})
set(NomDuSoft_SRC ${SOURCES_FILES})
get_headers(${NomDuSoft_SRC_DIRS})
set(NomDuSoft_HEADERS ${HEADERS_FILES})


# Prise en compte des répertoires des sources pour les include
include_directories(${NomDuSoft_SRC_DIRS})

# Tout est maintenant prêt pour la création de la librairie:
add_library(tools SHARED ${NomDuSoft_SRC})

# link de la librairie, si nécessaire
target_link_libraries(tools ${EXTERNAL_LIBS})

# ---- Creation d'un exécutable, utilisant la librairie qu'on vient de créer ----
# Creation d'un executable c++
add_executable(monExeCpp src/main2.cpp)
# link avec notre librairie
target_link_libraries(monExeCpp tools)

# Création d'un executable fortran
#add_executable(monExeFortran src/code2_Fortran/main1.f90)
#set_property(TARGET tools monExeFortran PROPERTY LINKER_LANGUAGE CXX) 
# link avec pour l'executable Fortran
#target_link_libraries(monExeFortran tools)

# ---- installation des différents composants ----
install(TARGETS monExeCpp tools
  RUNTIME DESTINATION bin  # executables
  ARCHIVE DESTINATION lib  # librairies statiques
  LIBRARY DESTINATION lib  # librairies dynamiques
  )

install(FILES ${NomDuSoft_HEADERS} DESTINATION include)
install(DIRECTORY ${CMAKE_Fortran_MODULE_DIRECTORY} DESTINATION include)


# Generation (option) de la doc
if(WITH_DOCUMENTATION)
  add_subdirectory(doc)
endif()

# ---- Exemples de test ----
include(CTest)
if(HAS_BOOST)
  add_executable(testBoostExe src/tests/test_boost.cpp)
  target_link_libraries(testBoostExe tools)
  add_test(testBoost ${CMAKE_BINARY_DIR}/testBoostExe)
endif()

if(HAS_FFTW)
  add_executable(testFFTExe src/tests/test_fft.f90)
  target_link_libraries(testFFTExe tools)
  add_test(testFFT ${CMAKE_BINARY_DIR}/testFFTExe)
endif()

# ---- Résumé ----
message(STATUS "====================== Summary ======================")
message(STATUS " Fortran compiler : ${CMAKE_Fortran_COMPILER}")
message(STATUS " CXX compiler : ${CMAKE_CXX_COMPILER}")
if(HAS_FFTW)
  message(STATUS " FFTW libs found : ${FFTW_LIBRARIES}")
  message(STATUS " FFTW Headers : ${FFTW_INCLUDE_DIRS}")
else()
  message(STATUS " FFTW not found")
endif()
if(HAS_BOOST)
  message(STATUS " Boost found in : ${Boost_INCLUDE_DIRS}")
else()
  message(STATUS " Boost not found.")
endif()
message(STATUS " Sources are in : ${CMAKE_SOURCE_DIR}")
message(STATUS " Project will be installed in ${CMAKE_INSTALL_PREFIX}")
message(STATUS " CMake build type is : ${CMAKE_BUILD_TYPE}")

