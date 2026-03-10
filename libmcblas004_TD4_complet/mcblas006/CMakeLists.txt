# ============================================================
# Adding mcblas versions
# ============================================================


set(GOPTS -Wall -g)
#set(OPTIONS "O0" "O1" "O2" "O3")
set(LIBBASENAME "mcblas")

# set(OPTIONS "O0" "O1" "O2" "O3")
# set(VERSIONS "001" "002" "003")
#set(OPTIONS "O2" "O3")
#set(VERSIONS "001" "002" "003")
get_property(OPTIONS GLOBAL PROPERTY PROP_OPTIONS)

foreach(OPT ${OPTIONS})
  # foreach(VER ${VERSIONS})
  set(VER "006")
  set(LIB ${LIBBASENAME}${VER}${OPT})

    add_library(${LIB})
    target_sources(${LIB}
      PUBLIC
      mcblas0.hpp
      mcblas1.hpp
      mcblas3.hpp
      PRIVATE
      mcblas0.cpp
      mcblas1.cpp
      mcblas3.cpp
    )
    target_compile_features(${LIB} PUBLIC cxx_std_11)
    target_compile_options(${LIB} PRIVATE ${GOPTS} -${OPT})
    target_compile_options(${LIB} BEFORE INTERFACE ${GOPTS} -${OPT})
    target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

  # endforeach()
endforeach()
