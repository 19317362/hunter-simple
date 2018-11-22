# Copyright (c) 2014-2016, Ruslan Baratov
# All rights reserved.

cmake_minimum_required(VERSION 3.2)

### Hunter snapshot that will be used ###
include("cmake/HunterGate.cmake")
HunterGate(
  URL "https://github.com/ruslo/hunter/archive/v0.23.57.tar.gz"
  SHA1 "8befbbaea51cb54681f6e690212ed753ae807529"
  LOCAL # <----- Use local config.cmake
         # ${CMAKE_CURRENT_LIST_DIR}/cmake/Hunter/config.cmake
)
project(HunterSimple)

### Download dependencies ###
hunter_add_package(GTest)
hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)
### Find dependencies ###
find_package(GTest CONFIG REQUIRED) # GTest::main

### Targets ###
add_executable(simple simple.cpp)
target_link_libraries(simple PUBLIC GTest::main OpenSSL::SSL OpenSSL::Crypto)

### Testing ###
enable_testing()

if(IOS)
  # Extra cmake modules needed for iOS testing:
  # * https://github.com/ruslo/sugar/tree/master/cmake/core#sugar_add_ios_gtest
  add_test(
      NAME SimpleTest COMMAND "${CMAKE_COMMAND}" -E echo "iOS testing ignored"
  )
elseif(ANDROID)
  # Building .apk, testing: https://github.com/forexample/android-cmake
  add_test(
      NAME SimpleTest
      COMMAND "${CMAKE_COMMAND}" -E echo "Android testing ignored"
  )
else()
  add_test(NAME SimpleTest COMMAND simple)
endif()
