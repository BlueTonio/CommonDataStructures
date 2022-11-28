#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define setNode struct set_node

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}
struct set_node
{
    const char *key;
    size_t key_len;
    setNode *next;
};
struct set_table
{
    setNode **nodes;
    size_t hashmap_size;
};
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

setNode *set_insert(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *head = table->nodes[index];
    if (!head)
    {
        table->nodes[index] = malloc(sizeof(struct set_node));
        if (!table->nodes[index])
        {
            return NULL;
        }
        table->nodes[index]->key = key;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->next = NULL;
        return table->nodes[index];
    }
    setNode *new_item = malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return NULL;
    }
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL;
    struct set_node *tail = head;
    while (head)
    {
        if(head->key == key){
            return NULL;
        }
        tail = head;
        head = head->next;
    }
    tail->next = new_item;
    return new_item;
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
    const int hashmap_size = 10;
    struct set_table *table = set_table_new(hashmap_size);
    set_insert(table, "Pippo", hashmap_size);
    set_insert(table, "Francesco", hashmap_size);
    set_insert(table, "OkWooper", hashmap_size);
    set_insert(table, "Kyogrez", hashmap_size);
    set_insert(table, "Sassa", hashmap_size);

    printf("Hai cercato: %s\n", search_node(table, "OkWooper", hashmap_size)->key);
    RemoveNode(table, "OkWooper", hashmap_size);
    printf("Hai cercato: %s\n", search_node(table, "Sassa", hashmap_size)->key);
    return 0;
}
