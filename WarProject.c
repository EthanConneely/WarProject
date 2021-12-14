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

int currentRound;
int currentPlayer;
int numberOfPlayers;

int cards[TotalCards];
int suits[TotalCards];

// https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
// Used to clear the screen
void clearScreen()
{
    system("cls");
}

// Randomize the order of cards in the deck
void shuffleDeck()
{
    for (int i = 0; i < 200; i++)
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

// Reset the cards and shuffle
void reset()
{
    srand((unsigned)time(0));

    for (int i = 0; i < TotalCards; i++)
    {
        cards[i] = 2 + (i % PlayersCards);
        suits[i] = i / PlayersCards;
    }

    for (int i = 0; i < 1000; i++)
    {
        shuffleDeck();
    }
}

// Prints out all the cards to the screen
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

        for (int i = 0; i < PlayersCards; i++)
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

    return answer;
}

int promptOptions(char *title, char *options[], int optionsSize)
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

void startUp()
{
    char *options[] = {"Choose Card", "Save and Exit", "Exit without saving", "Ouput Status"};
    int option = promptOptions("test", options, 4);

    printf("%d", option);

    getchar();

    clearScreen();
}

void main(void)
{
    reset();

    char *options[] = {"New Game", "Load Game"};
    int option = promptOptions("Pick an option.", options, 2);

    // Load a previous Game
    if (option == 2)
    {
        exit(0);
        char *options[] = {"New Game", "Load Game"};
        int option = promptOptions("Pick an option.", options, 2);
    }

    startUp();

    promptCards(0);

    getchar();
    getchar();
}
