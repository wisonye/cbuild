#define C_BUILD_IMPLEMENTATION
#include "../../cbuild.h"

///
///
///
int main(int argc, char **argv) {
    CB_setup_build_folder();
    CB_setup_compiler();

    // CB_compile_all("test.c", NULL);
    CB_compile_and_build_executable("main_test", "test.c", NULL);
}
