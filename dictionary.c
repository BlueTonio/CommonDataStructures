#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define setNode struct set_node

int hashmap_size = 10;
struct set_node
{
    const char *key;
    size_t key_len;
    setNode *next;
    int value;
};
struct set_table
{
    setNode **nodes;
    size_t hashmap_size;
    size_t size;
};
size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}
struct set_table *set_table_new(const size_t hashmap_size)
{
    struct set_table *table = malloc(sizeof(struct set_table));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}
int search_and_return(struct set_table *table, const char *key, const size_t key_len){
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    setNode *head = table->nodes[index];
    while (head)
    {
        if (head->key == key)
        {
            return head->value;
        }
        head = head->next;
    }
    return 0;
}
int re_hash(struct set_table *table){
    hashmap_size++;
    for (int i = 0; i < table->size; i++)
    {
        size_t hash = djb33x_hash(table->nodes[i]->key, hashmap_size);

    }
    return 0;
}

setNode *search_node(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    setNode *head = table->nodes[index];
    while (head)
    {
        if (head->key == key)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}
struct set_node *set_insert(struct set_table *table, const char *key, const size_t key_len, const int Value)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *head = table->nodes[index];

    if(search_node(table, key, hashmap_size) != NULL)
    {
        if(search_node(table, key, hashmap_size)->key == key)
        {
            re_hash(table);
        }
        else
        {
            return NULL; // ritorna nullo
        }
    }

    if (!head) // se il nodo iniziale non esiste
    {
        head = malloc(sizeof(struct set_node)); 
        if (!head) // se il nuovo nodo non esiste
        {
            return NULL;
        }
        head->key = key;
        head->key_len = key_len; 
        head->next = NULL;
        head->value = Value;
        table->nodes[index] = head; 
        return head; 
    }
    struct set_node *new_item = malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return NULL;
    }
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL; 
    new_item->value = Value;
    struct set_node *tail = head;
    tail->next = new_item; 
    return new_item; 
}



setNode *RemoveNode(struct set_table *table, const char *key, const size_t key_len){
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    setNode *head = table->nodes[index];
    setNode *prev;
    while (head)
    {
        if (head->key == key)
        {
            if(head == table->nodes[index]){
                table->nodes[index] = head->next;
            }
            else{
                prev->next = head->next;
            }
            return head;
        }
        prev = head;
        head = head->next;
    }
    return NULL;
}

int main()
{
    struct set_table *table = set_table_new(hashmap_size);
    set_insert(table, "Pippo", hashmap_size, 45);
    set_insert(table, "Francesco", hashmap_size, 12);
    set_insert(table, "OkWooper", hashmap_size, 79);
    set_insert(table, "Kyogrez", hashmap_size, 80);
    set_insert(table, "Sassa", hashmap_size, 1);

    printf("Hai cercato: %s\n", search_node(table, "OkWooper", hashmap_size)->key);
    printf("Hai cercato: %d\n", search_and_return(table, "OkWooper", hashmap_size));
    RemoveNode(table, "Sassa", hashmap_size);
    printf("Hai cercato: %s\n", search_node(table, "Sassa", hashmap_size)->key);
    return 0;
}
