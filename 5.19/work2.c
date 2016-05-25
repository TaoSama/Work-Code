#include <stdio.h>
#include <string.h>

typedef struct {
    int x, y;
} point_t;

//a method to construct a point
void make_point(point_t* p, int x, int y) {
    p->x = x;
    p->y = y;
}

typedef struct {
    int row, col; //row, column
    char map[105][105]; //original map
    int dis[105][105]; //distance to starting points
    point_t pre[105][105]; //previous point in shortest path
    int have_solution; //a boolean to save whether there is a solution
    point_t exit; //first and leftmost exit in shortest path
} maze_t;

//check whether (x, y) is in the maze
int is_in_bound(maze_t* maze, point_t* p) {
    return p->x >= 0 && p->x <= maze->row && p->y >= 0 && p->y <= maze->col;
}

//bfs to get all the info we want
void bfs(maze_t* maze) {
    static int dir[][2] = { { -1, 0},  {0, 1}, {1, 0}, {0, -1}}; // 4 directions

    point_t queue[10005]; //a queue to save points
    int head, end; // the queue's pointers
    head = end = 0; //initialize to empty

    int i, j;
    for(i = 0; i < maze->row; ++i)  //marked to unvisited
        for(j = 0; j < maze->col; ++j)
            maze->dis[i][j] = -1;

    //initializing
    for(i = 0; i < maze->col; ++i) {
        if(maze->map[0][i] == '.') {
            point_t start;
            make_point(&start, 0, i);
            queue[end++] = start;
            maze->dis[0][i] = 0; //initialize to 0

            make_point(&start, -1, -1);
            maze->pre[0][i] = start; //no previous point
        }
    }

    point_t exit;
    make_point(&exit, -1, -1);  //initialize to no answer
    while(head != end) {
        point_t u = queue[head++];  //get the point of queue head

        //save the exit in shortest path
        if(u.x == maze->row - 1) { //last row
            if(exit.x == -1) exit = u; //no answer yet
            //shortest one
            else if(maze->dis[u.x][u.y] < maze->dis[exit.x][exit.y]) exit = u;
            //leftmost one
            else if(maze->dis[u.x][u.y] == maze->dis[exit.x][exit.y]
                    && u.y < exit.y) exit = u;
        }

        //4 adjacent cells
        for(i = 0; i < 4; ++i) {
            point_t v = u;
            v.x += dir[i][0], v.y += dir[i][1];
            if(!is_in_bound(maze, &v)) continue; //out of bound
            if(maze->map[v.x][v.y] == '#') continue; //obstacle

            if(maze->dis[v.x][v.y] == -1) { //unvisited
                maze->dis[v.x][v.y] = maze->dis[u.x][u.y] + 1; //update shortest path
                maze->pre[v.x][v.y] = u; //record previous point
                queue[end++] = v; //push to queue
            }
        }
    }

    //save exit to maze
    maze->exit = exit;
    maze->have_solution = maze->exit.x != -1;
}

void read_maze(maze_t* maze) {
    maze->row = 0;
    while(scanf("%s", maze->map[maze->row]) != EOF)
        ++maze->row;
    maze->col = strlen(maze->map[0]);
}

void print_stage_1(maze_t* maze) {
    bfs(maze);

    printf("Stage 1\n=======\n");
    printf("maze has %d rows and %d columns\n", maze->row, maze->col);

    int i, j;
    for(i = 0; i < maze->row; ++i) {
        for(j = 0; j < maze->col; ++j)
            printf("%c%c", maze->map[i][j], maze->map[i][j]);
        printf("\n");
    }
    printf("\n");
}

void print_stage_2(maze_t* maze) {
    printf("Stage 2\n=======\n");
    if(maze->have_solution) printf("maze has a solution\n");
    else printf("maze does not have a solution\n");

    int i, j;
    for(i = 0; i < maze->row; ++i) {
        for(j = 0; j < maze->col; ++j) {
            if(maze->map[i][j] == '#') printf("##"); //obstacles
            else {
                //reachable or not
                printf("%s", maze->dis[i][j] == -1 ? "--" : "++");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_stage_3(maze_t* maze) {
    printf("Stage 3\n=======\n");
    printf("maze has a solution with cost %d\n",
           maze->dis[maze->exit.x][maze->exit.y]);

    int i, j;
    for(i = 0; i < maze->row; ++i) {
        for(j = 0; j < maze->col; ++j) {
            if(maze->map[i][j] == '#') printf("##"); //obstacles
            else {
                int distance = maze->dis[i][j];
                if(distance == -1) printf("--"); //unreachable
                else { //reachable
                    if(distance % 2 == 1) printf("++"); //odd steps
                    else {
                        //even steps
                        distance = distance % 100;
                        int x = distance / 10, y = distance % 10;
                        printf("%d%d", x, y);
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void dfs(maze_t* maze, point_t u) { //color the shortest path
    if(u.x == -1) return;
    maze->map[u.x][u.y] = 'C';
    dfs(maze, maze->pre[u.x][u.y]);
}

void print_stage_4(maze_t* maze) {
    printf("Stage 4\n=======\nmaze solution\n");

    dfs(maze, maze->exit); //use dfs to color the shortest path

    int i, j;
    for(i = 0; i < maze->row; ++i) {
        for(j = 0; j < maze->col; ++j) {
            if(maze->map[i][j] == '#') printf("##"); //obstacles
            else {
                int distance = maze->dis[i][j];
                if(distance == -1) printf("--"); //unreachable
                else { //reachable
                    //not in the shortest path
                    if(maze->map[i][j] != 'C') printf("  ");
                    else {
                        if(distance % 2 == 1) printf(".."); //odd steps
                        else {
                            //even steps
                            distance = distance % 100;
                            int x = distance / 10, y = distance % 10;
                            printf("%d%d", x, y);
                        }
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    maze_t maze;
    read_maze(&maze); //read maze

    print_stage_1(&maze);
    print_stage_2(&maze);
    if(maze.have_solution) {  //if there is a solution
        print_stage_3(&maze);
        print_stage_4(&maze);
    }
    return 0;
}
