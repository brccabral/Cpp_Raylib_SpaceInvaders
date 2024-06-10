#!/bin/bash

source $EMSDK/emsdk_env.sh

emcc -o space_invaders.html code/main.cpp code/alien.cpp code/block.cpp code/game.cpp code/laser.cpp code/mysteryship.cpp code/obstacle.cpp code/spaceship.cpp -Os -Wall $RAYLIB_INSTALL_PATH/lib/libraylib.a -I. -I$RAYLIB_INSTALL_PATH/include -L. -L$RAYLIB_INSTALL_PATH/lib -s USE_GLFW=3 -s ASYNCIFY --shell-file $RAYLIB_SRC_PATH/shell.html -DPLATFORM_WEB --preload-file resources/Font --preload-file resources/Graphics --preload-file resources/Sounds

# python -m http.server 8080
