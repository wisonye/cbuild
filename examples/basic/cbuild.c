#define C_BUILD_IMPLEMENTATION
#include "../../cbuild.h"

///
///
///
int main(int argc, char **argv) {
    setup_builder_folder();
    setup_compiler();

    const char *source_files[] = {
        "src/utils.c", "src/ball.c", "src/player.c", "src/scoreboard.c",
        "src/table.c", "src/game.c", "src/main.c",
    };
    size_t source_files_arr_len = sizeof(source_files) / sizeof(char *);

    CBuild_compile_all("src/utils.c", "src/ball.c", "src/player.c",
                       "src/scoreboard.c", "src/table.c", "src/game.c",
                       "src/main.c", NULL);
}
