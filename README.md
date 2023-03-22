# `c-build`

## 1. Why I build this?

Inspired by [tsoding's nobuild](https://github.com/tsoding/nobuild) and I want
to build my customized one.

</br>


## 2. What `c-build` can offer

#### 2.1 Only `C` compiler needed for building your C project.

Like `nobuild` mentioned:

You should not need anything but a C compiler to build a C project. No
`make`, no `cmake`, no `shell`, no `cmd`, no `PowerShell` etc. **Only C
compiler**.

If you love C, then use C to write your own building process, it's kind of
fun and cool:)

</br>

#### 2.2. Differences with `nobuild`

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


    </br>

### 3. Usage by examples

#### 3.1 Basic

- Create `c-build.c` and include `c-build.h` and write your own build process

    ```c
    #include "c-build.h"

    char cmd[] = "cc -pedantic-errors -Wall -Wextra -Werror -std=c11 -o main src/main.c";
    CMD(cmd);

    INFO(">>>");
    INFO(">>> Project has been built successfully.");
    INFO(">>>");
    ```

    </br>

- Compile `c-build.c` and then use it to compile the project:

    ```bash
    ${C_COMPILER} -o c-build c-build.c && \
        ENABLE_SANITIZER=true \
        C_COMPILER=${C_COMPILER} \
        BUILD_FOLDER=${BUILD_FOLDER} \
        ./c-build && \
        ${BUILD_FOLDER}/${EXECUTABLE}
    ```

    </br>


#### 3.2 Support configurable env var

- Create `c-build.c` and include `c-build.h` and write your own build process

    See the `examples/env.c`

    </br>

- Compile `c-build.c` and then use it to compile the project and run it:

    ```bash
    #!/bin/sh

    C_COMPILER=$(which clang)
    # C_COMPILER=$(which cc)
    EXECUTABLE="my-program"
    BUILD_FOLDER="temp_build"

    ${C_COMPILER} -o c-build c-build.c && \
        ENABLE_SANITIZER=true \
        C_COMPILER=${C_COMPILER} \
        BUILD_FOLDER=${BUILD_FOLDER} \
        ./c-build && \
        ${BUILD_FOLDER}/${EXECUTABLE}
    ```

    </br>


