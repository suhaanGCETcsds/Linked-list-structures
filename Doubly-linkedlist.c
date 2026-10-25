
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;
struct Node *tail = NULL;

void insertBeginning(int value) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = head;

    if (head == NULL) {
        head = tail = newNode;
    } else {
        head->prev = newNode;
        head = newNode;
    }

    printf("Node inserted successfully.\n");
}

// Insert at end
void insertEnd(int value) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = tail;

    if (tail == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    printf("Node inserted successfully.\n");
}

// Delete from beginning
void deleteBeginning() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = head;

    printf("Deleted element: %d\n", temp->data);

    head = head->next;

    if (head == NULL) {
        tail = NULL;
    } else {
        head->prev = NULL;
    }

    free(temp);
}

void displayForward() {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = head;

    printf("Forward: ");

    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

void displayBackward() {
    if (tail == NULL) {
        printf("List is empty!\n");
        return;
    }

    struct Node *temp = tail;

    printf("Backward: ");

    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }

    printf("NULL\n");
}

void freeList() {
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }

    tail = NULL;
}

int main() {
    int choice, value;

    while (1) {
        printf("\n1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Delete from beginning\n");
        printf("4. Display forward\n");
        printf("5. Display backward\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            freeList();
            return 0;
        }

        switch (choice) {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    freeList();
                    return 0;
                }
                insertBeginning(value);
                break;

            case 2:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    freeList();
                    return 0;
                }
                insertEnd(value);
                break;

            case 3:
                deleteBeginning();
                break;

            case 4:
                displayForward();
                break;

            case 5:
                displayBackward();
                break;

            case 6:
                freeList();
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
