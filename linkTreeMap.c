void __TreeMap_put(struct TreeMap* self, char *key, int value) {
    struct TreeMapEntry *cur = self->__root;
    struct TreeMapEntry *parent = NULL;
    struct TreeMapEntry *left = NULL, *right = NULL;
    int cmp;

    // Search the tree
    while (cur != NULL) {
        cmp = strcmp(key, cur->key);
        if (cmp == 0) {
            cur->value = value; // Update
            return;
        }

        parent = cur;
        if (cmp > 0) {
            right = cur;
            cur = cur->__left;
        } else {
            left = cur;
            cur = cur->__right;
        }
    }

    // Create new entry
    struct TreeMapEntry *new = malloc(sizeof(*new));
    new->key = strdup(key);
    new->value = value;
    new->__left = NULL;
    new->__right = NULL;
    new->__next = NULL;

    // First node
    if (self->__head == NULL) {
        self->__head = new;
        self->__root = new;
    } else {
        // Insert in linked list
        if (left != NULL) {
            new->__next = left->__next;
            left->__next = new;
        } else {
            new->__next = self->__head;
            self->__head = new;
        }
        // Insert in tree
        if (strcmp(key, parent->key) > 0) {
            parent->__left = new;
        } else {
            parent->__right = new;
        }
    }

    self->__count++;
    __Map_check(self, left, key, right);  // For debugging
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
