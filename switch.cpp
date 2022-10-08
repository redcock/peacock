#include <stdio.h>
#include <stdlib.h>
#include <cstring>
int main (int argc, char **argv) {

   /* local variable definition */
   int flag = 1;

   while (flag) {
       if (strcmp(argv[1], "EXIT") == 0) {
          printf("Quite\n");
          flag = 0;
       }
       else if (strcmp(argv[1], "Get Quote") == 0) {
          printf("Do more work\n");
          flag = 0;
       }
       else {
          printf("Illegal message\n");
          flag = 0;
       }
   } 
}
