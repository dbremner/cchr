#include "parsestr.h"
#include "semtree.h"
#include "abs2sem.h"
#include "sem2csm.h"

typedef void* yyscan_t;
int yylex_init (yyscan_t* scanner);
int yylex_destroy (yyscan_t yyscanner );
int yyparse(yyscan_t scanner,cchr_t *output);

int main(int argc, char *argv[])
{
  yyscan_t scanner;
  //freopen("gcd.cchr","r",stdin);
  yylex_init(&scanner);
  cchr_t cchr;
  yyparse(scanner,&cchr);
  yylex_destroy(scanner);
  sem_cchr_t sem_cchr;
  sem_generate_cchr(&sem_cchr,&cchr);
  destruct_cchr_t(&cchr);
  csm_generate(&sem_cchr,stdout);
  sem_cchr_destruct(&sem_cchr);
  return(0);
}
