#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100
#define MAX 1000

struct HashTableItem
{
    int key;
    int value;
};

struct HashTable
{
    struct HashTableItem **table;
};

struct HashTable *createTable()
{
    struct HashTable *newTable = (struct HashTable *)malloc(sizeof(struct HashTable));
    newTable->table = (struct HashTableItem **)malloc(TABLE_SIZE * sizeof(struct HashTableItem *));
    for (int i = 0; i < TABLE_SIZE; i++)
        newTable->table[i] = NULL;
    return newTable;
}

int hashFunction(int key)
{
    return key % TABLE_SIZE;
}

void insertHashTable(struct HashTable *hashtable, int key, int value)
{
    int hashIndex = hashFunction(key);
    struct HashTableItem *newItem = (struct HashTableItem *)malloc(sizeof(struct HashTableItem));
    newItem->key = key;
    newItem->value = value;
    while (hashtable->table[hashIndex] != NULL && hashtable->table[hashIndex]->key != -1)
    {
        hashIndex++;
        hashIndex %= TABLE_SIZE;
    }
    hashtable->table[hashIndex] = newItem;
}

int searchHashTable(struct HashTable *hashtable, int key)
{
    int hashIndex = hashFunction(key);
    while (hashtable->table[hashIndex] != NULL)
    {
        if (hashtable->table[hashIndex]->key == key)
            return hashtable->table[hashIndex]->value;
        hashIndex++;
        hashIndex %= TABLE_SIZE;
    }
    return -1; // Không tìm thấy
}

void deleteHashTable(struct HashTable *hashtable, int key)
{
    int hashIndex = hashFunction(key);
    while (hashtable->table[hashIndex] != NULL)
    {
        if (hashtable->table[hashIndex]->key == key)
        {
            struct HashTableItem *temp = hashtable->table[hashIndex];
            hashtable->table[hashIndex] = NULL;
            free(temp);
            return;
        }
        hashIndex++;
        hashIndex %= TABLE_SIZE;
    }
}

// Định nghĩa cho cấu trúc ngăn xếp
struct Stack
{
    int top;
    int arr[MAX];
};

void khoiTaoStack(struct Stack *stack)
{
    stack->top = -1;
}

int dayStack(struct Stack *stack)
{
    return stack->top == MAX - 1;
}

int rongStack(struct Stack *stack)
{
    return stack->top == -1;
}

void day(struct Stack *stack, int item)
{
    if (dayStack(stack))
    {
        printf("Ngăn xếp đầy\n");
        return;
    }
    stack->arr[++stack->top] = item;
    printf("%d được đẩy vào ngăn xếp\n", item);
}

int lay(struct Stack *stack)
{
    if (rongStack(stack))
    {
        printf("Ngăn xếp rỗng\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

int xem(struct Stack *stack)
{
    if (rongStack(stack))
    {
        printf("Ngăn xếp rỗng\n");
        return -1;
    }
    return stack->arr[stack->top];
}

int main()
{
    struct HashTable *ht = createTable();
    insertHashTable(ht, 1, 20);
    insertHashTable(ht, 2, 70);
    insertHashTable(ht, 42, 80);
    printf("Phần tử có key 42 là: %d\n", searchHashTable(ht, 42));

    deleteHashTable(ht, 2);
    printf("Phần tử có key 2 sau khi xóa: %d\n", searchHashTable(ht, 2));

    struct Stack stack;
    khoiTaoStack(&stack);

    day(&stack, 10);
    day(&stack, 20);
    day(&stack, 30);

    printf("%d được lấy ra khỏi ngăn xếp\n", lay(&stack));
    printf("Phần tử trên cùng là %d\n", xem(&stack));

    return 0;
}
