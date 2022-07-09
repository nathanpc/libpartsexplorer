/**
 * partsexplorer.c
 * The helper library to deal with your electronic components definitions.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "partsexplorer.h"
#include <stdio.h>
#include <string.h>
#include <cvector.h>
#include <microtar.h>

// A simple test of our build setup.
int pe_test(void) {
    mtar_t tar;
    const char *str1 = "Hello world";
    const char *str2 = "Goodbye world";

    mtar_open(&tar, "~/dev/parts-explorer/example/example.tar", "w");

    /* Write strings to files `test1.txt` and `test2.txt` */
    mtar_write_file_header(&tar, "test1.txt", strlen(str1));
    mtar_write_data(&tar, str1, strlen(str1));
    mtar_write_file_header(&tar, "test2.txt", strlen(str2));
    mtar_write_data(&tar, str2, strlen(str2));

    /* Finalize -- this needs to be the last thing done before closing */
    mtar_finalize(&tar);

    /* Close archive */
    mtar_close(&tar);

    return 42;
}
