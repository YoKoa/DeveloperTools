#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#define Begin() static int state=0; switch(state) { case 0:
#define Yield(x) do { state=__LINE__; return x; case __LINE__:; } while (0)
#define End() }

int function_v3(void) {
  static int i;
  Begin();
  for (i = 0; i < 10; i++)
    Yield(i);
  End();
}
int function_v2(void) {
  static int i, state = 0;
  switch (state) {
    case 0: 
    for (i = 0; i < 10; i++) {
      state = 1;
      return i;
      case 1:;
    }
  }
}
int function_v1(void) {
  static int i, state = 0;
  switch (state) {
    case 0: goto LABEL0;
    case 1: goto LABEL1;
  }
  LABEL0: /* start of function */
  for (i = 0; i < 10; i++) {
    state = 1; /* so we will come back to LABEL1 */
    return i;
    LABEL1:; /* resume control straight after the return */
  }
}


int main()
{
      int i = function_v3();
      printf("%d\n",i);

      int j = function_v3();
      printf("%d\n",j);

      int r = function_v3();
      printf("%d\n",r);

      int t = function_v3();
      printf("%d\n",t);
      
}


