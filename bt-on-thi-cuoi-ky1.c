#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Node structure for linked list
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Hash table structure
typedef struct
{
    Node *head;
} HashTable;

// Initialize hash table
void initializeTable(HashTable table[])
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i].head = NULL;
    }
}

// Hash function
int hashFunction(int key)
{
    return key % TABLE_SIZE;
}

// Insert function with chaining with replacement
void insert(HashTable table[], int data)
{
    int hashIndex = hashFunction(data);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (table[hashIndex].head == NULL)
    {
        table[hashIndex].head = newNode;
    }
    else
    {
        Node *current = table[hashIndex].head;
        Node *prev = NULL;
        while (current != NULL && hashFunction(current->data) == hashIndex)
        {
            prev = current;
            current = current->next;
        }

        if (prev == NULL)
        { // Replace the head if needed
            newNode->next = table[hashIndex].head;
            table[hashIndex].head = newNode;
        }
        else
        { // Replace within the list
            newNode->next = prev->next;
            prev->next = newNode;
        }
    }
}

// Display function for hash table
void displayTable(HashTable table[])
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Index %d: ", i);
        Node *current = table[i].head;
        while (current != NULL)
        {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main()
{
    HashTable table[TABLE_SIZE];
    initializeTable(table);

    int data[] = {62, 17, 32, 48, 27, 12, 13, 18, 10, 29};
    int size = sizeof(data) / sizeof(data[0]);

    for (int i = 0; i < size; i++)
    {
        insert(table, data[i]);
    }

    displayTable(table);
    return 0;
}
