#include "genericCardGame.h"
#include "ansiColourCodes.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


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
}

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

int printCardList(struct CardList* cardList) {
    CardTP current;
    int i;
    for(current = cardList->head, i = 0; current != NULL; current = current->next, i++){
        printf(ANSI_COLOR_WHITE);
        printf("%d: ", i + 1);
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

CardTP findCardAtPosition(struct CardList* CardList, int index){
    int i;
    CardTP current;

    for(i = 0, current = CardList->head; i < index && current != NULL; i++, current = current->next){

    }

    return current;
}

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