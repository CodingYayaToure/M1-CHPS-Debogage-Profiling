
# Works with 3.15 and tested through 3.21
cmake_minimum_required(VERSION 3.15...3.25)

# Project name and a few useful settings. Other commands can pick up the results
project(
  mcblas
  VERSION 0.1
  DESCRIPTION "MCBLAS Performance library"
  LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD,
  # CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDE's
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app. Note this needs to be done
  # in the main CMakeLists since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # # Docs only available if this is the main app
  # find_package(Doxygen)
  # if(Doxygen_FOUND)
  #   add_subdirectory(docs)
  # else()
  #   message(STATUS "Doxygen not found, not building docs")
  # endif()
endif()

# # Accumulator library This is header only, so could be replaced with git
# # submodules or FetchContent
# find_package(Boost REQUIRED)
# # Adds Boost::boost / Boost::headers (newer FindBoost / BoostConfig 3.15 name)

# set(VERSIONS "001" "002" "003")
#set(VERSIONS "001" "002" "003")
#set_property(GLOBAL PROPERTY PROP_VERSIONS "001" "002" "003" "004" "005" "006" "007" "008" "009")
#set_property(GLOBAL PROPERTY PROP_VERSIONS "009")
#set_property(GLOBAL PROPERTY PROP_OPTIONS "O2")
set_property(GLOBAL PROPERTY PROP_VERSIONS "001" "002" "007" "008" "009" "010")
set_property(GLOBAL PROPERTY PROP_OPTIONS "O2" "O3")

get_property(VERSIONS GLOBAL PROPERTY PROP_VERSIONS)

# The compiled library code is here
foreach(VER ${VERSIONS})
  add_subdirectory(mcblas${VER})
endforeach()
# The executable code is here
# add_subdirectory(tests)

# Testing only available if this is the main app
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
