#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct node {
    void* data;
    struct node* next;
} node;
 
typedef struct Person {
    char name[50];
    int age;
} Person;
 
Person create_person() {
    char name[50];
    int age;
 
    printf("\nEnter name name: ");
    scanf("%s", name);
    printf("Enter the age: ");
    scanf("%d", &age);
 
    Person p;
    strcpy(p.name, name);
    p.age = age;
 
    return p;
}
 
void clean_list(node** head) {
    while ((*head)->data != NULL) {
        node* old_head = *head;
        *head = (*head)->next;
        free(old_head);
    }
}
 
void insert_node(node** head, void* value, size_t data_size, int (*cmp)(const void*, const void*)) {
    // Create a new node to be inserted
    node* new_node = (node*)malloc(sizeof(*new_node));
    new_node->data = malloc(data_size);
    memcpy(new_node->data, value, data_size);
    new_node->next = NULL;
 
    // If the list is empty or the new node's value is not bigger than the head's value,
    // set the new node as the head of the list
    if ((*head)->data == NULL || cmp(value, (*head)->data) < 1) {
        new_node->next = *head;
        *head = new_node;
    }
    else {
        // Traverse the list to find the proper place to insert the new node
        node* current = *head;
        while (current->next->data != NULL && cmp(value, current->next->data) == 1) {
            current = current->next;
        }
        // Insert the new node after the current node
        new_node->next = current->next;
        current->next = new_node;
    }
}
 
void delete_node(node** head, void* value, size_t data_size, int(*cmp)(const void*, const void*)) {
 
    // list is empty
    if ((*head)->data == NULL) {
        printf("List is empty. There is nothing to deleted\n");
        return;
    }
 
    // head is equal to the value
    if (cmp((*head)->data, value) == 0) {
        node* old_head = *head;
        *head = (*head)->next;
        free(old_head);
        return;
    }
 
    // traversing through the list to find the element to be deleted
    // stop when encoutering bigger value than the one to be deleted
    node* current = (*head);
    while (current->next->data != NULL && cmp(value, current->next->data) == 1) {
        current = current->next;
    }
 
    // element is not in the list
    if (current->next->data == NULL || (current->next->data != NULL && cmp(value, current->next->data) != 0)) {
        printf("Selected value is not in the list\n");
        return;
    }
 
    // now, current->next must be equal to the value being deleted
    node* deleted_node = current->next;
    current->next = current->next->next;
    free(deleted_node);
}
 
void print_list(node* head, void (*print)(const void*)) {
    node* current = head;
    while (current->data != NULL) {
        print(current->data);
        current = current->next;
    }
    printf("\n");
}
 
// comparisons
//  0 -> equal
// -1 -> a < b
//  1 -> a > b
int cmp_int(const void* a, const void* b) {
    const int* pa = (int*)a;
    const int* pb = (int*)b;
    return *pa < *pb ? -1 : *pa > *pb;
}
 
int cmp_str(const void* a, const void* b) {
    const char* str_a = (char*)a;
    const char* str_b = (char*)b;
    return strcmp(str_a, str_b);
}
 
// people sorted by the age in ascending order
int cmp_custom(const void* a, const void* b) {
    const Person* person_a = (Person*)a;
    const Person* person_b = (Person*)b;
    return person_a->age < person_b->age ? -1 : person_a->age > person_b->age;
}
 
// printings
void print_int(const void* a) {
    int* pa = (int*)a;
    printf("%d ", *pa);
}
 
void print_str(const void* a) {
    const char* str_a = (char*)a;
    printf("\"%s\" ", str_a);
}
 
void print_custom(const void* a) {
    const Person* person_a = (Person*)a;
    printf("{Name: %s, Age: %d}\n", person_a->name, person_a->age);
}
 
 
int main(int argc, char** argv) {
 
    int (*cmp)(const void*, const void*) = NULL;
    void (*print)(const void*) = NULL;
 
    int type_choice, valid_input = 0, run = 1, action;
    char c;
 
    node* list = (node*)malloc(sizeof(node));
    list->data = NULL;
    list->next = NULL;
 
    size_t data_size;
 
    int int_value;
    char str_value[100];
 
 
    printf("Welcome to generic sorted linked list :D\nChoose your datatype:\n");
    printf("1. Integer\n");
    printf("2. String\n");
    printf("3. Object: Person {name: String, age: Int} - sorted by age\n");
    printf("------------------------------------------------------------------\n");
 
    do {
        printf("ENTER THE NUMBER (between 1 and 3): ");
        valid_input = scanf("%d", &type_choice);
 
        if (valid_input != 1) {
            printf("Invalid input. Please enter a valid integer.\n");
            while ((c = getchar()) != '\n' && c != EOF); // clear input buffer
        }
 
    } while (valid_input != 1 || type_choice < 1 || type_choice > 3);
 
    if (type_choice == 1) {
        printf("Your choice is Integer.\n");
        data_size = sizeof(int);
        cmp = cmp_int;
        print = print_int;
    }
    else if (type_choice == 2) {
        printf("Your choice is String.\n");
        data_size = 100 * sizeof(char);
        cmp = cmp_str;
        print = print_str;
    }
    else if (type_choice == 3) {
        printf("Your choice is Person object.\n");
        data_size = sizeof(Person);
        cmp = cmp_custom;
        print = print_custom;
    }
 
 
    while (run) {
 
        printf("------------------------------------------------------------------\n");
        printf("Available actions:\n");
        printf("1. Add element to the list\n");
        printf("2. Delete an element from the list\n");
        printf("3. Print the list\n");
        printf("4. EXIT\n");
        printf("------------------------------------------------------------------\n");
 
        do {
            printf("ENTER THE NUMBER (between 1 and 4): ");
            valid_input = scanf("%d", &action);
 
            if (valid_input != 1) {
                printf("Invalid input. Please enter a valid integer.\n");
                while ((c = getchar()) != '\n' && c != EOF); // clear input buffer
            }
        } while (valid_input != 1 || action < 1 || action > 4);
 
        switch (action)
        {
        case 1:
            printf("Selected action: Adding element to the list.\n");
            printf("Enter the value to be added: ");
 
            switch (type_choice)
            {
            case 1:
                scanf("%d", &int_value);
                insert_node(&list, &int_value, data_size, cmp);
                break;
 
            case 2:
                scanf("%s", str_value);
                insert_node(&list, str_value, data_size, cmp);
                break;
 
            case 3:
                struct Person p = create_person();
                insert_node(&list, &p, data_size, cmp);
                break;
 
            default:
                break;
            }
            break;
 
        case 2:
            printf("Selected action: Removing an element from the list.\n");
            printf("Enter the value to be deleted: ");
 
            switch (type_choice)
            {
            case 1:
                scanf("%d", &int_value);
                delete_node(&list, &int_value, data_size, cmp);
                break;
 
            case 2:
                scanf("%s", str_value);
                delete_node(&list, str_value, data_size, cmp);
                break;
 
            case 3:
                printf("(age of person that will be deleted) ");
                scanf("%d", &int_value);
                Person p;
                p.age = int_value;
 
                delete_node(&list, &p, data_size, cmp);
                break;
 
            default:
                break;
            }
            break;
 
        case 3:
            printf("Selected action: Printing the list.\n");
            print_list(list, print);
            break;
 
        case 4:
            clean_list(&list);
            free(list);
            run = 0;
            break;
 
        default:
            break;
        }
 
    }
 
    return 0;
 
}
