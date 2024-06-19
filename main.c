#include "genericCardGame.h"
#include "ansiColourCodes.h"
#include<stdlib.h>
#include<stdio.h>
#define clearScreen() printf("\033c")

typedef struct Set {
    int value;
    CardTP head;
    struct Set* next;
} SetT, *SetTP;

typedef struct Field {
    SetTP head;
} FieldT, *FieldTP;

typedef struct Player {
    int score;
    int playerNumber;
    HandTP hand;
    FieldTP field;
    struct Player* nextPlayer;
} PlayerT, *PlayerTP;

typedef struct GameTable {
    DeckTP deck;
    DiscardPileTP discardPile;
    PlayerTP firstPlayer;
} GameTableT, *GameTableTP;

int getInt(){
    int validInput;
    int userInput;
    int c;
    char inputBuffer[16];
    
    validInput = 0;
    while(!validInput){
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        if(sscanf(inputBuffer, "%d", &userInput) == 1){
            validInput = 1;
        }else{
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\33[1A");
            printf("\33[2K");
        }
    }
    return userInput;
}

void initGame(GameTableTP GameTable){
    int i;
    int numberOfPlayers;
    PlayerTP temp;
    PlayerTP temp2;

    printf("Welcome to Queens\nTo begin, please enter the number of players (greater than one): \n");
    
    numberOfPlayers = 0;
    while(numberOfPlayers <= 1){
        numberOfPlayers = getInt();
        if(numberOfPlayers <= 1){
            printf("\33[1A");
            printf("\33[2K");
        }
    }

    GameTable->deck = buildDeck(numberOfPlayers);
    temp = (PlayerTP)malloc(sizeof(PlayerT));
    temp->hand = (HandTP)malloc(sizeof(HandT));
    draw(temp->hand, GameTable->deck, 13);
    temp->playerNumber = 1;
    GameTable->firstPlayer = temp;

    for(i = 0; i < numberOfPlayers - 1; i++){
        temp2 = (PlayerTP)malloc(sizeof(PlayerT));
        temp->nextPlayer = temp2;
        temp2->hand = (HandTP)malloc(sizeof(HandT));
        draw(temp2->hand, GameTable->deck, 13);
        temp2->playerNumber = i + 2;
        temp = temp->nextPlayer;
    }
    temp->nextPlayer = GameTable->firstPlayer;
    clearScreen();
}
/*returns a */
int playerTurn(PlayerTP player){
    int hasCards;
    int playerInput;

    playerInput = 0;
    printf("Welcome Player %d\nType 1 to begin your turn\n", player->playerNumber);

    while(playerInput != 1){
        playerInput = getInt();
        printf("\33[1A");
        printf("\33[2K");
    }

    clearScreen();
    return hasCards;
}

int gameLoop(GameTableT GameTable){
    int roundInProgress;
    PlayerTP player;

    player = GameTable.firstPlayer;
    while(roundInProgress){
        roundInProgress = playerTurn(player);
        player = player->nextPlayer;
    }
    return 0;
}

/*
//literally just add the whole discard pile to the player's hand.
//then take the head node and form a set with two matching cards
//in the player's hand
int pickUpStack(PlayerTP player, DiscardPileTP discardPile) {

}*/

int main(void) {
    GameTableT GameTable;

    initGame(&GameTable);
    gameLoop(GameTable);

    return 0;
}