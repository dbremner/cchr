#include <stdio.h>
#include <ctype.h>

#include "parse.h"

/* 
 read data from a file. Multiple spaces,tabs and newlines are shrinked to
 one space. Support for C-style string and character constants, C-style
 comments, indentation('{','}') and delimiters (';' and '}') outside brackets,
 ignoring empty items 
*/

int lread(char* buf,FILE* file,int* line) {
 char *ob=buf; /* old buffer */
 char *mb=buf+MAXLINELEN-1; /* max buffer */
 int st=1,nh=0,sh=0; /* compact following space,'('s,'['s */
 while (1) {
  int c=getc(file);
  if (c=='\n') (*line)++;
  if (c==EOF) {
   *buf=0;
   return(READ_EOF); /* normal end-of-file */
  }
  if (c=='/') { /* C-style comment handler */
   c=getc(file);
   if (c==EOF) return(READ_EEOF); /* error end-of-file */
   if (c=='*') {
    int cc=0;
    if (!st) {
     if (buf==mb) return(READ_BUFF); /* buffer overflow */
     *(buf++)=' ';
     st=1;
    }
    do {
     c=getc(file);
     if (c==EOF) return(READ_EEOF);
     if (c=='*') cc=2;
     if (c=='/' && cc) break;
     if (cc) cc--;
    } while (1);
    continue;
   } else {
    ungetc(c,file);
    c='/';
   }
  }
  if (isspace(c)) { /* spacing handler */
   if (!st) {
    do {
     c=getc(file);
     if (c=='\n') (*line)++;
     if (c==EOF) {
      *buf=0;
      return(READ_EOF);
     }
     if (c==';'||c=='{'||c=='}'||c==/*(*/')'||c=='['||c==']'||c==','||c=='\''||c=='#') {
      ungetc(c,file);
      break;
     }
     if (!isspace(c)) {
      ungetc(c,file);
      if (buf==mb) return(READ_BUFF);
      *(buf++)=' ';
      break;
     }
    } while(1);
   }
   continue;
  }
  if (c=='('/*)*/) { /* open bracket handler */
   if (buf==mb) return(READ_BUFF);
   *(buf++)=c;
   nh++;
   st=1;
   continue;
  }
  if (c==/*(*/')') { /* close bracket handler */
   if (buf==mb) return(READ_BUFF);
   *(buf++)=c;
   if (!(nh--)) {
    *buf=0;
    return(READ_CHAR);
   }
   st=0;
   continue;
  }
  if (c=='['/*]*/) { /* open block bracket handler */
   if (buf==mb) return(READ_BUFF);
   *(buf++)=c;
   sh++;
   st=1;
   continue;
  }
  if (c==/*[*/']') { /* close block bracket handler */
   if (buf==mb) return(READ_BUFF);
   *(buf++)=c;
   if (!(sh--)) {
    *buf=0;
    return(READ_BRAC); /* bracket error */
   }
   st=1;
   continue;
  }
  if (c=='"') { /* double quote handler */
   if (buf==mb) return(READ_BUFF);
   *(buf++)='"';
   do {
    c=getc(file);
    if (c=='\n') (*line)++;
    if (c==EOF) return(READ_EEOF);
    if (buf==mb) return(READ_BUFF);
    *(buf++)=c;
    if (c=='\\') {
     c=getc(file);
     if (c=='\n') (*line)++;
     if (c==EOF) return(READ_EEOF);
     if (buf==mb) return(READ_BUFF);
     *(buf++)=c;
     c=0;
     continue;
    }
   } while (c!='"');
   st=0;
   continue;
  }
  if (c=='\'') { /* single quote handler */
   if (buf==mb) return(READ_BUFF);
   *(buf++)='\'';
   do {
    c=getc(file);
    if (c=='\n') (*line)++;
    if (c==EOF) return(READ_EEOF);
    if (buf==mb) return(READ_BUFF);
    *(buf++)=c;
    if (c=='\\') {
     c=getc(file);
     if (c=='\n') (*line)++;
     if (c==EOF) return(READ_EEOF);
     if (buf==mb) return(READ_BUFF);
     *(buf++)=c;
     c=0;
     continue;
    }
   } while (c!='\'');
   st=1;
   continue;
  }
  st=0;
  if ((!nh)&&(!sh)) { /* '{','}' and ';' handled specially outside brackets */
   if (c=='{'/*}*/) { /* open '{' */
    *buf=0;
    return(READ_EOLS); /* end-of-line, subblock starts */
   }
   if (c==/*{*/'}') { /* close '}' */
    *buf=0;
    if (buf==ob) {
     do {
      c=getc(file);
      if (c=='\n') (*line)++;
     } while (isspace(c)||c==';');
     ungetc(c,file);
     return(READ_EOB); /* end of block */
    }
    ungetc(c,file);
    return(READ_EOL); /* end of line */
   }
   if (c==';') {
    if (buf==ob) continue;
    *buf=0;
    do {
     c=getc(file);
     if (c=='\n') (*line)++;
    } while (isspace(c)||c==';');
    ungetc(c,file);
    return(READ_EOL);
   }
  } else {
   if (c=='{'||c=='}'||c==';') st=1;
  }
  if (c==',') st=1;
  if (buf==mb) return(READ_BUFF);
  if (c & 0x80 || c<32) return(READ_CHAR); /* invalid character */
  *(buf++)=c;
 } while(1);
 *buf=0;
 return(READ_EOL);
}
