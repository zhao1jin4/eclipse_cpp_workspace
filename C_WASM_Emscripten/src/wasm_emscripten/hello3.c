
#include <stdio.h>
#include <emscripten/emscripten.h>

int main()
{
    printf("Hello World\n");
}

#ifdef __cplusplus
extern "C"
{
#endif

    EMSCRIPTEN_KEEPALIVE void myFunction(int argc, char **argv)
    {
        printf("MyFunction Called\n");
    }

#ifdef __cplusplus
}
#endif

// emcc -o hello.html hello.c -O3 -s WASM=1 --shell-file shell_minimal.html

