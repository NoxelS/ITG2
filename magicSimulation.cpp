// Zum selber lernen

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <climits>

using namespace std;

struct card
{
    string color;
    int value;
    bool isJester;
    bool isWizard;
};

struct player
{
    string name;
    card *hand;
    int score;
};

int print_deck(card *deck)
{
    // Loop over every card in the deck
    for (int i = 0; i < 60; i++)
    {
        // Print the card
        cout << setw(5) << deck[i].value << setw(10) << deck[i].color << setw(5) << deck[i].isJester << setw(5) << deck[i].isWizard << endl;
    }
}

card *shuffle_deck(card *deck)
{
    card *tempDeck = new card[60];
    // Loop over every card in the deck
    for (int i = 0; i < 60; i++)
    {
        // Generate a random number between 0 and 59
        int random = rand() % 60;

        // Swap the card with the random card
        card temp = deck[i];
        tempDeck[i] = deck[random];
        tempDeck[random] = temp;
    }
    return tempDeck;
}

int play_game(card *deck, player *players, int round, string trump)
{
    // Loop over every sunround
    for (int i = 0; i < round; i++)
    {
        // TODO
    }
}

const int MAX_PLAYERS = 4;

int main()
{
    // Create Player
    player *players = new player[MAX_PLAYERS];
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        players[i].name = "Player " + to_string(i + 1);
        players[i].score = 0;
    }

    // Create Card Deck
    card *deck = new card[60];

    // Insert 4 wizard cards into the deck
    for (int i = 0; i < 4; i++)
    {
        deck[i].isWizard = true;
        deck[i].isJester = false;
        deck[i].color = "";
        deck[i].value = 14;
    }

    // Insert 4 jester cards into the deck
    for (int i = 4; i < 8; i++)
    {
        deck[i].isWizard = false;
        deck[i].isJester = true;
        deck[i].color = "";
        deck[i].value = 0;
    }

    // Create four colors
    string colors[4] = {"red", "blue", "green", "yellow"};

    // // Insert 52 normal cards into the deck
    int index = 8;
    for (int colorI = 0; colorI < 4; colorI++)
    {
        for (int valueI = 1; valueI <= 13; valueI++)
        {
            deck[index].color = colors[colorI];
            deck[index].value = valueI;
            deck[index].isWizard = false;
            deck[index].isJester = false;
            index++;
        }
    }

    int max_rounds = 60 / MAX_PLAYERS;
    if (max_rounds > 20)
        max_rounds = 20;

    max_rounds = 1;

    // Loop over rounds
    for (int round = 1; round <= max_rounds; round++)
    {
        cout << "Round " << round << endl;
        // Create new shuffled deck
        card *currentDeck = shuffle_deck(deck);

        // Deal cards to players
        for (int playerI = 0; playerI < MAX_PLAYERS; playerI++)
        {
            // Allocate memory for round cards
            players[playerI].hand = new card[round];

            // Draw cards from currentDeck
            for (int j = 0; j < round; j++)
            {
                players[playerI].hand[j] = currentDeck[playerI * round + j];
            }
        }

        // Pick one more card
        card *nextCard = &currentDeck[MAX_PLAYERS * round];
        // Print next card
        cout << "On top of the deck: " << nextCard->value << " " << nextCard->color << " " << nextCard->isJester << " " << nextCard->isWizard << endl;
        string trump = nextCard->color;
        if (trump == "")
        {
            if (nextCard->isJester)
            {
                // There is no trump color
                trump = "";
            }
            else if (nextCard->isWizard)
            {
                // Random trump color
                trump = colors[rand() % 4];
            }
        }
        if (trump != "")
        {
            cout << "Trump color: " << trump << endl;
        }
        else
        {
            cout << "No trump color" << endl;
        }

        // Print cards of players
        for (int playerI = 0; playerI < MAX_PLAYERS; playerI++)
        {
            cout << players[playerI].name << endl;
            for (int j = 0; j < round; j++)
            {
                cout << setw(5) << players[playerI].hand[j].value << setw(10) << players[playerI].hand[j].color << setw(5) << players[playerI].hand[j].isJester << setw(5) << players[playerI].hand[j].isWizard << endl;
            }
        }

        // Delete currentDeck
        delete[] currentDeck;

        // Play the game
        if (round == 1)
        {
            // First round
        }
        else
        {
            // Ordinary round
        }
    }
}