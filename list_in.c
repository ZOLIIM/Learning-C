void list_add(lst, value)
    struct list *lst;
    int value;
{
    struct lnode *new= (struct lnode *) malloc(sizeof(struct lnode));
  	if(lst->tail != NULL) lst->tail->next=new;
  	new->value=value;
  	new->next=NULL;
  	lst->tail=new;
  	if (lst->head==NULL) lst->head=new;
}

struct lnode * list_find(lst, value)
    struct list *lst;
    int value;
{	
  	int i=NULL;
  	struct lnode *cur;
    for(cur=lst->head; cur != NULL ; cur=cur->next) {
      
      if(cur->value == value){
		break;
      }

    }
    return cur;
}
#include <stdio.h>
#include <stdlib.h>

struct lnode {
    int value;
    struct lnode *next;
};

struct list {
  struct lnode *head;
  struct lnode *tail;
};

int main()
{
    void list_add();
	void list_remove();
    void list_dump();
    struct lnode * list_find();

    struct list mylist;
    struct lnode * mynode;

    mylist.head = NULL;
    mylist.tail = NULL;

    list_add(&mylist, 10);
    list_add(&mylist, 20);
    list_add(&mylist, 30);
    list_dump(&mylist);

    mynode = list_find(&mylist, 42);
    if ( mynode == NULL ) {
        printf("Did not find 42\n");
    } else {
        printf("Looked for 42, found %d\n", mynode->value);
    }

    mynode = list_find(&mylist, 30);
    if ( mynode == NULL || mynode->value != 30) {
        printf("Did not find 30\n");
    } else {
        printf("Found 30\n");
    }

    list_add(&mylist, 40);
    list_dump(&mylist);
 	list_add(&mylist, 10);
    list_add(&mylist, 20);
    list_add(&mylist, 30);
    list_dump(&mylist);

    list_remove(&mylist, 42);

    list_remove(&mylist, 10);
    list_dump(&mylist);

    list_remove(&mylist, 30);
    list_dump(&mylist);

    list_add(&mylist, 40);
    list_dump(&mylist);

}

void list_dump(lst)
    struct list *lst;
{
    struct lnode *cur;
    printf("\nDump:\n");
    for(cur=lst->head; cur != NULL; cur=cur->next) {
        printf("  %d\n", cur->value);
    }
}

void list_remove(lst, value)
    struct list *lst;
    int value;
{
    int i=NULL;
  	struct lnode *cur;
  	struct lnode *prev=NULL;
  
    for(cur=lst->head; cur != NULL ; cur=cur->next) {
      
      if(cur->value == value){
		if(prev==NULL){
        //HEAD
          //printf("HEAD");
          lst->head=cur->next;
          break;
        }
        
        else if(cur->next==NULL){
        //TAIL
         // printf("TAIL");
         prev->next=NULL;
         lst->tail=prev;
          break;
        }
        
        else{
         //MID 
          
         //printf("MID");
         prev->next=cur->next;
        }
      }
      else{
      prev=cur;
      }

    }
