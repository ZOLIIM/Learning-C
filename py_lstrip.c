void py_lstrip(inp)
    char *inp;
{
      char *start = inp;

    // Find the first non-whitespace character
    while (*start == ' ' || *start == '\t' || *start == '\n') {
        start++;
    }

    // Shift the remaining characters to the beginning of the string
    while (*start) {
        *inp++ = *start++;
    }

    *inp = '\0'; // Null-terminate the modified string
  /*	Not use it, it is not neccesary
  while (*inp){
      free(*inp++);
      }
  */
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    char s1[] = "   Hello   World    ";
    void py_lstrip();
    py_lstrip(s1);
    printf("-%s-\n", s1);
}
