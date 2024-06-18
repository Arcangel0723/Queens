# What Is Queens?
Queens is a card game that me and my Dad's family used to play a lot. One day I decided to try making it in C.
## The Rules of Queens
The aim of the game is to make sets of three or more cards and get all of your cards out onto the board. Each card is worth points, and any card left in your hand counts against your score for each round.

The game begins by the first player picking up a stack of cards from a shuffled deck and dealing 13 out to each player. If you picked up the exact right amount of cards you get 100 points. I did not try to implement this aspect in C (at least not yet)

On your turn you can lay down sets of three of any card, but some cards are special. A two is a wild card, you can match it up with a pair to create a set of three, and the joker can be player by itself. However, to access these sepcial abilities you have to already have a "natural" set on the board (a set of three of a kind). You also can not add a two to a pile already on the board (you can add any card to an already laid down set of that card though, for instance if you laid down a set of kings last turn and just drew some kings, then you can add it to that pile).

At the end of your turn you discard a card into the discard pile. The discard pile is special, as if you have a pair that will make a set of three with the card on top (no 2s allowed unless all three are 2s), then you can pick up the discard pile instead of drawing (some variations of the rules you just get the card on top, though I think it is more fun to just pick up the whole thing as it can sometimes leave you behind in points if it is high value and you can not get all the cards out and the next players gets all of their cards out). Again, in order to access this special ability you have to get a "natural" set out first. You also must play the set formed this way (as a way to prove that you actually do have the pair in your hand).

The values of each card is as follows:
| Card            | Value |
| --------------- | ----------- |
| Ace             | 15          |
| 2               | 20          |
| 3 to 9          | 5           |
| 10 & face cards | 10          |
| Queen of spades | 100         |
| Joker           | 50          |

When someone has no cards in their hand the game immediately ends. The players count up the total amount of points on their hand and subtract that from the total points they have down on the table.

Shuffle up and the next player deals. Play continues until a player reaches at least the winning number (usually 1 or 2 thousand). In the case of a tie at the end of the game, the first person (the person to the right of the dealer of the latest round) gets last, the player after them gets second last, etc. The dealer gets first priority since they went last. 

There are lots of minor variations
