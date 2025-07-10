#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 10

char maze[HEIGHT][WIDTH + 1];
int playerX, playerY;
int moveCount = 0;
time_t startTime;

void loadMazeFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error loading maze from %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < HEIGHT; i++) {
        fgets(maze[i], WIDTH + 2, file); // +2 for newline and null terminator
        for (int j = 0; j < WIDTH; j++) {
            if (maze[i][j] == 'P') {
                playerY = i;
                playerX = j;
            }
        }
    }

    fclose(file);
}

void drawMaze() {
    system("cls"); // Use "clear" if on Linux/Mac
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s", maze[i]);
    }
    printf("\nMoves: %d\n", moveCount);
    printf("Time: %ld seconds\n", time(NULL) - startTime);
}

void movePlayer(char dir) {
    int newX = playerX;
    int newY = playerY;

    if (dir == 'w') newY--;
    else if (dir == 's') newY++;
    else if (dir == 'a') newX--;
    else if (dir == 'd') newX++;
    else if (dir == 'q') {
        printf("Game exited by user.\n");
        exit(0);
    }
    else return;

    char target = maze[newY][newX];
    if (target == ' ' || target == 'G') {
        maze[playerY][playerX] = ' ';
        playerX = newX;
        playerY = newY;
        maze[playerY][playerX] = 'P';
        moveCount++;
        if (target == 'G') {
            drawMaze();
            printf("\n🎉 You reached the goal in %d moves and %ld seconds!\n", moveCount, time(NULL) - startTime);
            exit(0);
        }
    } else if (target == 'X') {
        printf("Blocked by obstacle!\n");
    }
}

int main() {
    char input;
    startTime = time(NULL);

    loadMazeFromFile("level1.txt");

    while (1) {
        drawMaze();
        printf("Enter move (w/a/s/d), 'q' to quit: ");
        scanf(" %c", &input);
        movePlayer(input);
    }

    return 0;
}
