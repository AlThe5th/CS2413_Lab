#include <stdio.h>

//Define universal size of matrix
#define ROWS 4
#define COLS 5

//Function that does DFS traversal
void dfs(int grid[ROWS][COLS], int r, int c){
    //Stop traversal if matrix border or water hit
    if(r < 0 || c < 0 || r >= ROWS || c >= COLS || grid[r][c] == 0){
        return;
    }

    //Mark current cell as visited
    grid[r][c] = 0;

    //Visit all 4 adjacent directions
    dfs(grid, r + 1, c);
    dfs(grid, r - 1, c);
    dfs(grid, r, c + 1);
    dfs(grid, r, c - 1);
}

//Function that counts number of islands in matrix
int numIslands(int grid[ROWS][COLS]){
    int count = 0;

	//Loop each row and column to count 1s
    for(int r = 0; r < ROWS; r++){
        for(int c = 0; c < COLS; c++){
            if(grid[r][c] == 1){
                count++;
                dfs(grid, r, c);
            }
        }
    }
    return count;
}


int main(){
	//Initialize matrix
    int grid[ROWS][COLS] = {{1, 1, 1, 0, 0},
                            {1, 0, 1, 0, 1},
                            {0, 1, 0, 0, 0},
                            {1, 0, 0, 1, 0}};

	//Call island counter
    printf("Number of islands: %d\n", numIslands(grid));
}
