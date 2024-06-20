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
    int numSets;
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
    temp->field = (FieldTP)malloc(sizeof(FieldT));
    draw(temp->hand, GameTable->deck, 13);
    temp->playerNumber = 1;
    GameTable->firstPlayer = temp;

    for(i = 0; i < numberOfPlayers - 1; i++){
        temp2 = (PlayerTP)malloc(sizeof(PlayerT));
        temp->nextPlayer = temp2;
        temp2->hand = (HandTP)malloc(sizeof(HandT));
        temp2->field = (FieldTP)malloc(sizeof(FieldT));
        draw(temp2->hand, GameTable->deck, 13);
        temp2->playerNumber = i + 2;
        temp = temp->nextPlayer;
    }
    temp->nextPlayer = GameTable->firstPlayer;
    clearScreen();
}

void resetPlayerBoard(PlayerTP player){
    int i;
    clearScreen();
    printf("Enter '0' to end your turn\n");
    printCardList(player->hand);
    
    for(i = 0; i < player->field->numSets; i++){
        printf("Set of %d\n", player->field->head->value);
    }
}

/*returns a */
int playerTurn(PlayerTP player){
    int hasCards;
    int playerInput;
    CardTP temp;
    CardTP cardBuffer[3];
    SetTP set;
    int i;

    playerInput = 0;
    printf("Welcome Player %d\nType 1 to begin your turn\n", player->playerNumber);

    while(playerInput != 1){
        playerInput = getInt();
        printf("\33[1A");
        printf("\33[2K");
    }
    clearScreen();

    printf("Enter '0' to end your turn\n");
    printCardList(player->hand);

    while(playerInput != 0){
        /*if player has no natural set yet*/
        if(player->field->head == NULL){
            for(i = 0; i < 3; i++){
                do
                {
                    printf("Type a card number to add to your set: ");
                    playerInput = getInt();
                    if(playerInput == 0){
                        break;
                    }
                } while ((temp = findCardAtPosition(player->hand, playerInput - 1)) == NULL);
                cardBuffer[i] = temp;
                printf("Inputed Card: %d\n", temp->value);
                if(playerInput == 0){
                    break;
                }
            }
            if(playerInput != 0){
                if(cardBuffer[0]->value == cardBuffer[1]->value && cardBuffer[1]->value == cardBuffer[2]->value){
                    resetPlayerBoard(player);
                    printf("Valid Set\n");
                }else{
                    resetPlayerBoard(player);
                    printf("Invalid set, please choose different cards\n");
                }
            }
            
        }else{

        }
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