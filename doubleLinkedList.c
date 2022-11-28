#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <stddef.h>
#define listNode struct list_node *
#define listAppend_Str(string) list_append((listNode *)&my_linked_list, (listNode)string_item_new(string));
struct list_node
{
    listNode prev;
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
listNode list_append(listNode *head, listNode item)
{
    listNode tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
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
    (*head)-> prev = NULL;
    current_head->next = NULL;
    return current_head;
}
void deleteNode(listNode *head, int position){
    listNode nodeToRemove = *head;
    listNode prev;

    if(position <= 0){
        list_pop(head);
        return;
    }

    for (int i = 0; i <= position; i++) 
    {
        if (i == position)
        {
            prev->next = nodeToRemove->next; 
            nodeToRemove->next->prev = prev; 
            free(nodeToRemove);
        }
        else
        {
            if (!nodeToRemove)
            {
                break;
            }
            prev = nodeToRemove; 
            nodeToRemove = nodeToRemove->next; 
        }
    }
}

void addItemAfter(listNode nodeToAdd, listNode prevNode)
{
    if(!prevNode){
        return;
    }
    nodeToAdd->prev = prevNode;
    nodeToAdd->next = prevNode->next;
    if(prevNode->next){
        prevNode->next->prev = nodeToAdd;
    }
    prevNode->next = nodeToAdd;
}

void addItemBefore(listNode nodeToAdd, listNode nextNode)
{
    if(!nextNode){
        return;
    }
    nodeToAdd->next = nextNode;
    nodeToAdd->prev = nextNode->prev;
    if(nextNode->prev){
        nextNode->prev->next = nodeToAdd;
    }
    nextNode->prev = nodeToAdd;
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
    listNode b = listAppend_Str("Test002");
    listNode c = listAppend_Str("Last Item of the Linked List");
    struct string_item *string_item = my_linked_list;
    //deleteNode((listNode *)&my_linked_list, 1);
    addItemBefore((listNode) string_item_new("pippa"), c);
    addItemAfter((listNode) string_item_new("pippo"), c);
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (struct string_item *)string_item->node.next;
    }
    return 0;
}