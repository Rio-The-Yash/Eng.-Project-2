#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the user struct
typedef struct {
    int row;
    int col;
} Position;

// Define the queue node struct
typedef struct QueueNode {
    Position data; // Data stored in the node (a User struct)
    struct QueueNode *next; // Pointer to the next node in the queue
} QueueNode;

// Global variable declaration for the head of the linked list
QueueNode* head = NULL; // Initialize head pointer to NULL

// Function to create a new node
QueueNode* createList(Position data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode)); // Allocate memory for a new node
    if (newNode == NULL) { // Check if memory allocation failed
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data; // Assign data to the new node
    newNode->next = NULL; // Initialize next pointer to NULL
    return newNode;
}

// Function to add an element to the beginning of the list
void addElementToList(Position data) {
    QueueNode* newNode = createList(data); // Create a new node
    newNode->next = head; // Set the next pointer of the new node to the current head
    head = newNode; // Update head to point to the new node
}

// Function to remove an element from the end of the list
void removeElementFromList() {
    if (head == NULL) { // Check if the list is empty
        printf("List is empty!\n");
        return;  
    }
    if (head->next == NULL) { // Check if there is only one node in the list
        free(head); // Free memory of the single node
        head = NULL; // Update head to NULL
        return;
    }
    QueueNode* current = head;
    while (current->next->next != NULL) { // Traverse the list until the second last node
        current = current->next;
    }
    free(current->next); // Free memory of the last node
    current->next = NULL; // Set next pointer of second last node to NULL
}

// Function to search for an element in the list
int searchList() {
    if (head == NULL || head->next == NULL) // If the list is empty or has only one element, there are no duplicates
        return 0;

    QueueNode* current = head;
    QueueNode* compare;

    while (current != NULL) 
    {
        compare = current->next; // Start comparing from the node next to the current node
        while (compare != NULL) 
        {
            if (current->data.row == compare->data.row && current->data.col == compare->data.col)
                return 1; // Duplicate found
            compare = compare->next;
        }
        current = current->next;
    }
    return 0; // No duplicates found
}


// Function to delete the entire list
void deleteList() {
    QueueNode* current = head;
    QueueNode* next;
    while (current != NULL) { // Traverse the list
        next = current->next; // Store next node pointer
        free(current); // Free memory of the current node
        current = next; // Move to the next node
    }
    head = NULL; // Set head to NULL after deleting all nodes
}

// Function to print the list
void printList() {
    if (head == NULL) { // Check if the list is empty
        printf("List is empty!\n");
        return;
    }
    printf("Linked List: ");
    QueueNode* current = head;
    while (current != NULL) { // Traverse the list
        printf("(%d, %d) ", current->data.row, current->data.col); // Print data of each node
        current = current->next; // Move to the next node
    }
    printf("\n");
}

int main() {
    // Function calls to showcase capabilities
    printList(); // Print empty list
    addElementToList((Position){1, 2}); // Add elements to the list
    addElementToList((Position){3, 4});
    addElementToList((Position){5, 6});
    addElementToList((Position){7, 8});
    // addElementToList((Position){3, 4});
    printList(); // Print list
    printf("Element found: %s\n", searchList() ? "Yes" : "No"); // Search for an element
    removeElementFromList(); // Remove an element
    printf("After removing element:\n");
    printList(); // Print list after removal

    removeElementFromList(); // Remove another element
    addElementToList((Position){9, 0});
    printf("After removing second element and adding new one:\n");
    printList(); // Print list after removal
    deleteList(); // Delete entire list
    printf("After deleting all elements from the list:\n");
    printList(); // Print list after deletion
    
    return 0;
}
