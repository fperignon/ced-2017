# debug
macro(display V)
  message(STATUS "${V} = ${${V}}")
endmacro(display V)

# -- Liste des extensions de fichiers sources standards
# Resultat dans ALL_EXTS
macro(get_standard_ext)
  set(ALL_EXTS)
  foreach(_EXT
      ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}
      ${CMAKE_C_SOURCE_FILE_EXTENSIONS}
      ${CMAKE_Fortran_SOURCE_FILE_EXTENSIONS}
      ${CMAKE_Java_SOURCE_FILE_EXTENSIONS}
      ${CMAKE_RC_SOURCE_FILE_EXTENSIONS})
    list(APPEND ALL_EXTS ${_EXT})
  endforeach()
  if(ALL_EXTS)
    list(REMOVE_DUPLICATES ALL_EXTS)
  endif()
endmacro()

# Visite une liste de répertoires et collecte tous les fichiers vérifiant certaines extensions (.f90, .c, .cpp)
# La liste obtenue est stockée dans la variable SOURCES_FILES
# Utilisation:
# set(src_dirs dir1 dir2)
# get_sources(src_dirs)
macro(get_sources)
  set(SOURCES_FILES)
  get_standard_ext()
  # ARGV : liste de tous les arguments de la macro
  # recupère les fichiers *.EXT
  foreach(_DIR ${ARGV})
    foreach(_EXT ${ALL_EXTS})
      # recupère les fichiers *.EXT
      file(GLOB FILES_LIST ${_DIR}/*.${_EXT})
      if(FILES_LIST) # si non vide
	list(APPEND SOURCES_FILES ${FILES_LIST})
      endif()
    endforeach()
  endforeach()
  if(SOURCES_FILES)
    list(REMOVE_DUPLICATES SOURCES_FILES)
  endif()
endmacro() 


# Visite une liste de répertoires et collecte tous les fichiers 'headers'
# La liste obtenue est stockée dans la variable HEADERS_FILES
# Utilisation:
# set(src_dirs dir1 dir2)
# get_headers(src_dirs)
function(get_headers slist)
  set(HEADERS_FILES)
  foreach(_DIR IN LISTS slist)
    # recupère les fichiers *.h, *.hpp
    file(GLOB FILES_LIST ${_DIR}/*.h ${_DIR}/*.hpp)
    if(FILES_LIST) # si non vide
      list(APPEND HEADERS_FILES ${FILES_LIST})
    endif()
  endforeach()
  if(HEADERS_FILES)
    list(REMOVE_DUPLICATES HEADERS_FILES)
    set(HEADERS_FILES ${HEADERS_FILES} PARENT_SCOPE)
  endif()
endfunction() 

function(varscope)
  message(" --- Function ---")
  message("var2 dans fonction : ${var2}")
  set(varlocale "var locale")
  message("var locale fonction : ${varlocale}")
  set(var1 "new var1")
  message("var1 modifiée dans fonction : ${var1}")
  message("varcache dans fonction : ${var2}")
  set(var2 "new var2")
  message("var cache écrasée dans fonction : ${var2}")
  
endfunction()
macro(m_varscope)
  message(" --- Macro ---")
  message("var2 dans fonction : ${var2}")
  set(varlocale "var locale")
  message("var locale fonction : ${varlocale}")
  set(var1 "new var1")
  message("var1 modifiée dans fonction : ${var1}")
  message("varcache dans fonction : ${var2}")
  set(var2 "new var2")
  message("var cache écrasée dans fonction : ${var2}")
  
endmacro()


