/*
Mason Manca
CPSC 346 Section 02
Dr. Zhang
Sept. 9 2022
*/

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

void MakeNode(struct node** head,int data);
struct node* Merge(struct node* head1, struct node* head2);
struct node* MergeSort(struct node* head, int size);
void Split(struct node* head1, struct node** head2, int mid_point);
void PrintList(struct node* head);
int GetSize(struct node* head);

/*
This function creates a node at the end of a linkedList, also is used for intialzing the list
@ returns nothing, but edits head through pointer
*/

void MakeNode(struct node** head,int data){
    if(*head == NULL){
        *head = (struct node*) malloc(sizeof(struct node));
        (*head)-> next = NULL;
        (*head)-> data = data;
    }
    else{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));

    new_node->data = data; //store data in new linked list ( essentially the head )
    new_node->next = NULL; 
    struct node* temp = *head;
    while(temp->next != NULL){ // iterates through linked list in order to add it to the tail 
        temp = temp->next;
    }
    temp->next = new_node;
    }
}

/*
This function prints the linked list starting at the head and continuing until the end(NULL)
@ No return, takes in singular head as parameter
*/
void PrintList(struct node* head){

    while(head != NULL){
        printf("%d\n",head->data);
        head = head->next;
    }
}

/*
This function takes in a head as a parameter, and determines the size of the linked list
@ returns int size
*/
int GetSize(struct node* head1){
    int size = 0;
    struct node* temp = head1;
    while(temp != NULL){ // iterates through list until end
        temp = temp->next;
        size += 1;
    }
    return size;
}

/*
Split function finds the mid_point and separates linked list into two sublists
@ no return, takes in 2 heads and a midpoint value to split upon
*/
void Split(struct node* head1, struct node** head2, int mid_point){
    for (int i = 1; i < mid_point; i++) {
        head1 = head1->next;
    }
    *head2 = head1->next; // head2 now start of second sublist
    head1->next = NULL;

}

/*
Function responsible for merging the list back together once sorted
@ returns the head of a new sorted linked list
*/
struct node* Merge(struct node* head1, struct node* head2){
    struct node* new_head = NULL;
    // This loop is for the sorting of the sublists into a singular merged list
    while(!(head1 == NULL && head2 == NULL))
    {
        if(head2 == NULL) {
            MakeNode(&new_head, head1->data);
            head1 = head1->next;
        }
        else if (head1 == NULL) {
            MakeNode(&new_head, head2->data);
            head2 = head2->next;
        }
        else if (head1->data >= head2->data){
            MakeNode(&new_head, head2->data);
            head2 = head2->next;
        }
        else {
            MakeNode(&new_head, head1->data);
            head1 = head1->next;
        }

    }
    return new_head;
}


/*
This is the main merge sort function, it takes in the entire linked list
*/
struct node* MergeSort(struct node* head, int size){

    struct node* head1 = head;
    struct node* head2 = NULL;
    int mid_point = size / 2;

    if (size <= 1) {
        return head;
    }
    Split(head, &head2, mid_point);
    head1 = MergeSort(head1, GetSize(head1));
    head2 = MergeSort(head2, GetSize(head2));

    return Merge(head1, head2);
}


int main(int argc, char *argv[]) {

    struct node* linkedList1 = NULL; // initial linked list
    struct node* linkedList2 = NULL; 
    struct node* merged = NULL; // end sorted list
    
    MakeNode(&linkedList1,1);
    MakeNode(&linkedList1,3);
    MakeNode(&linkedList1,2);
    MakeNode(&linkedList1,4);
    MakeNode(&linkedList1,6);
    MakeNode(&linkedList1,5);

    printf("Checking nodes are in list: \n");
    PrintList(linkedList1); // ensure all nodes are in the list

    merged = Merge(linkedList1, linkedList2); // checking merge() as specified in parameters
    printf("Original: \n"); 
    PrintList(merged);

    merged = MergeSort(merged, GetSize(merged)); // print the final merged linkedList
    printf("Sorted list: \n");
    PrintList(merged);
}