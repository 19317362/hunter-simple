# Copyright (c) 2014-2016, Ruslan Baratov
# All rights reserved.

cmake_minimum_required(VERSION 3.2)

option(HUNTER_BUILD_SHARED_LIBS "Print a lot of info" ON) # Good

# https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
# SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
#     ${PROJECT_SOURCE_DIR}/pub CACHE
#     PATH "Directory where all the .lib files are dumped." FORCE)
# SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY
#     ${PROJECT_SOURCE_DIR}/pub CACHE
#     PATH "Directory where .exe and .dll files are dumped." FORCE)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# install(FILES $<TARGET_FILE:OpenAL::OpenAL> DESTINATION lib)

# install(
#     FILES
#     $<TARGET_FILE:OpenSSL::Crypto>
#     $<TARGET_FILE:ZLIB::zlib>
#     DESTINATION
#     lib
# )
### Hunter snapshot that will be used ###
include("cmake/HunterGate.cmake")
HunterGate(
  URL "https://github.com/ruslo/hunter/archive/v0.23.161.tar.gz"
  SHA1 "714a57df86883ae726f3a0572bf6b74a2f7000c0"
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

hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)

### Targets ###
add_executable(simple simple.cpp)
target_link_libraries(simple PUBLIC
Boost::boost
GTest::main OpenSSL::SSL OpenSSL::Crypto)

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

