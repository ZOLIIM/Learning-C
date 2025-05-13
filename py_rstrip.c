//a C function called py_rstrip() that removes spaces from the end of a string. This function modifies its parameter and should never be called with a constant value.

void py_rstrip(inp)
    char inp[];
{
  	int length;
  	for (length=0;inp[length]!='\0';length ++);
  	int i;
  	for(i=length-1;inp[i]== ' ';i--){
    free(inp[i+1]);
    inp[i]='\0';
    }
}

#include <stdio.h>
#include <string.h>
int main() {
    char s1[] = "   Hello   World    ";
    void py_rstrip();
    py_rstrip(s1);
    printf("-%s-\n", s1);
}
