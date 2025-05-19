#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeMapEntry {
    char *key;
    int value;
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
    struct TreeMapEntry *__head;
    struct TreeMapEntry *__root;
    int __count;
    int debug;

    void (*put)(struct TreeMap* self, char *key, int value);
    int (*get)(struct TreeMap* self, char *key, int def);
    int (*size)(struct TreeMap* self);
    void (*dump)(struct TreeMap* self);
    struct TreeMapIter* (*iter)(struct TreeMap* self);
    void (*del)(struct TreeMap* self);
};

/* Iterator */
struct TreeMapEntry* __TreeMapIter_next(struct TreeMapIter* self) {
    struct TreeMapEntry* cur = self->__current;
    if (cur) self->__current = cur->__next;
    return cur;
}

void __TreeMapIter_del(struct TreeMapIter* self) {
    free(self);
}

/* TreeMap Methods */
int __TreeMap_get(struct TreeMap* self, char *key, int def) {
    struct TreeMapEntry *cur = self->__root;
    while (cur) {
        int cmp = strcmp(key, cur->key);
        if (cmp == 0) return cur->value;
        cur = (cmp < 0) ? cur->__left : cur->__right;
    }
    return def;
}

void __TreeMap_put(struct TreeMap* self, char *key, int value) {
    struct TreeMapEntry *cur = self->__root, *parent = NULL;
    struct TreeMapEntry *left = NULL, *right = NULL;
    int cmp;

    while (cur) {
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

    struct TreeMapEntry *new = malloc(sizeof(*new));
    new->key = strdup(key);
    new->value = value;
    new->__left = new->__right = NULL;

    // Insert into linked list
    if (left == NULL && right == NULL) {
        // Empty map
        new->__next = NULL;
        self->__head = new;
        self->__root = new;
    } else if (left == NULL) {
        // Insert before head
        new->__next = right;
        self->__head = new;
    } else {
        // Insert after left
        new->__next = left->__next;
        left->__next = new;
    }

    // Insert into tree
    if (parent != NULL) {
        cmp = strcmp(key, parent->key);
        if (cmp < 0) {
            parent->__left = new;
        } else {
            parent->__right = new;
        }
    } else {
        self->__root = new;
    }

    self->__count++;
}

struct TreeMapIter* __TreeMap_iter(struct TreeMap* self) {
    struct TreeMapIter *iter = malloc(sizeof(*iter));
    iter->__current = self->__head;
    iter->next = __TreeMapIter_next;
    iter->del = __TreeMapIter_del;
    return iter;
}

void __TreeMap_del(struct TreeMap* self) {
    struct TreeMapEntry *cur = self->__head, *next;
    while (cur) {
        free(cur->key);
        next = cur->__next;
        free(cur);
        cur = next;
    }
    free(self);
}

int __TreeMap_size(struct TreeMap* self) {
    return self->__count;
}

void __TreeMap_dump(struct TreeMap* self) {
    struct TreeMapEntry *cur = self->__head;
    printf("TreeMap size=%d\n", self->__count);
    while (cur) {
        printf("  %s=%d\n", cur->key, cur->value);
        cur = cur->__next;
    }
}

struct TreeMap * TreeMap_new() {
    struct TreeMap *map = malloc(sizeof(*map));
    map->__head = NULL;
    map->__root = NULL;
    map->__count = 0;
    map->debug = 0;
    map->put = __TreeMap_put;
    map->get = __TreeMap_get;
    map->size = __TreeMap_size;
    map->dump = __TreeMap_dump;
    map->iter = __TreeMap_iter;
    map->del = __TreeMap_del;
    return map;
}
