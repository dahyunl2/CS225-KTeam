# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# src_sources at src/CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225/225_project/CS225-KTeam/src/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225/225_project/CS225-KTeam/src/Flight.cpp"
  "/workspaces/cs225/225_project/CS225-KTeam/src/airport.cpp"
  "/workspaces/cs225/225_project/CS225-KTeam/src/djikstras.cpp"
  "/workspaces/cs225/225_project/CS225-KTeam/src/graph.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225/225_project/CS225-KTeam/build/CMakeFiles/cmake.verify_globs")
endif()

# tests_src at CMakeLists.txt:131 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225/225_project/CS225-KTeam/tests/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225/225_project/CS225-KTeam/tests/test.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225/225_project/CS225-KTeam/build/CMakeFiles/cmake.verify_globs")
endif()
