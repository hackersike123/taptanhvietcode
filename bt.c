#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

Node* findX(Node* head, int x) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == x) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node* findFirstEven(Node* head) {
    Node* current = head;
    while (current != NULL) {
        if (current->data % 2 == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void insertAfterFirstEven(Node** head, int x) {
    Node* evenNode = findFirstEven(*head);
    if (evenNode != NULL) {
        Node* newNode = createNode(x);
        newNode->next = evenNode->next;
        evenNode->next = newNode;
    }
}

void deleteAfterFirstOdd(Node** head) {
    Node* current = *head;
    while (current != NULL && current->next != NULL) {
        if (current->data % 2 != 0) {
            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}

void insertSorted(Node** head, int x) {
    Node* newNode = createNode(x);
    if (*head == NULL || (*head)->data >= x) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next != NULL && current->next->data < x) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void splitList(Node* head, Node** l1, Node** l2) {
    *l1 = NULL;
    *l2 = NULL;
    Node** lastPtrRef1 = l1;
    Node** lastPtrRef2 = l2;

    while (head != NULL) {
        if (head->data % 2 == 0) {
            *lastPtrRef1 = head;
            lastPtrRef1 = &(head->next);
        } else {
            *lastPtrRef2 = head;
            lastPtrRef2 = &(head->next);
        }
        head = head->next;
    }
    *lastPtrRef1 = NULL;
    *lastPtrRef2 = NULL;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("Original list: ");
    printList(head);

    insertAfterFirstEven(&head, 6);
    printf("After inserting 6 after first even: ");
    printList(head);

    deleteAfterFirstOdd(&head);
    printf("After deleting node after first odd: ");
    printList(head);

    insertSorted(&head, 0);
    printf("After inserting 0 in sorted order: ");
    printList(head);

    Node* l1 = NULL;
    Node* l2 = NULL;
    splitList(head, &l1, &l2);
    printf("List with even numbers: ");
    printList(l1);
    printf("List with odd numbers: ");
    printList(l2);

    return 0;
}
