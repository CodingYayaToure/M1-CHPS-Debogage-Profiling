
cmake_minimum_required(VERSION 3.15...3.25)

project(
  mcblas
  VERSION 0.1
  DESCRIPTION "MCBLAS Performance library"
  LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(CTest)
endif()

#set_property(GLOBAL PROPERTY PROP_VERSIONS "001" "002" "003" "004" "005" "006" "007" "008" "009" "010" "011")
#set_property(GLOBAL PROPERTY PROP_VERSIONS "009")
#set_property(GLOBAL PROPERTY PROP_OPTIONS "O2")
#set_property(GLOBAL PROPERTY PROP_VERSIONS "001" "002" "007" "008" "009")
#set_property(GLOBAL PROPERTY PROP_VERSIONS "001" "002" "006" "007" "008" "009")
set_property(GLOBAL PROPERTY PROP_VERSIONS "001" "002" "003" "004" "005" "006" "007" "008" "009" "010" "011")
set_property(GLOBAL PROPERTY PROP_OPTIONS "O2" "O3")

get_property(VERSIONS GLOBAL PROPERTY PROP_VERSIONS)

foreach(VER ${VERSIONS})
  add_subdirectory(mcblas${VER})
endforeach()

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

# ============================================================
# GUI : generation des graphiques et dashboard HTML
# ============================================================
find_program(PYTHON3 python3)
find_program(GPP g++)

if(PYTHON3 AND GPP)
  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/plot_results
    COMMAND ${GPP} -O2 -o ${CMAKE_BINARY_DIR}/plot_results
            ${CMAKE_SOURCE_DIR}/tools/plot_results.cpp
    DEPENDS ${CMAKE_SOURCE_DIR}/tools/plot_results.cpp
    COMMENT "Compilation de plot_results"
  )
  add_custom_target(plot_results_bin DEPENDS ${CMAKE_BINARY_DIR}/plot_results)

  add_custom_target(GUI
    COMMAND ${CMAKE_BINARY_DIR}/plot_results
            ${CMAKE_BINARY_DIR}/tests/runs/data/grall.data
            ${CMAKE_BINARY_DIR}/tests/runs/graphs
    COMMAND ${PYTHON3}
            ${CMAKE_SOURCE_DIR}/tools/generate_dashboard.py
            ${CMAKE_BINARY_DIR}/tests/runs/data/grall.data
            ${CMAKE_BINARY_DIR}/tests/runs/graphs/dashboard.html
    COMMAND xdg-open ${CMAKE_BINARY_DIR}/tests/runs/graphs/dashboard.html
    COMMAND xdg-open ${CMAKE_BINARY_DIR}/tests/runs/graphs/plot_overview.pdf
    COMMAND xdg-open ${CMAKE_BINARY_DIR}/tests/runs/graphs/plot_zoom.pdf
    COMMAND xdg-open ${CMAKE_BINARY_DIR}/tests/runs/graphs/plot_gains.pdf
    COMMAND xdg-open ${CMAKE_BINARY_DIR}/tests/runs/graphs/plot_o2vso3.pdf
    DEPENDS plot_results_bin GALL
    COMMENT "Generation des graphiques et du dashboard HTML"
  )
endif()