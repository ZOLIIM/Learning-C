void __TreeMap_put(struct TreeMap* self, char *key, int value) {
    struct TreeMapEntry *cur = self->__root;
    struct TreeMapEntry *parent = NULL;
    struct TreeMapEntry *left = NULL, *right = NULL;
    int cmp = 0;

    if (key == NULL) return;

    // Traverse the BST to find the correct location
    while (cur != NULL) {
        cmp = strcmp(key, cur->key);
        if (cmp == 0) {
            cur->value = value;
            return;
        }
        parent = cur;
        if (cmp < 0) {
            right = cur;
            cur = cur->__left;
        } else {
            left = cur;
            cur = cur->__right;
        }
    }

    // Allocate and initialize new entry
    struct TreeMapEntry *new = malloc(sizeof(*new));
    new->key = strdup(key);
    new->value = value;
    new->__left = NULL;
    new->__right = NULL;
    new->__next = NULL;

    // Insert into linked list
    if (self->__head == NULL) {
        self->__head = new;
    } else if (left == NULL) {
        // Insert at the front of the list
        new->__next = right;
        self->__head = new;
    } else {
        // Insert after 'left' in the linked list
        new->__next = left->__next;
        left->__next = new;
    }

    // Insert into tree
    if (self->__root == NULL) {
        self->__root = new;
    } else if (cmp < 0) {
        parent->__left = new;
    } else {
        parent->__right = new;
    }

    // Check position for debug

 self->__count++;
  if(left==NULL && right==NULL);
  else printf("Check position: %s < %s > %s\n", (left ? left->key : "0"),
            key, (right ? right->key : "0") );
  
   
}

int __TreeMap_get(struct TreeMap* self, char *key, int def) {
    struct TreeMapEntry *cur = self->__root;

    while (cur != NULL) {
        int cmp = strcmp(key, cur->key);
        if (cmp == 0) return cur->value;
        else if (cmp > 0) cur = cur->__left;
        else cur = cur->__right;
    }
    return def;
}

struct TreeMapEntry* __TreeMapIter_next(struct TreeMapIter* self) {
    struct TreeMapEntry *cur = self->__current;
    if (cur == NULL) return NULL;
    self->__current = cur->__next;
    return cur;
}
int __TreeMap_get(struct TreeMap* self, char *key, int def) {
    struct TreeMapEntry *cur = self->__root;

    while (cur != NULL) {
        int cmp = strcmp(key, cur->key);
        if (cmp == 0) return cur->value;
        else if (cmp > 0) cur = cur->__left;
        else cur = cur->__right;
    }
    return def;
}

struct TreeMapEntry* __TreeMapIter_next(struct TreeMapIter* self) {
    struct TreeMapEntry *cur = self->__current;
    if (cur == NULL) return NULL;
    self->__current = cur->__next;
    return cur;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeMapEntry {
    char *key;  /* public */
    int value;  /* public */
    struct TreeMapEntry *__next;
    struct TreeMapEntry *__left;
    struct TreeMapEntry *__right;
};

struct TreeMapIter {
   struct TreeMapEntry *__current;

   struct TreeMapEntry* (*next)(struct TreeMapIter* self);
   void (*del)(struct TreeMapIter* self);
};

struct TreeMap {
   /* Attributes */
   struct TreeMapEntry *__head;
   struct TreeMapEntry *__root;
   int __count;
   int debug;

   /* Methods */
   void (*put)(struct TreeMap* self, char *key, int value);
   int (*get)(struct TreeMap* self, char *key, int def);
   int (*size)(struct TreeMap* self);
   void (*dump)(struct TreeMap* self);
   struct TreeMapIter* (*iter)(struct TreeMap* self);
   void (*del)(struct TreeMap* self);
};

void __TreeMap_del(struct TreeMap* self) {
    struct TreeMapEntry *cur, *next;
    cur = self->__head;
    while(cur) {
        free(cur->key);
        /* value is just part of the struct */
        next = cur->__next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

void __TreeMapIter_del(struct TreeMapIter* self) {
    free((void *)self);
}

void __TreeMap_dump_tree(struct TreeMapEntry *cur, int depth)
{
    int i;
    if ( cur == NULL ) return;
    for(i=0;i<depth;i++) printf("| ");
    printf("%s=%d\n", cur->key, cur->value);
    if ( cur->__left != NULL ) {
        __TreeMap_dump_tree(cur->__left, depth+1);
    }
    if ( cur->__right != NULL ) {
        __TreeMap_dump_tree(cur->__right, depth+1);
    }
}

void __TreeMap_dump(struct TreeMap* self)
{
    struct TreeMapEntry *cur;
    printf("Object TreeMap count=%d\n", self->__count);
    for(cur = self->__head; cur != NULL ; cur = cur->__next ) {
         printf("  %s=%d\n", cur->key, cur->value);
    }
    printf("\n");
    __TreeMap_dump_tree(self->__root, 0);
    printf("\n");
}

/* Run a check to see if left and right are broken */
void __Map_check(struct TreeMap* self, struct TreeMapEntry *left, char *key, struct TreeMapEntry *right)
{
    if ( self->debug ) 
        printf("Check position: %s < %s > %s\n", (left ? left->key : "0"),
            key, (right ? right->key : "0") );

    /* Check our location in the linked list */
    if ( left != NULL ) {
        if ( left->__next != right ) {
            printf("FAIL left->__next != right\n");
        }
    } else {
        if ( self->__head != right ) {
            printf("FAIL self->__head != right\n");
        }
    }

    /* Check our location in the tree */
    if ( right != NULL && right->__left == NULL ) {
        /* OK */
    } else if ( left != NULL && left->__right == NULL ) {
        /* OK */
    } else {
        printf("FAIL Neither right->__left nor left->__right are available\n");
    }
}

#include "student.c"

int __TreeMap_size(struct TreeMap* self)
{
    return self->__count;
}

struct TreeMapIter* __TreeMap_iter(struct TreeMap* self)
{
    struct TreeMapIter *iter = malloc(sizeof(*iter));
    iter->__current = self->__head;
    iter->next = &__TreeMapIter_next;
    iter->del = &__TreeMapIter_del;
    return iter;
}

struct TreeMap * TreeMap_new() {
    struct TreeMap *p = malloc(sizeof(*p));

    p->__head = NULL;
    p->__root = NULL;
    p->__count = 0;
    p->debug = 0;

    p->put = &__TreeMap_put;
    p->get = &__TreeMap_get;
    p->size = &__TreeMap_size;
    p->dump = &__TreeMap_dump;
    p->iter = &__TreeMap_iter;
    p->del = &__TreeMap_del;
    return p;
}

int main(void)
{
    struct TreeMap * map = TreeMap_new();
    struct TreeMapEntry *cur;
    struct TreeMapIter *iter;

    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

    map->debug = 1 == 1;

    printf("Testing TreeMap\n");
    map->put(map, "h", 42);
    map->put(map, "d", 8);
    map->put(map, "f", 5);
    map->put(map, "b", 123);
    map->dump(map);
    map->put(map, "k", 9);
    map->put(map, "m", 67);
    map->put(map, "j", 12);
    map->put(map, "f", 6);
    map->dump(map);

    printf("r=%d\n", map->get(map, "r", 42));
    printf("x=%d\n", map->get(map, "x", 42));

    printf("\nIterate\n");
    iter = map->iter(map);
    while(1) {
        cur = iter->next(iter);
        if ( cur == NULL ) break;
        printf(" %s=%d\n", cur->key, cur->value);
    }
    iter->del(iter);

    map->del(map);
}
