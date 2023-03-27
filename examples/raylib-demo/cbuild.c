#include <stdio.h>

#define EXTRA_COMPILE_FLAGS "-I/usr/local/Cellar/raylib/4.2.0/include"
#define EXTRA_LINK_FLAGS "-L/usr/local/Cellar/raylib/4.2.0/lib", "-lraylib"

#define C_BUILD_IMPLEMENTATION

#include "../../cbuild.h"

///
///
///
int main(int argc, char **argv) {
    CB_setup_build_folder();
    CB_setup_compiler();

    CB_compile_and_build_executable("src/game.c", "src/main.c", NULL);
}
