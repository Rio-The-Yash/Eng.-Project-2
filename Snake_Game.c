/*
 * This program implements a simple snake game.
 *
 * Author: Yash Gandhi, Jwal Patel and Claricel Ramos
 * Date: March 27, 2024
 * GitHub Repository link:- https://github.com/Rio-The-Yash/Snake-game/tree/proj_II_w_6
 */

/*
 * Header files needed for the project
 */
#include <stdio.h>
#include <conio.h> // _kbhit() _getch()
#include <windows.h> // Sleep()
#include <unistd.h> // system("cls")
#include <time.h> // srand and rand

// defining numbers for the directions
enum Input { UP, DOWN, LEFT, RIGHT};

// defining the number of the rows and columns
#define ROWS    30
#define COLS    30

// Define the user struct
typedef struct {
    int headX;
    int headY;
} Position;

// Define the queue node struct
typedef struct QueueNode {
    Position data; // Data stored in the node (a User struct)
    struct QueueNode *next; // Pointer to the next node in the queue
} QueueNode;

// Global variable declaration for the head of the linked list
QueueNode* head = NULL; // Initialize head pointer to NULL
	
char userInput;
// defining the sleep time and speed for the snake
int updater = 100;
int level = 1;

int foodX ,foodY;

// end game flag  : 0 or 1
int gameover;
int direction;

// grow snake flag -> to mimic if food eaten
int grow;

int gameStarted = 0;  // Variable to track whether the game has started or not
int score=0;

// Function to generate a random food location
void createList(int row, int col) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode)); // Allocate memory for a new node

    newNode->data = (Position){row,col}; // Assign data to the new node
    newNode->next = NULL; // Initialize next pointer to NULL
    head = newNode; // Update head to point to the new node
}

// Function to add an element to the beginning of the list
void addElementToList(int row, int col) // int row , int col
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode)); // Allocate memory for a new node
    if (newNode == NULL) { // Check if memory allocation failed
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = (Position){row,col}; // Assign data to the new node

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
        printf("(%d, %d) ", current->data.headX, current->data.headY); // Print data of each node
        current = current->next; // Move to the next node
    }
    printf("\n");
}

void generateFood() {
    struct QueueNode *current = head;
    int overlap = 1;
    // From the start food will be placed randomly but then it will check if the food is either on the head or on the body of the snake 
    while (overlap) {
        overlap = 0;
        foodX = rand() % (COLS - 2) + 1;
        foodY = rand() % (ROWS - 2) + 1;
		
        while(current!=NULL){
			if (foodX == current->data.headX && foodY == current->data.headY) {
            	overlap = 1; // Collision detected
            	break;
        	}
        current = current->next;
		}
    }
}

// initialization for the random position of the head and initial direction of the snake 
void setup() {
    createList(rand() % (COLS - 2) + 1, rand() % (ROWS - 2) + 1); // Randomly initialize snake's head position
    generateFood(); // Generate initial food position
    direction = RIGHT; // Set initial direction of the snake
}

// function to resume the game oncce 
void resumeGame() {
    gameStarted = 1;
}

// function to pause the game
void pauseGame() {
    gameStarted = 0;
    // if the user hit c it will again resume the game
    while (1) {
        if (_kbhit()) {
            userInput = _getch();
            if (userInput == 'c') {
                resumeGame();
                break;
            }
        }
    }
}

// function to draw the playing area, head and the tail of the snake
void draw() {
    system("cls");
	QueueNode* current = head;
	// upper wall
    for (int i = 0; i < ROWS; i++)
        printf("*");
    printf("\n");
	
	// Draws right,left wall and head, tail of the snake
    for (int i = 0; i < COLS; i++) {
    	current = head;
        for (int j = 0; j < ROWS; j++) {
            if (j == 0 || j == ROWS - 1)
                printf("*");
            else if (i == foodY && j == foodX)
                printf("0");
            else if (current->data.headX == j && current->data.headY == i) {
                printf("@");
            }
            else {
                int printed = 0;
                if (!printed)
                    printf(" ");
            }
        }
        printf("\n");
    }
    
	// for loop to make the lower border of  the play area
    for (int i = 0; i < ROWS ; i++)
        printf("*");
    printf("\n");
    printf("\n");

    printf("Level: %d\nScore: %d\n", level, score); // updates score after successfully eating the food
    printf("Position = (%d , %d)\n", current->data.headX, current->data.headY);
    printf("Press 'p' to pause the game\nPress 'c' to resume the game\nPress 'x' to quit the game");
//		printList();
}

// function to get input fromt the user to get the directions for the movement of the snake and to exit or start the program 
void input() {
    if (_kbhit()) {
        userInput = _getch();
        switch (userInput) {
            case 'w':
                if (direction != DOWN)
                    direction = UP;
                break;
            case 's':
                if (direction != UP)
                    direction = DOWN;
                break;
            case 'a':
                if (direction != RIGHT)
                    direction = LEFT;
                break;
            case 'd':
                if (direction != LEFT)
                    direction = RIGHT;
                break;
            case 'x':
                gameover = 1;
                break;
            case 'p':
            	pauseGame();
            	break;
            case 'c':
            	resumeGame();
            	break;
            default:
                break;
        }
    }
}

void levelUp() {
    if (score % 100 == 0 && score > 0) {
        updater -= 10; // Increase the game speed
        score += 10;
		level ++;   // Increase score as a reward for leveling up
        printf("Level Up! Game Speed Increased!\n");
    }
}

// function on which the main logic will work for the movement of the head and tail of the snake and how the tail will grow after giving the input 
void algorithm() {

	// logic for the movement of the snake in all directions
    switch (direction) {
        case UP:
            head->data.headY--;
            break;
        case DOWN:
            head->data.headY++;
            break;
        case LEFT:
            head->data.headX--;
            break;
        case RIGHT:
            head->data.headX++;
            break;
        default:
            break;
    }

	// game will end once the snake touches the border of the play area
    if (head->data.headX >= ROWS - 1 || head->data.headX < 0 || head->data.headY < 0 || head->data.headY >= COLS)
        gameover = 1;
	

	// logic for eating the food and the growth of the tail 
    if (foodX == head->data.headX && foodY == head->data.headY) {
    score += 10;
    generateFood();
	}

}

// initialization which will pop-up once we run the program
void Init() {
    printf("+------------+\n");
    printf("| SNAKE GAME |\n");
    printf("+------------+\n");
    printf("Press 'j' to start the game and 'x' to quit.\n");
    printf("Press 'w' to make the snake go UP\n");
    printf("Press 's' to make the snake go DOWN\n");
    printf("Press 'a' to make the snake go LEFT\n");
    printf("Press 'd' to make the snake go RIGHT\n");
    printf("Press 'c' to restart the game\n");

	// code will only accepts the value 'j' and 'x' as an input and the rest will be discarded
    while (userInput != 'j' && userInput != 'x') {
        userInput = _getch();
    }

    if (userInput == 'j') {
        gameStarted = 1; // Start the game if 'j' is pressed initially
        setup();
    }
    system("cls");
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    Init();
    while (!gameover){
    
		while (!gameover) {
    	    if (gameStarted) {
        	    draw();
            	input();
	            algorithm();
	            levelUp();
				Sleep(updater);
        	}
	    }
    	system("cls");
	    printf("GAME OVER!!\nScore:- %d\n",score);
    	printf("Do you want to quit the game or restart the Game??\nPress 'r' to restart and 'x' to quit");
    
    	userInput = _getch();
    // if the user will hit 'r' or 'x' the system will get it do appropriate function
    	while(userInput != 'r' && userInput != 'x'){
			userInput = _getch();
		}
    	
	    if (userInput == 'r') {
    	    gameover = 0;
    	    system("cls");
        	Init();
    	}
    	
    	if (userInput == 'x'){
    		gameover = 1;
		}
	}
	deleteList();
    return 0;
}
