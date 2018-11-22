
## Hunter 学习笔记

    - [MD语法参考](https://www.jianshu.com/p/b03a8d7b1719)
  
-------------
### 基本用法
  - 生成项目
    >cmake -H. -B_builds
 
  - 编译项目 (默认 Debug)
    > cmake --build _builds
    > cmake --build _builds --config Debug

  - 编译 Release
    > cmake --build _builds --config Release
  
  - Run Test
    > cd _builds && ctest -C Debug -VV && cd ..
    > cd _builds && ctest -C Release -VV && cd ..
  - 指定库版本
    - [官方说明](https://github.com/ruslo/hunter/wiki/example.custom.config.id)
    - 方法
      1. 配置为LOCAL
      >HunterGate(
      URL "https://github.com/ruslo/hunter/archive/v0.23.57.tar.gz"
      SHA1 "8befbbaea51cb54681f6e690212ed753ae807529"
      **LOCAL** 
    )

      1. 实现${CMAKE_CURRENT_LIST_DIR}/cmake/Hunter/config.cmake
        > hunter_config(OpenSSL VERSION 1.0.2a)
        > hunter_package(Foo VERSION 2.0 CMAKE_ARGS FOO_WITH_BOO=OFF)