#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define listNode struct list_node *
#define listAppend_Str(string) list_append((listNode *)&my_linked_list, (listNode)string_item_new(string));

struct list_node
{
    listNode next;
};
listNode list_get_tail(listNode *head)
{
    listNode current_node = *head;
    listNode last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

listNode list_append(listNode *head, listNode item) // serve per aggiungere un nodo ad una linked list
{
    listNode tail = list_get_tail(head);
    if (!tail)
    {
        *head = item; // se entra qui la linked list non ha nodi e lo mette come primo elemento
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}
listNode list_pop(listNode *head)  // rimuove il nodo alla testa della lista 
{
    listNode current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

void deleteNode(listNode *head, int position) // rimuove un nodo in qualsiasi posizione  cit.
{
    listNode temp = *head;
    listNode prev;

    if(position <= 0){
        position = 1;
    }

    for (int i = 0; i <= position; i++) //creo un ciclo per arrivare alla posizione richiesta
    {
        if (i == position)
        {
            prev->next = temp->next; // serve per assegnare il nodo attuale a quello successivo 
            free(temp); // free serve per liberare la memoria del nodo temporaneo
        }
        else
        {
            prev = temp; 
            if (temp == NULL)
            {
                break;
            }
            temp = temp->next; // assegno il nodo temporaneo a quello successivo
        }
    }
}


struct string_item // si possono creare liste di qualsiasi tipo 
{
    struct list_node node;
    const char *string;
};
struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}
int main()
{
    struct string_item *my_linked_list = NULL;
    listAppend_Str("HelloWorld");
    listAppend_Str("Test001");
    listAppend_Str("Test002");
    listAppend_Str("Last Item of the Linked List");
    deleteNode((listNode *)&my_linked_list, 0);
    struct string_item *string_item = my_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }
    return 0;
}