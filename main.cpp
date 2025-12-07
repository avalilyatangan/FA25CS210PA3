//
// Created by Manju Muralidharan on 11/22/25.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Directions for DFS (students must use these)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// ----------------------------------------------------------
// DO NOT MODIFY: Maze generation
// ----------------------------------------------------------
void generateMaze(vector<vector<int>>& maze, int N, int M) {
    srand(time(0));

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int roll = rand() % 100;
            maze[r][c] = (roll < 70) ? 0 : 1;   // 0 = open, 1 = wall
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Choose a random boundary cell that is open
// ----------------------------------------------------------
pair<int,int> chooseBoundaryCell(const vector<vector<int>>& maze) {
    int N = maze.size();
    int M = maze[0].size();

    while (true) {
        int side = rand() % 4;
        int r, c;

        if (side == 0) {          // top row
            r = 0;
            c = rand() % M;
        } else if (side == 1) {   // bottom row
            r = N - 1;
            c = rand() % M;
        } else if (side == 2) {   // left column
            r = rand() % N;
            c = 0;
        } else {                  // right column
            r = rand() % N;
            c = M - 1;
        }

        if (maze[r][c] == 0) {
            return {r, c};
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the maze with S and E markers
// ----------------------------------------------------------
void printMaze(const vector<vector<int>>& maze,
               int ent_r, int ent_c,
               int exit_r, int exit_c)
{
    int N = maze.size();
    int M = maze[0].size();

    cout << "\nMaze:\n";
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (r == ent_r && c == ent_c) {
                cout << "S ";
            } else if (r == exit_r && c == exit_c) {
                cout << "E ";
            } else {
                cout << maze[r][c] << " ";
            }
        }
        cout << "\n";
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the reconstructed path
// Students must fill parent[][] correctly during DFS
// ----------------------------------------------------------
void printPath(pair<int,int> exitcell,
               const vector<vector<int>>& parent_r,
               const vector<vector<int>>& parent_c,
               int ent_r, int ent_c)
{
    int r = exitcell.first;
    int c = exitcell.second;

    vector<pair<int,int>> path;

    // Walk backward from exit to entrance
    while (!(r == ent_r && c == ent_c)) {
        path.push_back({r, c});
        int pr = parent_r[r][c];
        int pc = parent_c[r][c];
        r = pr;
        c = pc;
    }
    path.push_back({ent_r, ent_c});

    cout << "\nPath from entrance to exit:\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << "(" << path[i].first << ", " << path[i].second << ")\n";
    }
}

// ----------------------------------------------------------
// STUDENTS IMPLEMENT DFS HERE
// Add arguments, return type, and logic
// ----------------------------------------------------------

bool dfs(int entRow, int entCol, vector<vector<int>>& maze, vector<vector<bool>>& visited,
    vector<vector<int>>& parentRow, vector<vector<int>>& parentCol, int exitRow, int exitCol) {
//     // Your code here

    // debug statement:
    //out of bounds check
    if (entRow > maze.size() || entCol > maze[0].size() || entRow < 0 || entCol < 0) {
        return false;
    }

    // check if current node is a wall or has been visited
    if (maze[entRow][entCol] == 1 || visited[entRow][entCol] == true) {
        return false;
    }

    // mark current node as visited
    visited[entRow][entCol] = true;

    // check if current node is the exit node
    if (entRow == exitRow && entCol == exitCol) {
        return true;
    }

    // TO DO: implement directional arrays to check neighbors
    // use for loop ?
    // implement recursion

    for (int i = 0; i < 4; i++) {

        // neighbor rows and cols
        int nr = entRow + dr[i];
        int nc = entCol + dc[i];

        // checks if dfs of the neighbor is true
        if (dfs(nr, nc, maze, visited, parentRow, parentCol, exitRow, exitCol)) {
            parentRow[nr][nc] = entRow;
            parentCol[nr][nc] = entCol;

            return true;
        }
    }

    return false;

}


// ----------------------------------------------------------
// MAIN PROGRAM (students add DFS calls and logic)
// ----------------------------------------------------------
int main() {
    int N, M;

    cout << "Enter maze dimensions N M: ";
    cin >> N >> M;

    vector<vector<int>> maze(N, vector<int>(M));
    generateMaze(maze, N, M);

    //debug
    cout<< "maze generated successfully";

    // Pick entrance and exit
    pair<int,int> entrance = chooseBoundaryCell(maze);
    pair<int,int> exitCell = chooseBoundaryCell(maze);

    while (exitCell == entrance) {
        exitCell = chooseBoundaryCell(maze);
    }

    int ent_r = entrance.first;
    int ent_c = entrance.second;
    int exit_r = exitCell.first;
    int exit_c = exitCell.second;

    // Display the maze
    printMaze(maze, ent_r, ent_c, exit_r, exit_c);

    // Students must use these
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> parent_r(N, vector<int>(M, -1));
    vector<vector<int>> parent_c(N, vector<int>(M, -1));

    // ------------------------------------------------------
    // STUDENT WORK:
    // Call your DFS, track visited, and fill parent_r and parent_c
    // ------------------------------------------------------
    // debug:
    // cout << "calling dfs";
    bool found = dfs(ent_r, ent_c, maze, visited, parent_r, parent_c, exit_r, exit_c);
    // debug:
    //cout << "dfs called.";
    // ------------------------------------------------------
    // STUDENT WORK:
    // If found, print the path
    // ------------------------------------------------------
    if (found == true) {
         printPath(exitCell, parent_r, parent_c, ent_r, ent_c);
    } else {
         cout<< "\nNo path exists.\n";
    }

    return 0;
}