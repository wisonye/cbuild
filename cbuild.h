#ifndef __C_BUILD_H__
#define __C_BUILD_H__

#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

///
/// Log related
///
void CB_info(const char *prefix, const char *fmt, ...);
void CB_warn(const char *prefix, const char *fmt, ...);
void CB_error(const char *prefix, const char *fmt, ...);
void CB_panic(const char *prefix, const char *fmt, ...);

///
/// Folder related
///
bool CB_folder_exists(const char *folder);
void CB_delete_folder(const char *folder);
void CB_create_folder(const char *folder);

///
/// Command related
///
bool CB_exec(const char *cmd, const char *args[]);
// bool CB_exec2(const char *cmd, ...);

///
/// Setup related
///
void CB_setup_builder_folder(void);
void CB_setup_compiler(void);

///
/// Compile the give source files, file list have to end with `NULL`!!!
///
void CB_compile_all(const char *source_file, ...);

///
/// Link all compiled object files and generate the givne executable
///
void CB_build_executable(const char *output_file);
#endif

#ifdef C_BUILD_IMPLEMENTATION

///
/// C compiler flags
///
/// `-I<dir>`: Add directory to the end of the list of include search paths
///
/// `-L<dir>`: Add directory to library search path
///
/// `-llibrary`: Specify a function library to be used at `link` time. The rule
///              is that if the library is called `libsomething.a`, you give
///              `cc` the argument `-lsomething`(without `lib` and extension
///              part).
///
///              For example, the `math` library is `libm.a`, so you give `cc`
///              the argument `-lm`.
///
/// `-pedantic-errors`: Error on language extensions. It requests to produce an
///                     error if a feature from a later standard revision is
///                     used in an earlier mode.
///
///                     For example if you use `-std=c99` standard to compile
///                     your code, but you use `_Generic` which only supported
///                     from `C11`, then `clang` will stop on that error.
///
///                     This is very good for you to know which C standard you
///                     should use or forbidden some features in your code.
///
/// `-Wall`: Enable all the warnings which the authors of `cc` believe are
///          worthwhile.
///
/// `-Wextra`: Cover extra warnings
///
/// `-Werror`: Treat warngins are errors!!!
///
/// All supported warnning options is here:
/// https://releases.llvm.org/15.0.0/tools/clang/docs/DiagnosticsReference.html
///
#define DEFAULT_C_COMPILER "cc"

#define DEFAULT_C_FLAGS \
    "-pedantic-errors", "-Wall", "-Werror", "-Wextra", "-std=c11", "-g"
#define DEFAULT_C_FLAGS_RELEASE                                           \
    "-pedantic-errors", "-Wall", "-Werror", "-Wextra", "-std=c11", "-O3", \
        "-DNDEBUG"

#define DEFAULT_C_FLAGS_SANITIZER                                        \
    "-pedantic-errors", "-Wall", "-Werror", "-Wextra", "-std=c11", "-g", \
        "-fsanitize=address", "-O1", "-fno-omit-frame-pointer"
#define DEFAULT_C_FLAGS_SANITIZER_RELEASE                                 \
    "-pedantic-errors", "-Wall", "-Werror", "-Wextra", "-std=c11", "-O3", \
        "-DNDEBUG", "-fsanitize=address", "-O1", "-fno-omit-frame-pointer"

///
/// Log related
///
#define LOG_COLOR_GREEN "\033[1;32m"
#define LOG_COLOR_YELLOW "\033[1;33m"
#define LOG_COLOR_RED "\033[1;31m"
#define LOG_COLOR_DEFAULT "\033[1;32m"
#define LOG_COLOR_PURPLE "\033[1;35m"
#define LOG_COLOR_RESET "\033[0m"

void CB_log(FILE *fd, const char *color, const char *prefix, const char *fmt,
            va_list args) {
    // fprintf(fd, ">>> %s[ %s ] %s- ", color, prefix, LOG_COLOR_RESET);
    fprintf(fd, "%s[ %s ] %s- ", color, prefix, LOG_COLOR_RESET);
    vfprintf(fd, fmt, args);
    fprintf(fd, "\n");
}

void CB_info(const char *prefix, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    CB_log(stdout, LOG_COLOR_GREEN, prefix, fmt, args);
    va_end(args);
}
void CB_warn(const char *prefix, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    CB_log(stdout, LOG_COLOR_YELLOW, prefix, fmt, args);
    va_end(args);
}

void CB_error(const char *prefix, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    CB_log(stdout, LOG_COLOR_RED, prefix, fmt, args);
    va_end(args);
}

void CB_panic(const char *prefix, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    CB_log(stdout, LOG_COLOR_PURPLE, prefix, fmt, args);
    va_end(args);
    exit(1);
}

///
/// Folder related
///
bool CB_folder_exists(const char *folder) { return false; }
void CB_delete_folder(const char *folder) {}
void CB_create_folder(const char *folder) {}

///
/// Command related
///
bool CB_exec(const char *cmd, const char *args[]) {
    char cmd_info[1024] = {0};
    size_t index = 0;
    int bytes_written = 0;
    char *next_str = (char *)args[index];
    while (next_str != NULL) {
        bytes_written +=
            snprintf(cmd_info + bytes_written, sizeof(cmd_info) - bytes_written,
                     "%s ", next_str);

        index++;
        next_str = (char *)args[index];
    }

    CB_info("EXEC", "%s", cmd_info);

    if (execvp(cmd, (char *const *)args) < 0) {
        CB_panic("CB_exec", "Fail to run child process: '%s' with error: %s",
                 cmd, strerror(errno));
        return false;
    }
    // execvp(const char *file, char *const argv[]);
    return true;
}

// bool CB_exec2(const char *cmd, ...) {
//     // execlp(const char *file, const char *arg0, ... /*, (char *)0 */);
//     va_list args;
//     // va_start(args, cmd);
//     if (execlp(cmd, cmd, args) < 0) {
//         CB_panic("CB_exec2", "Fail to run child process: '%s' with error:
//         %s",
//                  cmd, strerror(errno));
//         return false;
//     }
//     va_end(args);
//     return true;
// }

///
/// Print `...` (',' separated list) into `out_buffer`
///
void join_args(char *out_buffer, size_t buffer_size, ...) {
    va_list args;
    va_start(args, buffer_size);

    size_t index = 0;
    int bytes_written = 0;
    char *next_flag = (char *)va_arg(args, char *);
    while (next_flag != NULL) {
        bytes_written +=
            snprintf(out_buffer + bytes_written, buffer_size - bytes_written,
                     "%s ", next_flag);
        // printf("\n----bytes_written: %lu, out_buffer: %s", bytes_written,
        //        out_buffer);

        index++;
        next_flag = (char *)va_arg(args, char *);
    }
    out_buffer[bytes_written] = '\0';
    va_end(args);
}

///
///
///
static char BUILD_FOLDER[255] = {0};
static char NO_CACHE = false;

void CB_setup_build_folder(void) {
    const char *build_folder = getenv("BUILD_FOLDER");
    snprintf(BUILD_FOLDER, sizeof(BUILD_FOLDER), "%s/",
             build_folder != NULL ? build_folder : "build");

    const char *no_cache = getenv("NO_CACHE");
    if (no_cache != NULL &&
        (strcmp(no_cache, "true") == 0 || strcmp(no_cache, "TRUE") == 0)) {
        NO_CACHE = true;
    }

    // Create folder it not exists
    if (!CB_folder_exists(BUILD_FOLDER)) {
        CB_create_folder(BUILD_FOLDER);
        CB_info("BUILD_FOLDER", "Created build folder: %s",
                BUILD_FOLDER);
    }
    // Clean build
    else if (NO_CACHE) {
        CB_delete_folder(BUILD_FOLDER);
        CB_create_folder(BUILD_FOLDER);
        CB_info("BUILD_FOLDER",
                "NO_CACHE = true, re-created build folder: %s", BUILD_FOLDER);
    }
}

///
///
///
static bool already_setup_c_compiler = false;
static char C_COMPILER[255] = {0};
static char RELEASE_BUILD = false;

void CB_setup_compiler(void) {
    // Make sure only call once.
    if (already_setup_c_compiler) return;

    const char *c_compiler = getenv("C_COMPILER");
    snprintf(C_COMPILER, sizeof(C_COMPILER), "%s",
             c_compiler != NULL ? c_compiler : DEFAULT_C_COMPILER);

    const char *release_build = getenv("RELEASE_BUILD");
    if (release_build != NULL && (strcmp(release_build, "true") == 0 ||
                                  strcmp(release_build, "TRUE") == 0)) {
        RELEASE_BUILD = true;
    }

    char c_flags[255] = {0};
    if (RELEASE_BUILD) {
        join_args(c_flags, sizeof(c_flags), DEFAULT_C_FLAGS_RELEASE, NULL);
    } else {
        join_args(c_flags, sizeof(c_flags), DEFAULT_C_FLAGS, NULL);
    }
    snprintf(c_flags, sizeof(c_flags), "%s", c_flags);

    // print_memory_block("byte[]", sizeof(c_flags), c_flags);

    CB_info("COMPILER", "C_COMPILER: %s", C_COMPILER);
    CB_info("COMPILER", "C_FLAGS: %s", c_flags);
    CB_info("COMPILER", "RELEASE_BUILD: %s",
            RELEASE_BUILD ? "Yes" : "No");

    already_setup_c_compiler = true;
}

///
///
///
void CB_compile_all(const char *source_file, ...) {
    va_list args;
    va_start(args, source_file);
    // CB_info("COMPILE_ALL", "Compiling: %s", source_file);

    if (RELEASE_BUILD) {
        const char *cc_cmd[] = {C_COMPILER, DEFAULT_C_FLAGS_RELEASE, "-c",
                                source_file, NULL};
        CB_exec(cc_cmd[0], cc_cmd);
    } else {
        const char *cc_cmd[] = {C_COMPILER, DEFAULT_C_FLAGS, "-c", source_file,
                                NULL};
        CB_exec(cc_cmd[0], cc_cmd);
    }

    char *next_source_file = va_arg(args, char *);
    while (next_source_file != NULL) {
        // CB_info("COMPILE_ALL", "Compiling: %s", next_source_file);
        next_source_file = va_arg(args, char *);
    }
    va_end(args);
}

#endif
