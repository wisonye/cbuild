#define C_BUILD_IMPLEMENTATION
#include "../../cbuild.h"

///
///
///
int main(int argc, char **argv) {
    CB_setup_build_folder();
    CB_setup_compiler();

    // CB_compile_all("test.c", NULL);
    const char *executable = "main_test";
    CB_compile_and_build_executable(executable, "test.c", NULL);
}
