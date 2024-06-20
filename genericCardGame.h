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

int shuffleDeck(DeckTP deck);
DeckTP buildDeck(int numberOfDecks);
int printCardList(struct CardList* cardList);
int draw(HandTP hand, DeckTP deck, int numberToDraw);
CardTP findCardAtPosition(struct CardList* CardList, int index);