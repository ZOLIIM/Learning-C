void itob(n, s)
int n;
char s[];
{
  if (n == 0) {
        s[0] = '0';
       s[1] = '\0';
        return;
    }
  
  int k=0;
while (n>0){
  s[k++]=(n%2)+'0';
  n/=2;
 }
int i, j;
    char tmp;
    
     for (i = 0, j = k - 1; i < j; i++, j--) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
  
  s[k]='\0';
}

void itoh(n,s) 
int n;
char s[];
{
    if (n == 0) {
        s[0] = '0';
        s[1] = '\0';
        return;
    }

    int k = 0;
    while (n > 0) {
        int digit = n % 16;
        if (digit < 10)
            s[k++] = digit + '0';
        else
            s[k++] = digit - 10 + 'a';  // lowercase hex
        n /= 16;
    }

    // Reverse the string
  int i,j; 
  s[k] = '\0'; // null-terminate before reversing
    for (i = 0, j = k - 1; i < j; i++, j--) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}
