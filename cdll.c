#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev, *next;
};

// Create header node
struct node *createHeader() {
    struct node *h = malloc(sizeof(struct node));
    h->next = h;
    h->prev = h;
    return h;
}

// Insert before a given node
void insertBefore(struct node *p, int x) {
    struct node *n = malloc(sizeof(struct node));
    n->data = x;

    n->next = p;
    n->prev = p->prev;
    p->prev->next = n;
    p->prev = n;
}

// Insert at front
void insertFront(struct node *h, int x) {
    insertBefore(h->next, x);
}

// Insert at rear
void insertRear(struct node *h, int x) {
    insertBefore(h, x);
}

// Count nodes
int count(struct node *h) {
    int c = 0;
    struct node *p = h->next;

    while (p != h) {
        c++;
        p = p->next;
    }
    return c;
}

// Insert at specified position
void insertPos(struct node *h, int x, int pos) {
    int i, n = count(h);
    struct node *p = h->next;

    if (pos < 1 || pos > n + 1) {
        printf("Invalid position\n");
        return;
    }

    for (i = 1; i < pos; i++)
        p = p->next;

    insertBefore(p, x);
}

// Delete a given node
void deleteNode(struct node *p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

// Delete at front
void deleteFront(struct node *h) {
    if (h->next == h) {
        printf("List is empty\n");
        return;
    }

    deleteNode(h->next);
}

// Delete at rear
void deleteRear(struct node *h) {
    if (h->prev == h) {
        printf("List is empty\n");
        return;
    }

    deleteNode(h->prev);
}

// Delete at specified position
void deletePos(struct node *h, int pos) {
    int i, n = count(h);
    struct node *p = h->next;

    if (pos < 1 || pos > n) {
        printf("Invalid position\n");
        return;
    }

    for (i = 1; i < pos; i++)
        p = p->next;

    deleteNode(p);
}

// Delete by key
void deleteKey(struct node *h, int key) {
    struct node *p = h->next;

    while (p != h && p->data != key)
        p = p->next;

    if (p == h) {
        printf("Key not found\n");
        return;
    }

    deleteNode(p);
    printf("Key deleted\n");
}

// Search by key
void searchKey(struct node *h, int key) {
    struct node *p = h->next;
    int pos = 1;

    while (p != h && p->data != key) {
        p = p->next;
        pos++;
    }

    if (p == h)
        printf("Key not found\n");
    else
        printf("Key found at position %d\n", pos);
}

// Display list
void display(struct node *h) {
    struct node *p = h->next;

    if (p == h) {
        printf("List is empty\n");
        return;
    }

    printf("List: ");

    while (p != h) {
        printf("%d ", p->data);
        p = p->next;
    }

    printf("\n");
}

// Clear list
void clearList(struct node *h) {
    while (h->next != h)
        deleteNode(h->next);
}

// Insert in ascending order
void sortedInsert(struct node *h, int x) {
    struct node *p = h->next;

    while (p != h && p->data <= x)
        p = p->next;

    insertBefore(p, x);
}

// Create ordered list
void createOrdered(struct node *h) {
    int n, x, i;

    clearList(h);

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter value: ");
        scanf("%d", &x);
        sortedInsert(h, x);
    }

    printf("Ordered list created\n");
}

// Reverse list
void reverseList(struct node *h) {
    struct node *p = h, *temp;

    do {
        temp = p->next;
        p->next = p->prev;
        p->prev = temp;
        p = temp;
    } while (p != h);

    printf("List reversed\n");
}

// Create a copy of list
struct node *copyList(struct node *h) {
    struct node *copy = createHeader();
    struct node *p = h->next;

    while (p != h) {
        insertRear(copy, p->data);
        p = p->next;
    }

    return copy;
}

// Main function
int main() {
    struct node *h = createHeader();
    struct node *copy;

    int ch, x, pos, key;

    printf("\n--- CIRCULAR DOUBLY LINKED LIST ---\n");
    printf("1. Insert Front\n");
    printf("2. Insert Rear\n");
    printf("3. Insert at Position\n");
    printf("4. Delete Front\n");
    printf("5. Delete Rear\n");
    printf("6. Delete at Position\n");
    printf("7. Delete by Key\n");
    printf("8. Search by Key\n");
    printf("9. Create Ordered List\n");
    printf("10. Reverse List\n");
    printf("11. Copy List\n");
    printf("12. Display List\n");

    while (1) {
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &x);
                insertFront(h, x);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &x);
                insertRear(h, x);
                break;

            case 3:
                printf("Enter value and position: ");
                scanf("%d%d", &x, &pos);
                insertPos(h, x, pos);
                break;

            case 4:
                deleteFront(h);
                break;

            case 5:
                deleteRear(h);
                break;

            case 6:
                printf("Enter position: ");
                scanf("%d", &pos);
                deletePos(h, pos);
                break;

            case 7:
                printf("Enter key: ");
                scanf("%d", &key);
                deleteKey(h, key);
                break;

            case 8:
                printf("Enter key: ");
                scanf("%d", &key);
                searchKey(h, key);
                break;

            case 9:
                createOrdered(h);
                break;

            case 10:
                reverseList(h);
                break;

            case 11:
                copy = copyList(h);
                printf("Copied list: ");
                display(copy);
                clearList(copy);
                free(copy);
                break;

            case 12:
                display(h);
                break;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
