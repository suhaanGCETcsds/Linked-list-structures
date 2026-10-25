
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node *next;
};

struct Node *createNode(int coeff, int exp) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    return newNode;
}

void insertEnd(struct Node **head, int coeff, int exp) {
    if (coeff == 0)
        return;

    struct Node *newNode = createNode(coeff, exp);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node *temp = *head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

struct Node *readPolynomial() {
    struct Node *head = NULL;
    int n, coeff, exp;

    printf("Enter number of terms: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent: ");

        if (scanf("%d %d", &coeff, &exp) != 2 ||
            exp < 0) {
            printf("Invalid input!\n");
            exit(EXIT_FAILURE);
        }

        insertEnd(&head, coeff, exp);
    }

    return head;
}

struct Node *addPolynomial(
    struct Node *p1, struct Node *p2) {

    struct Node *result = NULL;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            insertEnd(&result,
                      p1->coeff + p2->coeff,
                      p1->exp);

            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->exp > p2->exp) {
            insertEnd(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        }
        else {
            insertEnd(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        insertEnd(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        insertEnd(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

void display(struct Node *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    while (head != NULL) {
        printf("%dx^%d", head->coeff, head->exp);

        head = head->next;

        if (head != NULL)
            printf(" + ");
    }

    printf("\n");
}

void freeList(struct Node *head) {
    while (head != NULL) {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node *p1, *p2, *sum;

    printf("Enter first polynomial\n");
    p1 = readPolynomial();

    printf("\nEnter second polynomial\n");
    p2 = readPolynomial();

    printf("\nFirst polynomial: ");
    display(p1);

    printf("Second polynomial: ");
    display(p2);

    sum = addPolynomial(p1, p2);

    printf("Sum: ");
    display(sum);

    freeList(p1);
    freeList(p2);
    freeList(sum);

    return 0;
}
