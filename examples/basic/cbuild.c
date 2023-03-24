#define C_BUILD_IMPLEMENTATION
#include "../../cbuild.h"

///
///
///
int main(int argc, char **argv) {
    CB_setup_build_folder();
    CB_setup_compiler();

    const char *source_files[] = {
        "src/utils.c", "src/ball.c", "src/player.c", "src/scoreboard.c",
        "src/table.c", "src/game.c", "src/main.c",
    };
    size_t source_files_arr_len = sizeof(source_files) / sizeof(char *);

    CB_compile_all("src/ball.c", "src/player.c", "src/scoreboard.c",
                   "src/table.c", "src/game.c", "src/main.c", NULL);

    // const char *ls_cmd[] = {"ls", "-lht", "-st", "/Users/wison/Downloads/",
    //                         NULL};
    // CB_exec(ls_cmd[0], ls_cmd);

    // const char *compile_cmd[] = {"/usr/bin/cc",
    //                              "-o",
    //                              "temp_build/my-game ",
    //                              "-D_THREAD_SAFE",
    //                              "-pthread",
    //                              "-L/usr/local/lib",
    //                              "-lraylib",
    //                              "temp_build/main.c.o",
    //                              "temp_build/game.c.o",
    //                              "temp_build/table.c.o",
    //                              "temp_build/scoreboard.c.o",
    //                              "temp_build/player.c.o",
    //                              "temp_build/ball.c.o",
    //                              NULL};
    // CB_exec(compile_cmd[0], compile_cmd);
}
