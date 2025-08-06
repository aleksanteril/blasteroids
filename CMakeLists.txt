cmake_minimum_required(VERSION 3.10.0)
project(blasteroids)

set(SOURCES src/ship.c src/asteroid.c src/blast.c src/blasteroids.c src/utilities.c src/core.c)

add_executable(blasteroids ${SOURCES})
target_link_libraries(blasteroids allegro allegro_color allegro_primitives)
