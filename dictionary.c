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
struct set_node *set_insert(struct set_table *table, const char *key, const size_t key_len, const int Value) // inserisce un elemento nella tabella
{
    size_t hash = djb33x_hash(key, key_len); // calcola l'hash della chiave
    size_t index = hash % table->hashmap_size; // calcola l'indice della tabella
    struct set_node *head = table->nodes[index]; // inizializza il nodo iniziale con il nodo dell'indice

    if(search_node(table, key, hashmap_size) != NULL) // se la chiave è già presente nella tabella
    {
        if(search_node(table, key, hashmap_size)->key == key) // se la chiave è già presente nella tabella
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
        head = malloc(sizeof(struct set_node)); // alloca la memoria per il nuovo nodo
        if (!head) // se il nuovo nodo non esiste
        {
            return NULL; // ritorna nullo
        }
        head->key = key; // assegna la chiave al nuovo nodo
        head->key_len = key_len; // assegna la lunghezza della chiave al nuovo nodo
        head->next = NULL; // assegna il nodo successivo a NULL
        head->value = Value; // assegna il valore al nuovo nodo
        table->nodes[index] = head; // assegna il nodo dell'indice con il nodo iniziale
        return head; // ritorna il nodo iniziale
    }
    struct set_node *new_item = malloc(sizeof(struct set_node)); // alloca la memoria per il nuovo nodo
    if (!new_item) // se il nuovo nodo non esiste
    {
        return NULL; // ritorna nullo
    }
    new_item->key = key; // assegna la chiave al nuovo nodo
    new_item->key_len = key_len; // assegna la lunghezza della chiave al nuovo nodo
    new_item->next = NULL; // assegna il nodo successivo a NULL 
    new_item->value = Value; // assegna il valore al nuovo nodo
    struct set_node *tail = head; // inizializza il nodo finale con il nodo iniziale 
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