# ============================================================
# Config pour la génération de documentation.
# Exemple avec sphinx et doxygen
#
# - doxygen pour le code en C, C++ et Fortran
# - sphinx pour le code python et un exemple de manuel utilisateur
# 
# ============================================================

include(FindPythonModule)
include(FindSphinxModule)

# On fixe le répertoire de sortie pour la doc, dans le build
set(DOC_ROOT_DIR ${CMAKE_BINARY_DIR}/doc/build/html/ CACHE INTERNAL "Repertoire de génération de la documentation")

# On vérifie que doxygen est bien disponible
find_package(Doxygen)
#  ====== doxygen setup ======
if(DOXYGEN_FOUND)
  
  # où doit on écrire les fichiers générés par doxygen?
  if(NOT DOXYGEN_OUTPUT)
    set(DOXYGEN_OUTPUT ${DOC_ROOT_DIR}/doxygen CACHE INTERNAL "Doxygen outputs.")
  endif()
  file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT})
  # Fichier de configuration pour doxygen
  set(DOXY_CONFIG "${CMAKE_BINARY_DIR}/doc/config/doxy.config" CACHE INTERNAL "Doxygen configuration file for doc from sources.")

  # CMake génère un fichier de conf pour doxygen, à partir de doxy.config.in
  configure_file(${CMAKE_SOURCE_DIR}/doc/config/doxy.config.in ${DOXY_CONFIG} @ONLY)
  # Creation d'une target 'doxygen' pour le Makefile
  add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${DOXY_CONFIG})
  
endif()

  
#  ====== Sphinx setup ======
# Vérification des dépendances
# Il faut un interpréteur python et le module sphinx
find_package(PythonInterp)
find_python_module(sphinx)
if(sphinx_FOUND)  
  # ---  Fichiers de config pour sphinx ---
  # conf.py est généré par cmake à partir de conf.py.in
  configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/conf.py.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sphinx/conf.py" @ONLY)

  # index.rst (qui sera utilisé pour créer index.html) est généré
  # à partir de index.rst.in
  configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/index.rst.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sphinx/index.rst" @ONLY)

  # Tous les fichiers rst du répertoire doc/sphinx sont copiés dans le build
  FILE(GLOB RST_FILES sphinx/*.rst)
  foreach(_file ${RST_FILES})
    get_filename_component(_file_name ${_file} NAME)
    configure_file (
      "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/${_file_name}"
      "${CMAKE_CURRENT_BINARY_DIR}/sphinx/${_file_name}" @ONLY)

  endforeach()
  
  set(SPHINX_EXECUTABLE sphinx-build)

  # python apidoc --> generation de fichiers rst à partir du code
  set(SPHINX_APIDOC sphinx-apidoc)
  set(GENERATED_DOC ${CMAKE_CURRENT_BINARY_DIR}/sphinx/reference)
  set(APIDOC_PARAMETERS -e -P -o ${GENERATED_DOC})

  # Création d'une target apidoc pour le Makefile
  # make apidoc --> documentation de l'api à partir des commentaires python
  add_custom_target(apidoc
    COMMAND ${SPHINX_APIDOC} ${APIDOC_PARAMETERS}
    ${CMAKE_SOURCE_DIR}/tools2py
    )
  add_custom_command(
    TARGET apidoc PRE_BUILD
    COMMAND ln -sf ${CMAKE_SOURCE_DIR}/tools2py ${CMAKE_BINARY_DIR}/)
  
  
  # html doc
  set(SPHINX_PARAMETERS
    -b html # html output
    -d build/doctrees # path to doctree files
    ${CMAKE_CURRENT_BINARY_DIR}/sphinx  # path to rst source
    )

  add_custom_target(html
    COMMAND ${SPHINX_EXECUTABLE} ${SPHINX_PARAMETERS}
    ${CMAKE_CURRENT_BINARY_DIR}/build/html
    DEPENDS apidoc doxygen
    )
  
  # latex doc
  set(SPHINX_LATEX_PARAMETERS
    -b latex # latex output
    -d build/doctrees # path to doctree files
    ${CMAKE_CURRENT_BINARY_DIR}/sphinx  # path to rst source
    )
  
  add_custom_target(latex
    COMMAND ${SPHINX_EXECUTABLE} ${SPHINX_LATEX_PARAMETERS}
    ${CMAKE_CURRENT_BINARY_DIR}/build/latex
    DEPENDS apidoc
    )

  
  add_custom_target(doc
    DEPENDS doxygen html)

endif()
