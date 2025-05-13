#include <stdio.h>
/* 
Input: 42 > 114 > 105 > 97 > 
110 < < < < 66
*/

int main()
{
    char memory[256], token[256];
    int position = 0, value;

    while(scanf("%s",token) == 1 ) {
        switch (*token){
          case '>':
            position++;
           	break;
          case '<':
            position--;
            break;
          default:
            memory[position]=atoi(token);
        }

        /* Replace this with your code */
    }
  	
    printf("Memory:\n%s\n", memory);
}
