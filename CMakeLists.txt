cmake_minimum_required(VERSION 3.20)
project(SpaceInvaders)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} code/main.cpp
        code/spaceship.cpp
        code/game.cpp
        code/laser.cpp
        code/block.cpp
        code/obstacle.cpp
        code/alien.cpp
        code/mysteryship.cpp)
target_link_libraries(${PROJECT_NAME} raylib)
install(TARGETS ${PROJECT_NAME})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} gdi32 winmm)
    set(COMPILE_FLAGS "/NODEFAULTLIB:libcmt")
endif ()

if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .html)
    target_link_options(${PROJECT_NAME}
                        PRIVATE
                        -sALLOW_MEMORY_GROWTH=1
                        -sUSE_GLFW=3
                        -sEXPORTED_RUNTIME_METHODS=[requestFullscreen]
                        --preload-file resources
                        --shell-file $ENV{EMSCRIPTEN}/src/shell_brc.html
    )
endif ()

# copy resources to Build folder for debugging
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# copy resources to Install location
install(DIRECTORY
        ${PROJECT_SOURCE_DIR}/resources
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}
)
