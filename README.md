# `c-build`

## Why I build this?

Inspired by [tsoding's nobuild](https://github.com/tsoding/nobuild) and I want
to build my customized one.

</br>


# What `c-build` can offer

- Only `C` compiler needed for building your C project.

    Like `nobuild` mentioned:

    You should not need anything but a C compiler to build a C project. No
    `make`, no `cmake`, no `shell`, no `cmd`, no `PowerShell` etc. **Only C
    compiler**.

    If you love C, then use C to write your own building process, it's kind of
    fun and cool:)

    </br>

- Differences with `nobuild`

    - Improved color logging compared to `nobuild`

    </br>

    - Support user provided env var to override the default settings

    </br>

    - `CMD` support `char *` option, so you're able to do something like this:

        ```c
        char cmd[1024] = "";
        // ... Make up your command string in the way you like
        CMD(cmd);
        ```

        rather than like this:

        ```c
        #define C_COMPILER "CC"
        #define C_COMPILER "clang"
        #define C_FLAGS "-pedantic-errors", "-Wall", "-Wextra", "-Werror", "-std=c11"
        #define C_FLAGS_SANITIZER "-fsanitize=address", "-O1", "-fno-omit-frame-pointer"

        // `pkg-config --libs --cflags raylib`
        #define C_FLAGS_RAYLIB_COMPILING "-I/usr/local/include", "-D_THREAD_SAFE", "-pthread"
        #define C_FLAGS_RAYLIB_LINKING "-D_THREAD_SAFE", "-pthread", "-L/usr/local/lib", "-lraylib"

        CMD(C_COMPILER, C_FLAGS, C_FLAGS_SANITIZER, C_FLAGS_RAYLIB_COMPILING, EXTRA_C_FLAGS, "-o", obj_file, "-c", source_file);
        ```

        </br>

    - Only for `Linux` or `BSD` family, sorry, not for `windows`:)
