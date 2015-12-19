cmake_minimum_required(VERSION 3.0)

function(ForceBuildDir)
  if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
    message("######################################################")
    message("# Run cmake in a build directory:")
    message("#")
    message("# rm -rf CMakeFiles/ cmake_install.cmake CMakeCache.txt")
    message("# mkdir build")
    message("# cd build")
    message("# cmake ..")
    message("#")
    message("######################################################")
    message(FATAL_ERROR "Quitting configuration")
  endif()
endfunction()

ForceBuildDir()

project(Server)
find_package(
  Boost 1.59.0 REQUIRED
  date_time
  system
  filesystem
  thread
  coroutine
  )

# find_package(
#   Openssl REQUIRED
#   )

include_directories(
  includes
  ../common/includes
  )

file(
  GLOB_RECURSE
  source_files
  src/*
  includes/*
  ../common/src/*
  ../common/includes/*
  )

file(
  COPY ./ressources
  DESTINATION ${CMAKE_BINARY_DIR}
  )

add_executable(
  server
  ${source_files}
  )

add_definitions(
  -std=c++11
  -DCERTIFICATE_FILE=\"ressources/server.crt\"
  -DPRIVATE_KEY_FILE=\"ressources/server.key\"
  -DDH_FILE=\"ressources/dh1024.pem\"
  -DDEBUG
  )

target_link_libraries(
  server
  ${Boost_LIBRARIES}
  ssl
  dl
  crypto
  )
