#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ANSI_BACKGROUND_WHITE     "\033[107m"
#define ANSI_COLOR_BLACK     "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


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
    printf("The number of cards is: %d\n", numberOfCards);
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

    deck = malloc(sizeof(DeckT));
    deck->head = malloc(sizeof(CardT));
    temp = malloc(sizeof(CardT));
    deck->head = temp;

    for(i = 0; i < 13 * numberOfDecks; i++){
        for(j = 0; j < 4; j++){
            temp2 = malloc(sizeof(CardT));
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
    int i;
    printf("Start of print");
    for(current = cardList->head, i = 0; current != NULL; current = current->next){
        printf(ANSI_BACKGROUND_WHITE ANSI_COLOR_BLACK);
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
                printf(ANSI_COLOR_BLACK "♠\n" ANSI_COLOR_RESET);
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



/*/Take a pointer to a player, the deck, and the number of cards to draw
//If the player has no cards, make the deck's head the player's hand's
//head, then step in the number of cards to draw, make that pointer null
//Then set the next card as the deck's new head. If the player has cards
//in their hand (the head pointer is not null), then the final card drawn
//will point to the head. Actually this could work in both since the head
//would be null if there are no cards. If there are not enough cards in the
//deck then return an error value.*/
int draw(HandTP hand, DeckTP deck, int numberToDraw) {
    CardTP temp;
    CardT test = {NULL, 2, 0};
    int i;

    for(i = 0, temp = deck->head; i < numberToDraw; i++, temp = temp->next){

    }
    /*if the player has no cards in hand*/
    if(hand->head == NULL)
    {
        hand->head = deck->head;
        deck->head = temp;
        for(i = 0, temp = hand->head; i < numberToDraw - 1; i++, temp = temp->next){

        }
        printf("Here is the temp's Number: %d and Suit: %d and the next nodes value: %d", temp->value, temp->suit, temp->next->value );
        temp->next = NULL;
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
    int numberOfPlayers;
    GameTableT GameTable;
    PlayerT player1;

    player1.hand = (HandTP)malloc(sizeof(HandT));

    /*/ask user for number of players*/

    numberOfPlayers = 1;
    GameTable.deck = buildDeck(numberOfPlayers);
    printCardList(GameTable.deck);

    draw(player1.hand, GameTable.deck, 5);

    printCardList(GameTable.deck);
    printCardList(player1.hand);

    return 0;
}