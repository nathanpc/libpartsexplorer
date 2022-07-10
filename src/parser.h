/**
 * parser.h
 * Bunch of different parsers to cope with all of the different files inside
 * component archives.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _PARSER_H
#define _PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pecan.h"

// Attributes
pecan_err_t parse_attributes(pecan_archive_t *part, const char *contents);

#ifdef __cplusplus
}
#endif

#endif /* _PARSER_H */