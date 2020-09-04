#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define UNDEF -1

int Capital(char *testval)
{
   int i;
   for(i=0;i<strlen(testval);i++)
   {
      if((testval[i] >= 65 && testval[i] <=90))
      return 1;
   }
   return 0;
}
int Small(char *testval)
{
   int i;
   for(i=0;i<strlen(testval);i++)
   {
      if((testval[i] >= 97 && testval[i] <=122))
      return 1;
   }
   return 0;
}
int Digit(char *testval)
{
   int i;
   int c=0;
   for(i=0;i<strlen(testval);i++)
   {
      if((testval[i] >= 48 && testval[i] <=57))
      {
        c++;
      }
   }
   if(c>0)
   return 1;
   return 0;
}
int special(char *testval)
{
   int i;
   for(i=0;i<strlen(testval);i++){
  if((testval[i] == 32 || testval[i] == 44 || testval[i] == 58 || testval[i] == 59))
  return 1;
  }
  return 0;
}


void test(char *testval)
{
   if(strlen(testval)==0 || strlen(testval) > 45){
   printf("Text Length is Invalid\n");
   return;
   }

    if(testval == ""){
    printf("Empty String\n");
   return;
   }
   if(!(Capital(testval) || Small(testval) || Digit(testval)))
   {
      printf("Invalid character Input\n");
      return;
   }


   printf("ALL TEST PASSED\n");
   return;
}
int main()
{
  char testchar[50];
       int t;
      printf("Enter number of testcases");
      scanf("%d",&t);
      while(t--){
    printf("Enter TestValue\n");
   scanf("%s",testchar);
   test(testchar);
   }

  return 0;
}

