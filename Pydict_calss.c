/* print(dct) */
/* {'z': 'W', 'y': 'B', 'c': 'C', 'a': 'D'} */
void pydict_print(struct pydict* self)
{
  struct dnode *cur;
  printf("{");
    for(cur=self->head; cur != NULL ; cur=cur->next){
    	printf("'%s': '%s'",cur->key,cur->value);
      if(cur->next !=NULL){
      printf(", ");
      }
    }
   printf("}\n");
}



int pydict_len(const struct pydict* self)
{
  	struct dnode* cur;	
  	int i=0;
    for(cur=self->head; cur!=NULL; cur=cur->next){ 
      i++;
    }
  	return  i;
}

/* find a node - used in get and put */
char* pydict_find(struct pydict* self, char *key)
{	
   printf("eneter function\n");
  	struct dnode* cur;
    for(cur=self->head; cur!=NULL; cur=cur->next){
      printf("eneter loop\n");
      if (cur->key==key){
        printf("found\n");
        return cur->value;
      }
      else if (cur->key!=key&& cur->next==NULL){
        printf("not_found\n");
        return "(null)";
      }
      }

}

/* x.get(key) - Returns NULL if not found */
char* pydict_get(struct pydict* self, char *key)
{
  	struct dnode* cur;
    for(cur=self->head; cur!=NULL; cur=cur->next){
      if (cur->key==key){
        return cur->value;
      }
        else if (cur->key!=key&& cur->next==NULL){
        return "(null)";
      }
      }
}

/* x[key] = value; Insert or replace the value associated with a key */
void pydict_put(struct pydict* self, char *key, char *value)
{	
  	//printf("enter1\n");
   struct dnode* cur, *new;
  	if(self->head==NULL){
      //printf("enter2\n");
        new= malloc(sizeof(*new));
       	new->key=key;
        new->value=value;
        self->head=new;
    }
 	else{
      //printf("enter3\n");
    for(cur=self->head; cur!=NULL; cur=cur->next){
      if (cur->key==key) {
      cur->value=value;
      }
      else if(cur->key!=key && cur->next==NULL){
		///printf("enter4\n");
        new= malloc(sizeof(struct dnode));
       	new->key=key;
        new->value=value;
        cur->next=new;
        self->tail=new;
       }
      }
}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dnode {
    char *key;
    char *value;
    struct dnode *next;
};

struct pydict {
  struct dnode *head;
  struct dnode *tail;
  int count;
};

/* Constructor - dct = dict() */
struct pydict * pydict_new() {
    struct pydict *p = malloc(sizeof(*p));
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    return p;
}

/* Destructor - del(dct) */
void pydict_del(struct pydict* self) {
    struct dnode *cur, *next;
    cur = self->head;
    while(cur) {
        free(cur->key);
        free(cur->value);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

int main(void)
{
    struct dnode * cur;
    struct pydict * dct = pydict_new();

    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

    pydict_put(dct, "z", "Catch phrase");
    pydict_print(dct);
    pydict_put(dct, "z", "W");
    pydict_print(dct);
    pydict_put(dct, "y", "B");
    pydict_put(dct, "c", "C");
    pydict_put(dct, "a", "D");
    pydict_print(dct);
    printf("Length =%d\n",pydict_len(dct));

    printf("z=%s\n", pydict_get(dct, "z"));
    printf("x=%s\n", pydict_get(dct, "x"));

    printf("\nDump\n");
    for(cur = dct->head; cur != NULL ; cur = cur->next ) {
        printf("%s=%s\n", cur->key, cur->value);
    }

    pydict_del(dct);
}
