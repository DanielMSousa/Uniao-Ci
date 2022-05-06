#include "TAD.h"


int main(){
    List* list = create_list();
    add_node(list, 2);
    add_node(list, 4);
    add_node(list, 3);
    add_node(list, 5);
    add_node(list, 6);
    add_node(list, 5);
    print_list(list);
    free_list(list);
    return 0;
}