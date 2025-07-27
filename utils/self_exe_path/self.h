#ifndef _SELF_H
#define _SELF_H

/** get the current executing executable's absolute file path.
 *
 *  On success, the legnth of buf is returned and buf is filled with the current executing executable's absolute file path.
 *  On error, -1 is returned and errno is set to indicate the error.
 */
int selfpath(char buf[]);

#endif
