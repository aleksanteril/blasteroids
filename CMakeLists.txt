cmake_minimum_required(VERSION 3.10.0)
project(blasteroids)


add_executable(blasteroids blasteroids.c)
target_link_libraries(blasteroids allegro)
