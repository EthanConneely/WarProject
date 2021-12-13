#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define TotalCards 52
#define PlayersCards 13

int cards[TotalCards];
int suits[TotalCards];

void ShuffleDeck()
{
    // Randomize the order of cards in the deck
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
void PrintSuit(int suit)
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

void Reset()
{
    srand((unsigned)time(0));

    for (int i = 0; i < TotalCards; i++)
    {
        cards[i] = -1;
        //  2 + (i % PlayersCards);
        suits[i] = i / PlayersCards;
    }

    for (int i = 0; i < 1000; i++)
    {
        ShuffleDeck();
    }
}

void PrintCards(int player)
{
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
                    printf(" |K  |");
                }
                else if (cards[i] == 13)
                {
                    printf(" |Q  |");
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
            PrintSuit(suits[i]);
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
                    printf(" |__K|");
                }
                else if (cards[i] == 13)
                {
                    printf(" |__Q|");
                }
                else if (cards[i] == 14)
                {
                    printf("|__A|");
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
        printf("   %c  ", ('a' + i));
    }
    printf("\n");
    printf("\n");

    printf("Player %d card selection (a-m): ", player + 1);
}

int main(void)
{
    Reset();

    PrintCards(0);

    getchar();
    getchar();
}
