# =============================================================================
# LIBRARY COMPILATION
# =============================================================================

#set(OPTIONS O0 O1 O2 O3)
#set(TNAME "test001")
#set(TNUM "001")

#set(OPTIONS "O0" "O1" "O2" "O3")
#set(OPTIONS "O2" "O3")
#set(TBASENAME "tst")
#set(VERSIONS "001" "002" "003")
get_property(OPTIONS GLOBAL PROPERTY PROP_OPTIONS)
get_property(VERSIONS GLOBAL PROPERTY PROP_VERSIONS)


set(TBASENAME "tst")
set(LIBBASENAME "mcblas")


foreach(OPT ${OPTIONS})
  foreach(VER ${VERSIONS})
    set(TEST ${TBASENAME}${VER}${OPT})
    set(TSRC ${TBASENAME}${VER})

    add_executable(${TEST})
    target_sources(${TEST} PUBLIC ${TBASENAME}.hpp PRIVATE ${TSRC}.cpp)
    #    target_sources(${TEST} INTERFACE ${TBASENAME}.hpp PRIVATE ${TSRC}.cpp)
    target_link_libraries(${TEST} PUBLIC ${LIBBASENAME}${VER}${OPT})
    target_compile_options(${TEST} PRIVATE -Wall -g -${OPT})
    target_include_directories(${TEST} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
    #    target_include_directories(${TEST} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  endforeach()
endforeach()


add_subdirectory(runs)
