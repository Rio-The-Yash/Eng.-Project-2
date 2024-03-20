# Eng.-Project-2
### Linked List Implementation in C

This C program demonstrates the implementation of a linked list data structure using a queue. The program allows adding, removing, searching for elements, and deleting the entire list. Here's a breakdown of the components:

#### Source Code Files
- **main.c**: Contains the main program logic and function implementations for linked list operations.

#### Functionality

1. **Printing the List**: Prints the elements of the linked list.
2. **Adding Elements to the List**: Adds elements to the beginning of the linked list.
3. **Removing Elements from the List**: Removes elements from the end of the linked list.
4. **Searching for Elements**: Searches for duplicate elements within the linked list.
5. **Deleting the Entire List**: Deletes all elements from the linked list.

#### Compilation and Execution

To compile and run the program, follow these steps:

1. Ensure you have a C compiler installed (e.g., GCC).
2. Navigate to the directory containing the source code files.
3. Compile the program using the command: `gcc main.c -o linked_list`
4. Run the compiled program: `./linked_list`

#### Sample Output

```
List is empty!
Linked List: (7, 8) (5, 6) (3, 4) (1, 2)
Element found: No
After removing element:
Linked List: (7, 8) (5, 6) (3, 4)
After removing second element and adding new one:
Linked List: (9, 0) (7, 8) (5, 6)
After deleting all elements from the list:
List is empty!
```

#### Notes

- The program demonstrates basic operations on a linked list such as adding, removing, searching, and deleting.
- It uses a queue-like structure where elements are added to the beginning and removed from the end.
