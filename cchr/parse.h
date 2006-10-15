#ifndef _ufa_parse_h_
#define _ufa_parse_h_

#include <stdio.h>

#define MAXLINELEN 4096

#define READ_EOF  0 /* end-of-file */
#define READ_EOL  1 /* end-of-line */
#define READ_EOB  2 /* end-of-block */
#define READ_EOLS 3 /* end-of-line, subblock starts */
#define READ_EEOF 4 /* unexpected end of file */
#define READ_BUFF 5 /* buffer overflow */
#define READ_CHAR 6 /* weird character */
#define READ_BRAC 7 /* brackets out of balance */

int lread(char*,FILE*,int*);

#endif
