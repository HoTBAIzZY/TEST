cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE /home/zzy/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(test)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

#find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(test
    src/main.cpp
    src/snake.cpp)

#target_link_libraries(test
#    PRIVATE
#    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
 #   $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
#)


# 链接 SDL2 及其扩展库到你的可执行文件  
target_link_libraries(test PRIVATE SDL2::SDL2) 