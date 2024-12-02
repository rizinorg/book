#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This is simple hello_world program made for education purposes.
 * Licensed under CC-BY-SA 4.0 license.
 *
 * In order to compile executable run:
 *
 * gcc -o hello_world hello_world.c
 *
 */

int main(int argc, char* argv[])
{
    const char *str1 = "Hello ";
    const char *str2 = "world!";

    size_t str1_size = strlen(str1);
    size_t str2_size = strlen(str2);

    char *output = malloc(str1_size + str2_size + 1);
    if (output)
    {
        strcpy(output, str1);
        strcat(output, str2);

        puts(output);
        free(output);
    }

    return 0;
}
