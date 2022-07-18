/**
 * fileutils.h
 * Some utility functions to help us with files and paths.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _FILEUTILS_H
#define _FILEUTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

// Checking.
bool is_dir(const char *path);
bool file_exists(const char *fpath);
bool file_ext_match(const char *fpath, const char *ext);

// Path manipulaton.
size_t cleanup_path(char *path);
size_t pathcat(int npaths, char **buf, ...);
char *extcat(const char *fpath, const char *ext);

// File content.
size_t file_contents_size(const char *fname);
char* slurp_file(const char *fname);

#ifdef __cplusplus
}
#endif

#endif /* _FILEUTILS_H */