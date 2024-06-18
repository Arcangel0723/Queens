#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ANSI_BACKGROUND_WHITE     "\033[107m"
#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define clearScreen() printf("\033c")

enum Suit {
    SPADES,
    HEARTS,
    DIAMONDS,
    CLUBS
};

typedef struct Card {
    struct Card* next;
    int value;
    enum Suit suit;
} CardT, *CardTP;

typedef struct CardList {
    CardTP head;
} HandT, *HandTP, DeckT, *DeckTP, DiscardPileT, *DiscardPileTP;

typedef struct Set {
    int type;
    int amount;
    int twos;
    int spades;
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

int shuffleDeck(DeckTP deck){
    CardTP current;
    int numberOfCards;
    int i;
    int j;

    CardTP* cardArray;
    /*find length of linked list*/
    for(current = deck->head, numberOfCards = 0; current->next != NULL; current = current->next, numberOfCards++)
        ;
    cardArray = (CardTP*)malloc(sizeof(CardTP) * numberOfCards);

    for(current = deck->head, i = 0; current->next != NULL; current = current->next, i++){
        cardArray[i] = current;
    }
    /*Fisher-Yates shuffle*/
    srand(time(NULL));
    for(i = 0; i < numberOfCards; i++){
        j = rand()%(numberOfCards - i) + i;
        current = cardArray[i];
        cardArray[i] = cardArray[j];
        cardArray[j] = current;
    }

    for(current = deck->head, i = 0; current->next != NULL; current = current->next, i++){
        current->value = cardArray[i]->value;
        current->suit = cardArray[i]->suit;
    }

    return 0;
} /*
//Create a DeckTP, populate it with cards, return it*/
DeckTP buildDeck(int numberOfDecks) {
    DeckTP deck;
    CardTP temp;
    CardTP temp2;
    int i;
    int j;

    deck = (DeckTP)malloc(sizeof(DeckT));
    temp = (CardTP)malloc(sizeof(CardT));
    deck->head = temp;

    for(i = 0; i < 13 * numberOfDecks; i++){
        for(j = 0; j < 4; j++){
            temp2 = (CardTP)malloc(sizeof(CardT));
            temp->next = temp2;
            temp->value = i%13 + 1;
            temp->suit = j;
            temp = temp->next;
        }
    }
    shuffleDeck(deck);
    return deck;
}

/*Goes through the passed generic CardList linked list and prints each card
returns success/fail*/
int printCardList(struct CardList* cardList) {
    CardTP current;
    printf("Start of print\n");
    for(current = cardList->head; current != NULL; current = current->next){
        printf(ANSI_COLOR_WHITE);
        if(current-> value < 11){
            printf("%d of ", current->value);
        }else{
            switch(current->value){
                case 11:
                    printf("Jack of ");
                    break;
                case 12:
                    printf("Queen of ");
                    break;
                case 13:
                    printf("King of ");
                    break;
                case 14:
                    printf("Joker\n");
                    break;
            }
        }

        switch(current->suit){
            case SPADES:
                printf(ANSI_COLOR_WHITE "♠\n" ANSI_COLOR_RESET);
                break;
            case HEARTS:
                printf(ANSI_COLOR_RED "♥\n" ANSI_COLOR_RESET);
                break;
            case DIAMONDS:
                printf(ANSI_COLOR_BLUE "♦\n" ANSI_COLOR_RESET);
                break;
            case CLUBS:
                printf(ANSI_COLOR_GREEN "♣\n" ANSI_COLOR_RESET);
                break;
        }
    }

    return 1;
}

/*Splits the deck along where we want to draw and assigns the first bit to the hand
and the second bit to the deck*/
int draw(HandTP hand, DeckTP deck, int numberToDraw) {
    CardTP temp;
    CardTP temp2;
    int i;
    int j;
    if(numberToDraw <= 0){
        printf("Attempting to draw less than one card");
        return 0;
    }
    for(i = 0, temp = deck->head; i < numberToDraw; i++, temp = temp->next){
        if(temp->next == NULL){
            printf("Attempted to draw too many cards");
            return 0;
        }
    }
    /*if the player has no cards in hand*/
    if(hand->head == NULL)
    {
        hand->head = deck->head;
        deck->head = temp;
        for(i = 0, temp = hand->head; i < numberToDraw - 1; i++, temp = temp->next){

        }
        temp->next = NULL;
    }else{
        for(j = 0, temp2 = hand->head; temp2->next !=NULL; j++, temp2 = temp2->next){

        }
        temp2->next = deck->head;
        deck->head = temp;
        for(i = 0, temp = hand->head; i < numberToDraw + j; i++, temp = temp->next){

        }
        temp->next = NULL;
    }
    return 1;
}

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