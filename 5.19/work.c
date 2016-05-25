#include <stdio.h>
#include <string.h>

typedef struct {
    char map[105][105]; //original map
    int d[105][105]; //distance to starting points
    int p[105][105]; //previous point in shortest path
    int row, col; //row, column
    int ex, ey; //first and leftmost entrance
} Maze;

//encode (x, y) to number
int getID(Maze* maze, int x, int y) {
    return x * maze->col + y;
}

//decode number to (x, y)
void getCor(Maze* maze, int id, int* x, int* y) {
    *x = id / maze->col;
    *y = id % maze->col;
}

int isInMaze(Maze* maze, int x, int y) {
    return x >= 0 && x <= maze->row && y >= 0 && y <= maze->col;
}

void bfs(Maze* maze) {
    int q[10005], *front, *rear; // a queue and its pointers
    front = rear = q; //initialize to beginning

    for(int i = 0; i < maze->row; ++i)  //marked to unvisited
        for(int j = 0; j < maze->col; ++j)
            maze->d[i][j] = -1;
    int ex, ey; ex = ey = -1;  //initialize to no answer
    for(int i = 0; i < maze->col; ++i) {
        if(maze->map[0][i] == '.') {
            *rear++ = getID(maze, 0, i); //push to queue
            maze->d[0][i] = 0; //initialize to 0
            maze->p[0][i] = -1; //no previous point
        }
    }

    static int dir[][2] = { -1, 0, 0, -1, 1, 0, 0, 1}; //directions
    while(front != rear) {
        int id = *front++, x, y;  //get the element of queue head
        getCor(maze, id, &x, &y);

        //save the answer
        if(x == maze->row - 1) { //last row
            if(ex == -1) ex = x, ey = y;
            //shortest one
            else if(maze->d[x][y] < maze->d[ex][ey]) ex = x, ey = y;
            //leftmost one
            else if(maze->d[x][y] == maze->d[ex][ey] && y < ey) ex = x, ey = y;
        }

        //4 adjacent cells
        for(int i = 0; i < 4; ++i) {
            int nx = x + dir[i][0], ny = y + dir[i][1];
            if(!isInMaze(maze, nx, ny) || maze->map[nx][ny] == '#')
                continue; //out of bound or obstacles
            if(maze->d[nx][ny] == -1) { //unvisited
                maze->d[nx][ny] = maze->d[x][y] + 1; //update shortest path
                maze->p[nx][ny] = getID(maze, x, y); //record previous point
                *rear++ = getID(maze, nx, ny); //push to queue
            }
        }
    }

    //save answer to maze
    maze->ex = ex;
    maze->ey = ey;
}

void readMaze(Maze* maze) {
    for(maze->row = 0; ; ++maze->row) {
        int ret = scanf("%s", maze->map[maze->row]);
        if(ret != 1) break;
    }
    maze->col = strlen(maze->map[0]);
}

void printStage1(Maze* maze) {
    puts("Stage 1\n=======");
    printf("maze has %d rows and %d columns\n", maze->row, maze->col);
    for(int i = 0; i < maze->row; ++i) {
        for(int j = 0; j < maze->col; ++j)
            printf("%c%c", maze->map[i][j], maze->map[i][j]);
        puts("");
    }
    puts("");
}

void printStage2(Maze* maze) {
    puts("Stage 2\n=======");
    if(maze->ex != -1) puts("maze has a solution");
    else puts("maze does not have a solution");
    for(int i = 0; i < maze->row; ++i) {
        for(int j = 0; j < maze->col; ++j) {
            if(maze->map[i][j] == '#') printf("##"); //obstacles
            else {
                int d = maze->d[i][j];
                if(d == -1) printf("--"); //unreachable
                else printf("++");  //reachable
            }
        }
        puts("");
    }
    puts("");
}

void printStage3(Maze* maze) {
    puts("Stage 3\n=======");
    printf("maze has a solution with cost %d\n", maze->d[maze->ex][maze->ey]);
    for(int i = 0; i < maze->row; ++i) {
        for(int j = 0; j < maze->col; ++j) {
            if(maze->map[i][j] == '#') printf("##"); //obstacles
            else {
                int d = maze->d[i][j];
                if(d == -1) printf("--"); //unreachable
                else { //reachable
                    if(d & 1) printf("++"); //odd steps
                    else {
                        //even steps
                        int x = d % 100 / 10, y = d % 10;
                        printf("%d%d", x, y);
                    }
                }
            }
        }
        puts("");
    }
    puts("");
}

void printStage4(Maze* maze) {
    puts("Stage 4\n=======\nmaze solution");
    int x = maze->ex, y = maze->ey; //iterate the shortest path
    while(x != -1) {
        maze->map[x][y] = 'P'; //mark the path
        int id = maze->p[x][y];
        if(id == -1) break;  //already the starting point
        getCor(maze, id, &x, &y);
    }

    for(int i = 0; i < maze->row; ++i) {
        for(int j = 0; j < maze->col; ++j) {
            if(maze->map[i][j] == '#') printf("##"); //obstacles
            else {
                int d = maze->d[i][j];
                if(d == -1) printf("--"); //unreachable
                else { //reachable
                    //not in the shortest path
                    if(maze->map[i][j] != 'P') printf("  ");
                    else {
                        if(d & 1) printf(".."); //odd steps
                        else {
                            //even steps
                            int x = d % 100 / 10, y = d % 10;
                            printf("%d%d", x, y);
                        }
                    }
                }
            }
        }
        puts("");
    }
    puts("");
}

int main() {
    Maze maze;
    readMaze(&maze); //read maze

    bfs(&maze); //use bfs to get answer

    printStage1(&maze);
    printStage2(&maze);
    if(maze.ex != -1) {  //if there is a solution
        printStage3(&maze);
        printStage4(&maze);
    }
    return 0;
}
