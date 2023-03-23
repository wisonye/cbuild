# `cbuild`

### What is it and what it can offer to you

Inspired by [tsoding's nobuild](https://github.com/tsoding/nobuild) and
has been improved.

Easy to understand and use, with no extra configuration syntax (or
language) you need to learn, only C, the one you're super familiar with:)

Here is what `cbuild` can offer to you:

- Only `C` compiler needed for building your C project.

    You don't need to install the extra tools like `make`, `cmake` or anything
    you named it. **Only C compiler needed**.

    If you love C, then just write your own building process by using your
    favorite programming language, it's kind of fun and cool:)

- Improved color logging.

- Support user provided env var to override the default settings.

- Cover different function naming habits.

    So the following function calls are the same, just pick the one you
    preferred:

    - `CBuild_exec_command`
    - `CBuildExecCommand`
    - `CB_exec_command`
    - `CBExecCommand`

    </br>

- Single `cbuild.h` to cover all you need, nothing else.

### Limitation

Only work for `Linux` or `BSD` family at this moment, tested on `Linux/MacOS/FreeBSD`.

</br>

### Usage by examples

#### Basic

- Create `cbuild.c` and include `cbuild.h` and write your own build process

    ```c
    #define C_BUILD_IMPLEMENTATION
    #include "cbuild.h"

    char cmd[] = "cc -pedantic-errors -Wall -Wextra -Werror -std=c11 -o main src/main.c";
    CBuild_exec_command(cmd);

    INFO(">>>");
    INFO(">>> Project has been built successfully.");
    INFO(">>>");
    ```

    </br>

- Compile `cbuild.c` and then use it to compile your project:

    ```bash
    cc -o cbuild cbuild.c && ./cbuild
    ```

    </br>


#### Support configurable env var

- Create `cbuild.c` and include `cbuild.h` and write your own build process

    See the `examples/env.c`

    Here are the default env values if you don't provide them:

    | Env var | Default value |
    | ------- | ------------- |
    | C_COMPILER | `cc` |
    | RELEASE_BUILD | `false` and `-g` applied<br><br>When `true`, the following settings applied:<br>`-O3 -DNDEBUG`|
    | EXECUTABLE | `main` |
    | BUILD_FOLDER | `build`, folder will be created if not exists |
    | NO_CACHE | `false`<br><br>When `true`, it removes the entire `BUILD_FOLDER` (includes the previous built object files) and run a clean build |

    </br>

    Also, here is the default `C_FALGS`, feel free to change to what you needed:

    ```c
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
    ```

    </br>


- Compile `cbuild.c` and then use it to compile your project and run it:

    ```bash
    #!/bin/sh

    # C_COMPILER=$(which clang)
    C_COMPILER=$(which cc)
    EXECUTABLE="my_program"
    BUILD_FOLDER="temp_build"
    NO_CACHE=true

    #
    # Compile `cbuild.c` and then use it to compile the project
    #
    ${C_COMPILER} -o cbuild -g cbuild.c \
        && \
        C_COMPILER=${C_COMPILER} \
        BUILD_FOLDER=${BUILD_FOLDER} \
        NO_CACHE=${NO_CACHE} ./cbuild \
        && \
        ${BUILD_FOLDER}/${EXECUTABLE}
    ```

    </br>


