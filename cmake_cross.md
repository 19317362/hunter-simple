
## CMAKE CROSS COMPILE 笔记

    - [参考] (https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html)
    - [WIKI] (https://gitlab.kitware.com/cmake/community/wikis/home)
  
-------------
### 基本用法
  - osx alias in vim .bash_profile 
  - hunter_config(foo VERSION ${HUNTER_foo_VERSION} CMAKE_ARGS DUMMY=1)
  - set(TESTING_CONFIG_OPT FILEPATH ${CMAKE_CURRENT_LIST_DIR}/config.cmake) 
  - PROTOBUF https://github.com/ruslo/hunter/issues/494
  - HUNTER_KEEP_PACKAGE_SOURCES
  - CMAKE_STAGING_PREFIX
    > optional. It may be used to specify a path on the host to install to
 
  - CMAKE_FIND_ROOT_PATH
    >  find_package(), find_library()
    >  A;B;C

  - CMAKE_FIND_ROOT_PATH_MODE_INCLUDE
    > find_file() find_path()
    - NEVER  CMAKE_SYSROOT
    - ONLY  CMAKE_FIND_ROOT_PATH
    - BOTH  CMAKE_SYSROOT + CMAKE_FIND_ROOT_PATH
  
  - CMAKE_FIND_ROOT_PATH_MODE_LIBRARY
    > find_library().
    > NEVER ONLY BOTH

  - CMAKE_FIND_ROOT_PATH_MODE_PROGRAM
    - used by find_program().
    - NEVER ONLY BOTH
  
  - CMAKE_FIND_ROOT_PATH_MODE_PACKAGE
    - used by find_package()
    - NEVER ONLY BOTH

  - CMAKE_INSTALL_PREFIX
    - This variable may be set to a path to install to when cross-compiling
    - 
  - CMAKE_STAGING_PREFIX
    - If any RPATH/RUNPATH entries passed to the linker contain the CMAKE_STAGING_PREFIX, the matching path fragments are replaced with the CMAKE_INSTALL_PREFIX.
  
  - RPATH/RUNPATH 
    - CMAKE_BUILD_RPATH
    - CMAKE_INSTALL_RPATH
    - CMAKE_INSTALL_RPATH_USE_LINK_PATH
  
  - ARM example
    > set(CMAKE_SYSTEM_NAME Linux)
    > set(CMAKE_SYSTEM_PROCESSOR arm)
    > set(CMAKE_SYSROOT /home/devel/rasp-pi-rootfs)
    > set(CMAKE_STAGING_PREFIX /home/devel/stage)
    > set(tools /home/devel/gcc-4.7-linaro-rpi-gnueabihf)
    > set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc)
    > set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)
    > set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    > set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    > set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    > set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
  - COPY to some dir
      >  This is useful for one of them
      > SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
      > ${PROJECT_SOURCE_DIR}/lib CACHE
      > PATH "Directory where all the .lib files are dumped." FORCE)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_SOURCE_DIR}/bin CACHE
    PATH "Directory where .exe and .dll files are dumped." FORCE)

  - RPATH  with .so while crossing
    - https://stackoverflow.com/questions/30400362/cmake-cross-compile-target-rpath
    - https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/RPATH-handling
    - https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/recipe/InstallToALocalFolderForTesting
    - https://stackoverflow.com/questions/39075040/cmake-cmake-automoc-in-cross-compilation?rq=1
    -  [auto genereate cpp to test]https://stackoverflow.com/questions/43781207/how-to-cross-compile-with-cmake-arm-none-eabi-on-windows
    - copy (https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake) 
   
