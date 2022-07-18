/**
 * error.h
 * Handles the internal error state of the library.
 *
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _ERROR_H
#define _ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

// Decorate the error message with more information.
#ifdef DEBUG
#	define STRINGIZE(x) STRINGIZE_WRAPPER(x)
#	define STRINGIZE_WRAPPER(x) #x
#	define EMSG(msg) msg " [" __FILE__ ":" STRINGIZE(__LINE__) "]"
#else
#	define EMSG(msg) msg
#endif /* DEBUG */

// Operations
void err_init(void);
void err_set_msg(const char *msg);
void err_free(void);

// Inspections
const char *err_get_msg(void);
void err_print_msg(void);

#ifdef __cplusplus
}
#endif

#endif /* _ERROR_H */
