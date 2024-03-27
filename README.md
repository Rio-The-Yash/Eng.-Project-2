## Snake Game

This repository contains a simple implementation of the classic Snake game in C. The game is built using a console-based interface and allows players to control a snake that moves around a grid, eating food to grow longer. The game ends when the snake collides with the walls or itself.

### How to Play

1. **Controls**:
   - Use the `w`, `a`, `s`, and `d` keys to control the movement of the snake: UP, LEFT, DOWN, and RIGHT respectively.
   - Press `p` to pause the game and `c` to resume.
   - Press `x` to quit the game.

2. **Objective**:
   - Guide the snake to eat the food (displayed as `0`) to grow longer.
   - Avoid collisions with the walls or the snake's own body.

3. **Scoring**:
   - Each food item eaten increases the player's score by 10 points.
   - The game speeds up and the player advances a level every time the score reaches a multiple of 100.

### Implementation Details

#### 1. Grid Representation
- The game grid is represented by a 2D array.
- The snake's position is tracked using a linked list, where each node represents a segment of the snake's body.
- The head of the snake is represented by `@`, and the body segments by empty spaces.

#### 2. Movement Logic
- The snake's movement logic is based on user input.
- The snake moves one step in the direction specified by the user in each game iteration.
- The snake's direction can only be changed to a perpendicular direction to prevent self-collisions.

#### 3. Food Generation
- Food is randomly generated on the grid.
- The position of the food is checked to ensure it does not overlap with the snake's body.
- When the snake eats food, its length increases, and a new food item is generated at a random location.

#### 4. Game Over Conditions
- The game ends if the snake collides with the walls of the grid or with its own body.

#### 5. Level Up Mechanism
- As the player scores points, the game speed increases.
- Every time the score reaches a multiple of 100, the player advances to the next level, and the game speed increases further.


### Contributors

- **Yash Gandhi** - [GitHub](https://github.com/Rio-The-Yash)
- **Jwal Patel**
- **Claricel Ramos**

### Notes

- The game provides a simple yet enjoyable experience within a console window.
- Players can customize and extend the game by modifying the source code.
- Feedback and contributions are welcome. Please feel free to open issues or create pull requests.

--- 

This README file provides comprehensive explanations of the game's mechanics and implementation details. Users can refer to it for a deeper understanding of how the game functions and how to interact with it.
