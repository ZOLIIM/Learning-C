void process(line)
    char *line;
{
  	int i,count;
    printf("String: %s\n",line);
  	count=0;
  	for(i=0;*(line+i)!='\0';i++);
  	printf("Count=%d\n",i);
  	if(i>10){
      printf("The ninth character is: %c\n", *(line+9));
      
    }
  	for(i=0;*(line+i)!='\0';i++){
    	if(*(line+i)==' '){
          *(line+i)='-';
    }
    }
    printf("String: %s\n",line);
  	printf("\n");
  	
}
#include <stdio.h>
#include <string.h>
int main() {
    char line[1000];
    void process();
    strcpy(line,"Hi there and welcome to LBS290");
    process(line);
    strcpy(line,"I love C");
    process(line);
}
