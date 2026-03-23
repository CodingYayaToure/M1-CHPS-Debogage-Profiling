# ============================================================
# Adding mcblas versions
# ============================================================
set(GOPTS -Wall -g)
set(LIBBASENAME "mcblas")

get_property(OPTIONS GLOBAL PROPERTY PROP_OPTIONS)
find_package(OpenMP REQUIRED)

foreach(OPT ${OPTIONS})
  set(VER "011")
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
  target_compile_options(${LIB} PRIVATE ${GOPTS} -${OPT} -march=native -mavx2 -mfma -fopenmp -fopt-info-vec-optimized)
  target_compile_options(${LIB} BEFORE INTERFACE ${GOPTS} -${OPT})
  target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
  target_link_libraries(${LIB} PUBLIC OpenMP::OpenMP_CXX)

endforeach()
