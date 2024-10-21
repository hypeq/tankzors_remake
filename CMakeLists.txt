cmake_minimum_required(VERSION 3.1)

project(tankzors C)

find_package(PkgConfig REQUIRED)

pkg_search_module(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_search_module(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)
pkg_search_module(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
pkg_search_module(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)

aux_source_directory(./src SOURCES)


add_executable(tankzors ${SOURCES})

target_link_directories(tankzors PRIVATE
                        ${SDL2_LIBRARY_DIRS}
                        ${SDL2_TTF_LIBRARY_DIRS}
                        ${SDL2_IMAGE_LIBRARY_DIRS}
                        ${SDL2_MIXER_LIBRARY_DIRS}
                        )
                        
target_compile_options(tankzors PRIVATE -std=c99 -O2 -Wall -Wextra -Wshadow -Wshadow -Wvla -Wpointer-arith -Walloca -Wduplicated-cond -Wtrampolines -Wlarger-than=1048576 -Wframe-larger-than=32768 -Wdouble-promotion -Werror=return-type -Wno-unknown-warning-option)



set_target_properties(tankzors PROPERTIES LINK_FLAGS_RELEASE -s)

target_link_libraries(tankzors 
                          ${SDL2_LIBRARIES}
                          ${SDL2_TTF_LIBRARIES}
                          ${SDL2_IMAGE_LIBRARIES}
                          ${SDL2_MIXER_LIBRARIES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
