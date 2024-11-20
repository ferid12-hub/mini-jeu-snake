#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> // Pour la fonction Sleep

#define WIDTH 20 // Largeur de la grille
#define HEIGHT 20 // Hauteur de la grille

int gameover;
int score;
int tailX[100], tailY[100];
int nTail;
int x, y, fruitX, fruitY;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;

void Setup()
{
    gameover = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    nTail = 0;
}

void Draw()
{
    system("cls"); // Clear the screen
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                printf("#");
            if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else
            {
                int print = 0;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("o");
                        print = 1;
                    }
                }
                if (print == 0)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    printf("Score:%d", score);
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'q':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'z':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= WIDTH) x = 0; else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0; else if (y < 0) y = HEIGHT - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

int main()
{
    int choice;
    char name[100];
    printf("Bienvenue dans le jeu du Snake!\n");

    do {
        printf("\nMenu:\n");
        printf("1. Commencer à jouer\n");
        printf("2. Aide\n");
        printf("3. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Veuillez entrer votre nom: ");
                scanf("%s", name);
                Setup();
                while (!gameover)
                {
                    Draw();
                    Input();
                    Logic();
                    Sleep(100); // sleep(10);
                }
                printf("\nVotre score est: %d\n", score);
                break;
            case 2:
                printf("\nInstructions:\n");
                printf("Utilisez les touches 'z', 'q', 's', 'd' pour déplacer le serpent.\n");
                printf("Appuyez sur 'x' pour quitter le jeu.\n");
                break;
            case 3:
                printf("\nAu revoir, %s!\n", name);
                break;
            default:
                printf("\nChoix invalide. Veuillez choisir à nouveau.\n");
        }
    } while (choice != 3);

    return 0;
}
