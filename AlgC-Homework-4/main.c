//
//  main.c
//  AlgC-Homework-4
//
//  Created by admin on 12.07.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define M 6
#define N 6

void solution1();
void solution2();
void solution3();
//void solution4();
//void solution5();
void menu();

int main(int argc, const char * argv[]) {
    menu();
    return 0;
}

void menu() {
    srand( time(NULL) );
    int solutionNumber;
    printf("Choose solution (1..3):\n");
    scanf("%d", &solutionNumber);
    switch (solutionNumber) {
        case 1:
            solution1();
            break;
        case 2:
            solution2();
            break;
        case 3:
            solution3();
            break;
//        case 4:
//            solution4();
//            break;
//        case 5:
//            solution5();
//            break;
        default:
            printf("Wrong solution number!");
            break;
    }
}

void printMatrix(int n, int m, int a[N][M]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d", a[i][j]);
        }
        printf("\n");
    }
}

void solution1() {
    int map[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            map[i][j] = 1;
        }
    }
    int numberOfBarriers;
    printf("Input number of barriers: \n");
    scanf("%d", &numberOfBarriers);
    
    int index = 0;
    while (index < numberOfBarriers) {
        int randN = rand() % N;
        int randM = rand() % M;
        if (map[randN][randM] != 0 && randN + randM != N + M - 2 && randN + randM != 0) {
            map[randN][randM] = 0;
            index++;
        }
    }
    
    printf("Map matrix: \n");
    printMatrix(N, M, map);
    
    int a[N][M];
    a[0][0] = 1;
    for (int j = 1; j < M; j++) {
        a[0][j] = a[0][j-1] * map[0][j];
    }
    for (int i = 1; i < N; i++) {
        a[i][0] = a[i-1][0] * map[i][0];
        for (int j = 1; j < M; j++) {
            a[i][j] = (a[i-1][j] + a[i][j-1]) * map[i][j];
        }
    }
    
    printf("Result matrix: \n");
    printMatrix(N, M, a);

    printf("Number of routes: \n");
    printf("%d\n", a[N-1][M-1]);
}

int i, j, m, n, c[20][20];
char x[20], y[20], b[20][20];

void print(int i, int j)
{
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == 'c')
    {
        print(i - 1, j - 1);
        printf("%c", x[i - 1]);
    }
    else if (b[i][j] == 'u')
        print(i - 1, j);
    else
        print(i, j - 1);
}

void printLCSMatrix(int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d", c[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d", b[i][j]);
        }
        printf("\n");
    }
}

void lcs()
{
    m = strlen(x);
    n = strlen(y);
    for (i = 0; i <= m; i++)
        c[i][0] = 0;
    for (i = 0; i <= n; i++)
        c[0][i] = 0;

    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 'c';
            }
            else if (c[i - 1][j] >= c[i][j - 1])
            {
                c[i][j] = c[i - 1][j];
                b[i][j] = 'u';
            }
            else
            {
                c[i][j] = c[i][j - 1];
                b[i][j] = 'l';
            }
        }
}

void solution2() {
    printf("Enter 1st sequence: \n");
    scanf("%s", x);
    printf("Enter 2nd sequence: \n");
    scanf("%s", y);
    
    printf("LCS: \n");
    lcs();
    print(m, n);
    printf("\n");
}


#define X 7
#define Y 7

void printBoard(int a[X][Y]) {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            printf("%4d", a[i][j]);
        }
        printf("\n");
    }
}

int count = 1;
long unsigned counter = 0;
int board[X][Y];

int checkHorse(int positionX, int positionY) {
    if (positionX < 0 || positionY < 0 || positionX > X-1 || positionY > Y-1) {
        return 0;
    }
    if (board[positionX][positionY] != 0) {
        return 0;
    } else
    return 1;
}

int searchSolution(int currentX, int currentY) {
    counter++;
    printf("%d %lu\n", count, counter);
    //printBoard(board);
    if (checkHorse(currentX-1, currentY-2) == 1) {
        board[currentX-1][currentY-2] = 1;
        count++;
        if (count == X*Y) {
            return 1;
        }
        if (searchSolution(currentX-1, currentY-2) == 1) {
            return 1;
        }
    }
    if (checkHorse(currentX-2, currentY-1) == 1) {
        board[currentX-2][currentY-1] = 1;
        count++;
        if (count == X*Y) {
            return 1;
        }
        if (searchSolution(currentX-2, currentY-1) == 1) {
            return 1;
        }
    }
    if (checkHorse(currentX-2, currentY+1) == 1) {
        board[currentX-2][currentY+1] = 1;
        count++;
        if (count == X*Y) {
            return 1;
        }
        if (searchSolution(currentX-2, currentY+1) == 1) {
            return 1;
        }
    }
    if (checkHorse(currentX-1, currentY+2) == 1) {
        board[currentX-1][currentY+2] = 1;
        count++;
        if (count == X*Y) {
            return 1;
        }
        if (searchSolution(currentX-1, currentY+2) == 1) {
            return 1;
        }
    }
    if (checkHorse(currentX+1, currentY+2) == 1) {
        board[currentX+1][currentY+2] = 1;
        count++;
        if (count == X*Y) {
            return 1;
        }
        if (searchSolution(currentX+1, currentY+2) == 1) {
            return 1;
        }
    }
    if (checkHorse(currentX+2, currentY+1) == 1) {
        board[currentX+2][currentY+1] = 1;
        count++;
        if (count == X*Y) {
            return 1;
        }
        if (searchSolution(currentX+2, currentY+1) == 1) {
            return 1;
        }
    }
    if (checkHorse(currentX+2, currentY-1) == 1) {
        board[currentX+2][currentY-1] = 1;
        count++;
        if (count == X*Y) {
            return 1;
        }
        if (searchSolution(currentX+2, currentY-1) == 1) {
            return 1;
        }
    }
    if (checkHorse(currentX+1, currentY-2) == 1) {
        board[currentX+1][currentY-2] = 1;
        count++;
        if (count == X*Y) {
            return 1;
        }
        if (searchSolution(currentX+1, currentY-2) == 1) {
            return 1;
        }
    }
    count--;
    board[currentX][currentY] = 0;
    return 0;
}

void solution3() {
    
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            board[i][j] = 0;
        }
    }
    board[0][0] = 1;
    
    printf("Start matrix: \n");
    printBoard(board);
    
    if (searchSolution(0, 0) == 1) {
        printf("WIN\n");
        printBoard(board);
        printf("%d\n", count);
    }
}




