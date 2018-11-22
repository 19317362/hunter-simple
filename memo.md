
## Hunter 学习笔记

### 基本用法
  - cmake -H. -B_builds
    - 生成项目
  - cmake --build _builds
    - 编译项目
    - 默认 Debug
  - cmake --build _builds --config Release
    - 编译 Release
  - cmake --build _builds --config Debug
    - 编译 Debug
  - Test
    - cd _builds && ctest -C Debug -VV && cd ..
    - cd _builds && ctest -C Release -VV && cd ..