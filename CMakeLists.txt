#Would prefer to make this 3.1, as it makes C++ dialect selection automatic.
cmake_minimum_required (VERSION 3.9)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release
RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(DENSE_PATH "${CMAKE_SOURCE_DIR}/DENSE" CACHE FILEPATH "Path to the DENSE project")

if (NOT EXISTS ${DENSE_PATH}/CMakeLists.txt)
  message( FATAL_ERROR "Cannot find DENSE directory: make sure the git
  submodule was checked out or set the variable DENSE_PATH" )
endif (NOT EXISTS ${DENSE_PATH}/CMakeLists.txt)

project (StochSimMethods CXX C)

#add the DENSE library functions for building simulations
add_subdirectory(${DENSE_PATH} DENSE EXCLUDE_FROM_ALL)

#declare a few simulations to build for different models
DETERMINISTIC_SIMULATION(his2014_simulation ${CMAKE_CURRENT_SOURCE_DIR}/her_model_2014)
DETERMINISTIC_SIMULATION(bz_simulation2 ${CMAKE_CURRENT_SOURCE_DIR}/Belousov-Zhabotinksy)

#declare a main function to build using a particular model
SIMULATION(turing_simulation ${CMAKE_CURRENT_SOURCE_DIR}/Turing-Pattern custom_main.cpp)

#build just the simulation library, if you want to build something even more 
#  custom than a single-file main
SIMCORELIB(test_modellib ${CMAKE_CURRENT_SOURCE_DIR}/Nan_Test)
