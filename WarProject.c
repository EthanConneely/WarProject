/*
    By Ethan Conneely
    G00393941
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

#define TotalCards 52
#define PlayersCards 13

int currentRound = 1;
int currentPlayer = 0;
int numberPlaying = 2;

int cards[TotalCards];
int suits[TotalCards];
int playersChoice[4];

void clearScreen();
void printSuit(int suit);
void shuffleDeck();
int promptCards(int player);
int promptOptions(char* title, char* options[], int optionsSize);
void nextRound();
void loadGame();
void saveGame();
void printStatus();
void newGame();
void exitGame();

void main(void)
{
    char* options[] = { "New Game", "Load Game" };
    int option = promptOptions("Pick an option.", options, 2);

    // Load a previous Game
    if (option == 1)
    {
        newGame();
    }
    else
    {
        loadGame();
        printStatus();
    }
}

// https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
// Used to clear the screen
void clearScreen()
{
    system("cls");
}

// Prints the character for each card suit
void printSuit(int suit)
{
    switch (suit)
    {
    case 0:
        printf("S");
        break;

    case 1:
        printf("H");
        break;

    case 2:
        printf("D");
        break;

    case 3:
        printf("C");
        break;
    }
}

// Randomize the order of cards in the deck
void shuffleDeck()
{
    srand((unsigned)time(0));

    for (int i = 0; i < TotalCards; i++)
    {
        cards[i] = 2 + (i % PlayersCards);
        suits[i] = i / PlayersCards;
    }

    for (int i = 0; i < 1000; i++)
    {
        int cardA = rand() % TotalCards;
        int cardB = rand() % TotalCards;

        int tempCard = cards[cardA];
        cards[cardA] = cards[cardB];
        cards[cardB] = tempCard;

        int tempSuit = suits[cardA];
        suits[cardA] = suits[cardB];
        suits[cardB] = tempSuit;
    }
}

// Prints out all the cards to the screen and
// let user pick one
int promptCards(int player)
{
    char answer;

    do
    {
        clearScreen();

        for (int i = 0; i < PlayersCards; i++)
        {
            printf("  ___ ");
        }
        printf("\n");

        for (int i = PlayersCards * currentPlayer; i < PlayersCards + (PlayersCards * currentPlayer); i++)
        {
            if (cards[i] != -1)
            {
                if (cards[i] == 10)
                {
                    printf(" |%d |", cards[i]);
                }
                else
                {
                    if (cards[i] == 11)
                    {
                        printf(" |J  |");
                    }
                    else if (cards[i] == 12)
                    {
                        printf(" |Q  |");
                    }
                    else if (cards[i] == 13)
                    {
                        printf(" |K  |");
                    }
                    else if (cards[i] == 14)
                    {
                        printf(" |A  |");
                    }
                    else
                    {
                        printf(" |%d  |", cards[i]);
                    }
                }
            }
            else
            {
                printf(" | * |");
            }
        }
        printf("\n");

        for (int i = 0; i < PlayersCards; i++)
        {
            if (cards[i] != -1)
            {
                printf(" | ");
                printSuit(suits[i]);
                printf(" |");
            }
            else
            {
                printf(" |* *|");
            }
        }
        printf("\n");

        for (int i = 0; i < PlayersCards; i++)
        {
            if (cards[i] != -1)
            {
                if (cards[i] == 10)
                {
                    printf(" |_%d|", cards[i]);
                }
                else
                {
                    if (cards[i] == 11)
                    {
                        printf(" |__J|");
                    }
                    else if (cards[i] == 12)
                    {
                        printf(" |__Q|");
                    }
                    else if (cards[i] == 13)
                    {
                        printf(" |__K|");
                    }
                    else if (cards[i] == 14)
                    {
                        printf(" |__A|");
                    }
                    else
                    {
                        printf(" |__%d|", cards[i]);
                    }
                }
            }
            else
            {
                printf(" |_*_|");
            }
        }
        printf("\n");
        printf("\n");

        for (int i = 0; i < PlayersCards; i++)
        {
            if (cards[i] != -1)
            {
                printf("   %c  ", ('a' + i));
            }
            else
            {
                printf("      ");
            }
        }
        printf("\n");
        printf("\n");

        printf("Player %d card selection (a-m): ", player + 1);

        scanf("%c", &answer);

        answer = answer - 'a';
    } while (!(answer >= 0 && answer < 13));

    return answer + (PlayersCards * currentPlayer);
}

int promptOptions(char* title, char* options[], int optionsSize)
{
    int answer;

    do
    {
        clearScreen();
        printf("%s\n", title);

        for (int i = 0; i < optionsSize; i++)
        {
            printf("%d. %s\n", i + 1, options[i]);
        }
        printf("Choose option: ");

        scanf("%d", &answer);

        // Clear the input buffer of invalid data
        fflush(stdin);

    } while (!(answer >= 1 && answer <= optionsSize));

    return answer;
}

void handleWinner()
{
    clearScreen();

    for (int i = 0; i < numberPlaying; i++)
    {
        int index = playersChoice[i];
        printf("Player %d ", i + 1, cards[index]);
        printSuit(suits[index]);
        printf(" %d", cards[index]);
        printf("\n");
    }

    getchar();
}

void nextRound()
{
    char* options[] = { "Choose Card", "Save and Exit", "Exit without saving", "Ouput Status" };

    char title[60];

    sprintf(title, "Take your turn Player %d", currentPlayer + 1);
    int option = promptOptions(title, options, 4);

    switch (option)
    {
    case 1:
        playersChoice[currentPlayer] = promptCards(currentPlayer);
        break;

    case 2:
        saveGame();
        exitGame();
        break;

    case 3:
        exitGame();
        break;

    case 4:
        printStatus();
        break;
    }
}

void loadGame()
{
    FILE* file = fopen("WarSave1.txt", "r");

    fscanf(file, "%d", &currentRound);  // current Round
    fscanf(file, "%d", &numberPlaying); // number of players
    fscanf(file, "%d", &currentPlayer); // current player

    for (int i = 0; i < 4; i++)
    {
        for (int j = i * PlayersCards; j < PlayersCards + (PlayersCards * i); j++)
        {
            fscanf(file, "%d,", &cards[j]);
        }

        for (int j = i * PlayersCards; j < PlayersCards + (PlayersCards * i); j++)
        {
            fscanf(file, "%d,", &suits[j]);
        }
    }

    fclose(file);
}

void saveGame()
{
    FILE* file = fopen("WarSave1.txt", "w");

    fprintf(file, "%d\n", currentRound);  // current Round
    fprintf(file, "%d\n", numberPlaying); // number of players
    fprintf(file, "%d\n", currentPlayer); // current player

    for (int year = 0; year < 4; year++)
    {
        fprintf(file, "\n", year + 1);

        for (int j = year * PlayersCards; j < PlayersCards + (PlayersCards * year); j++)
        {
            fprintf(file, "%d,", cards[j]);
        }

        fprintf(file, "\n");

        for (int j = year * PlayersCards; j < PlayersCards + (PlayersCards * year); j++)
        {
            fprintf(file, "%d,", suits[j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

void printStatus()
{
    clearScreen();

    printf("Status:\n");

    printf("Press any key to close menu...");
    getchar();
}

void newGame()
{
    char* options[] = { "2 Player game", "3 Player game", "4 Player game" };
    int option = promptOptions("Choose how many players.", options, 3);

    shuffleDeck();
    numberPlaying = option + 1;

    while (1)
    {
        for (int i = 0; i < numberPlaying; i++)
        {
            nextRound();
            currentPlayer++;
        }

        handleWinner();

        getchar();

        currentPlayer = 0;
        currentRound++;
    }
}

void exitGame()
{
    char* options[] = { "New Game", "Load Game", "Quit" };
    int option = promptOptions("", options, 3);

    switch (option)
    {
    case 1:
        newGame();
        break;

    case 2:
        loadGame();
        break;

    case 3:
        exit(0);
        break;
    }
}
