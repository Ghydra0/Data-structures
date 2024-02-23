#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct _node{
    int data;
    struct _node* next;
} Node;

typedef struct _list
{
    int count;
    Node* head;
} List;

// creates a new empty list
List* create_new_list() {
    List* my_new_list = (List*)malloc(sizeof(List)); 
    my_new_list->count = 0;
    my_new_list->head = NULL;
    return my_new_list;
} 

// create an empty node
Node* create_new_node() {
    Node* n0;
    n0 = NULL;
    n0 = (Node*)malloc(sizeof(Node)); 
    (*n0).data = 0;
    //n0->data = 0;
    n0->next = NULL;
    return n0;
} 

// create a node with a value
Node* create_node(int val) {
    Node* result = create_new_node();
    result->data = val;
    return result;
}

// add a node to front of list
int add_node_front(List* list, Node* n) {
    if (list == NULL)
        return -1;
    
    n->next = list->head;
    list->head = n;
    ++list->count;

    return 0;
}

// add a node to end of list
int add_node_last(List* list, Node* n) {
    if (list == NULL)
        return -1;

    if(list->head == NULL) {
        list->head = n;
        ++list->count;
        return 0;
    }

    Node* tmp = list->head;
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = n;

    ++list->count;
    return 0;
}

// add a node to the list in alphabetical order
int add_node_alphabetical(List* list, Node* n) {
    // check for special cases
    if (list == NULL){
        return -1;
    }
    if (list->head == NULL){
        list->head = n;
        ++list->count;
        return 0;
    }
    if (n->data < list->head->data){
        n->next = list->head;
        list->head = n;
        ++list->count;
        return 0;
    }

    Node* tmp = list->head;
    while (n->data > tmp->data){
        if (n->data < tmp->next->data)
        {
        n->next = tmp->next;
        tmp->next = n;
        ++list->count;
        return 0;
        }
        tmp = tmp->next;
    }
    return 0;

}

// print the list
int print_list(List* list) {
    if (list == NULL)
        return 0;
    
    Node* tmp = list->head;
    while(tmp != NULL) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }

    return 0;
}

// print the list recursively (not useful in this case, just for learning purposes)
int print_list_rec(Node* item) {
    if(item == NULL)
        return 0;
    
    printf("%d ", item->data);
    print_list_rec(item->next);
    
    return 0;
}

// print the list in reverse (uses recursive method seen before)
int print_list_rec_reverse(Node* item) {
    if(item == NULL)
        return 0;
    
    print_list_rec_reverse(item->next);
    printf("%d ", item->data);
    
    return 0;
}

// find an integer in the list
bool find_int(List* list, int a) {
    if (list == NULL)
        return false;

    Node* tmp = list->head;
    while(tmp != NULL) {
        if (tmp->data == a)
            return true;
        tmp = tmp->next;
    }

    return false;
}

// remove a node from the list
Node* remove_node(List* list, int key){
    if(list == NULL)
        return NULL;

    if(list->head == NULL)
        return NULL;

    Node* tmp = list->head;
    if(list->head->data == key) {
        list->head = list->head->next;
        tmp->next = NULL;
        --list->count;
        return tmp;
    }

    while(tmp->next != NULL) {
        if(tmp->next->data == key) {
            Node* sub = tmp->next;
            tmp->next = sub->next;
            sub->next = NULL;
            --list->count;
            return sub;
        }
        tmp = tmp->next;
    }

    return NULL;
}

// delete a node
int delete_node(List* list, int key){
    Node* tmp = remove_node(list, key);
    if(tmp != NULL) {
        free(tmp);
        tmp = NULL;
    }
    return 0;
}

// returns a count of elements in a list
int count_elements(List* list) {
    if (list == NULL)
        return 0;
    Node* tmp = list->head;
    int count = 0;
    for (; tmp != NULL; ++count) {
        tmp = tmp->next;
    }
    return count;
}

// copy a list
List* copy_list(List* list) {
    if (list == NULL)
        return NULL;
    List* new_list = create_new_list();
    Node* tmp = list->head;
    while(tmp != NULL) {
        add_node_last(new_list, create_node(tmp->data));
        tmp = tmp->next;
    }
    return new_list;
}

// removes N elements from front of list
int remove_n_from_front(List* list, int n) {
    if (list == NULL)
        return -1;
    if (list->head == NULL)
        return -1;
    if (n > list->count)
        return -1;
        
    Node* tmp = list->head;
    for (int i = 0; i < n; i++)
    {
        int sub_node = tmp->data;
        tmp = tmp->next;
        delete_node(list, sub_node);
    }
    return 0;
}

// returns sum of all nodes in a list
int sum_list(List* list) {
    if (list == NULL)
        return -1;
    if (list->head == NULL)
        return -1;
    
    Node* tmp = list->head;
    int sum = 0;
    while (tmp != NULL) {
        sum += tmp->data;
        tmp = tmp->next;
    }
    return sum;
}

// moves last element to the beginning of list
int move_last_to_head(List* list) {
    if (list == NULL)
        return -1;
    if (list->head == NULL)
        return -1;

    Node* tmp = list->head;
    // parse list to find second to last node
    while (tmp->next->next != NULL) {
        tmp = tmp->next;
    }
    // move last node to the front
    tmp->next->next = list->head; // last nodes next is the current head
    list->head = tmp->next; // last node becomes head
    tmp->next = NULL; // second to last node points to NULL, thus becoming the last node
    return 0;
}

// function testing
int main() {

    Node* n0 = create_node(9);
    Node* n1 = create_node(4);
    Node* n2 = create_node(19);

    List* list = create_new_list();
    add_node_front(list, n0);
    add_node_front(list, n1);
    add_node_last(list, n2);
    List* list2 = copy_list(list);
    add_node_last(list, create_node(22));
    add_node_alphabetical(list, create_node(5));

    print_list(list);
    printf("\n");
    print_list_rec(list->head);
    printf("\n");
    print_list_rec_reverse(list->head);
    printf("\n");
    printf("Count: %d\n", count_elements(list));
    print_list(list2);
    printf("\n");
    remove_n_from_front(list2, 2);
    print_list(list2);
    printf("\n");
    printf("sum of values: %d \n", sum_list(list));
    move_last_to_head(list);
    print_list(list);

    bool a = find_int(list, 4);
    a = find_int(list, 9);
    a = find_int(list, 22);
    a = find_int(list, 0);

    free(n0); 
    n0 = NULL;

    free(n1);
    n1 = NULL;
    
    return 0;
}