# Legend of the Five Rings CardGame
Altered version of the game Legend of the five rings implementation for OOP course at UoA
## Contributors
[Apostolos Karvelas](https://github.com/TollisK)

[Ioannis Papadimitriou](https://github.com/Giannis-Papadimitriou)

## Compilation command:

    g++ main.cpp TypeConverter.cpp Holding.cpp DeckBuilder.cpp -o myprog

## Execution command:

    ./myprog

## This game is between 2 players with 5 phases each round.

## Main.cpp
The main program calls five different functions, which correspond to the five
different phases of the game.

**Phase1**: Phase1 is the starting phase. The player draws a card, all provinces and their attached
cards are revealed, all Holdings and Personalities on board become untapped and the Player’s
hand is printed.

**Phase2**: Phase2 is the Equipment Phase. During the second Phase the user/player will get to
choose whether they want to tap their holdings, buy cards from hand and attach them to their
Personalities, as many times as they want. They will be prompted to answer Yes/No questions
or type numbers in, to choose between available Card choices. Phase2 ends if the Player
doesn’t have an army to strengthen, or if the Player chooses to end it.

Phase2 temporarily stores the player’s money which start from 0 and increase as the player taps
their holdings. When the player chooses to buy a card it is checked if they have enough, then
after the player chooses the personality the greencard’s minimum honor is compared with the
Personality’s honor. If either of the checks fail nothing happens and the player is given the
chance to redo Phase2. If both checks pass Typeconverter is used to determine the card’s type,
after which the player’s money is reduced by the card’s cost and the greencard is attached to the
chosen personality through the use of the “ _addcard_ ” function. Once that’s done the player gets
to redo the Phase.

**Phase3**: Phase3 is the Battle Phase. Phase3A has two “subphases”, Phase3B and Phase3C.
When Phase3A is called the Player’s honors are compared. The player with the most honor gets
to attack first. Afterwards, Phase3B is called with a reference to the attacking player as its first
argument and a reference to the defending player as its second. Firstly, the attacking player is
shown their army and should they choose a province to attack, Phase3C will be called during
which the player will be prompted to choose which units they want to act with. When a
personality is chosen to participate in a battle their “Ready” state will be set to 1. When the
attacking player is done assembling their forces, Phase3C will be called for the defending
player who will get to do the same. Afterwards all personalities(and their attached
items/follower), whose “Ready” state is equal to 1 battle. The sum of their attack is compared
to the sum of the defender’s defence + the province’s defence. Afterwards, the known scenarios
play out and depending on the situation personalities, items, followers and the attacked
province may end up “dying”, thus being rendered useless for the rest of the game. If the
province is destroyed its “isDead” state is set to 1, which renders it unable to generate any more
blackcards for the rest of the game. If a Personality dies they are removed from the


“boardPersonalities” vector along with all their items and followers. After combat all the losing
Personalities lose 1 honor and if that leads to them having none, they commit seppuku
changing their “isDead” state to 1 and deleting all their followers and items. Afterwards, all
items in combat lose 1 durability and if it reaches 0 they are removed from the personality’s
item vector, while also reducing said personality’s attack and defence.

**Phase4**: Phase4 is the Economy Phase. The Player gets to tap holdings and buy
Personalities/Holdings if they have enough money. When a player buys a Blackcard from a
province that card is replaced by another that cannot be seen or interacted with until the next
Phase1 during which all blackcards will be revealed. Each Player gets to repeat the Economy
Phase as many times as they’d like.

The money system in Phase4 works the same as Phase2. When a player chooses a Blackcard to
buy it is checked whether they have enough money or not and if they do the Typeconverter is
called to determine the BlackCard’s type. Depending on it either “addHold” or
“addPersonality” are called which add the holding/personality to the player’s corresponding
board. Afterward, the province’s card is replaced with a new one through the function
BlackCard::Draw and that card is hidden.

**Phase5**: Phase5 is the Final Phase. During this phase the players are shown their hands and if
they exceed the predetermined maximum hand size they are forced to discard cards until they
don’t. Afterwards, both player’s Hands, Provinces, Armies and Holdings are printed.



### Card.h: 
includes the following classes: Card is a class used to describe the idea of a card. It has a name, an isTapped integer variable- used to represent Tapped and Untapped states- and a cost. These variables are initialized during construction. Card and all its derived classes have a “Reveal” function that prints the card’s contents. Card has two derived classes: BlackCard and GreenCard, which are used to represent the game’s blackcards and greencards. A GreenCard has an AttackBonus, a DefenceBonus, MinimumHonor, Cardtxt ( Card text), an EffectBonus and an EffectCost, which are initialized during construction. Apart from the accessors and mutators, there’s the “ bonusactivate” function, which when called increases the card’s cost, AttackBonus and DefenceBonus according to the EffectBonus and EffectCost, along with the “ hebrokenvm ” function that reverses the effect if it turns out that the player didn’t have enough money to afford the extra cost. There’s also a “ Draw” function which effectively removes the top card of the given Fate deck and returns a pointer to it.

A _BlackCard_ has an isRevealed value, accessors, mutators and a “ _Draw_ ” function which
functions as the GreenCard’s Draw function but for a given dynasty deck instead.

_GreenCard_ has two derived Classes: _Follower_ and _Item._

### Follower.h:
A _Follower_ has no variables. It only accessors, mutators, a constructor that is
simply used to pass the values from its derived classes’ constructors to the _GreenCard_
constructor and a “ _getType”_ function used for the Typeconverter file.

A follower’s derived classes are _Footsoldier, Archer, Sieger_ etc. which when created pass the
appropriate values to the _GreenCard_ constructor. The same concept applies for _Items,
Personalities_ and _Holdings._

### Item.h: An _Item_ is a _GreenCard_ that has a Durability, an appropriate getType function and a
“ _ChangeDurability_ ” function that reduces the item’s durability by 1 after combat.

### Psonality.h:
A _Personality_ is a _BlackCard_ that has Attack, Defence, Honor, an isDead state, a
Ready state that’s used during the combat phase, a pointer to a vector that contains pointers to
the _Followers_ attached to that personality. The same method is used for storing the
personality’s items. Apart from accessors and mutators, _Personalities_ have the “ _addcard”_
function that adds the _Item/Follower_ argument to the appropriate vector while also increasing
the _Personality’s_ Attack and Defence by the _Item/Follower’s_ AttackBonus and DefenceBonus.

### Holding.h:
A _Holding_ is a _BlackCard_ that has a HarvestValue. Apart from accessors, mutators,
“ _getType”_ a _Holding_ also has a _Mine_ , _GoldMine_ and a _CrystalMine_ typeconverter. All holdings
with the exception of _Mines_ , _GoldMines_ and _CrystalMines_ are constructed with the method
explained at the end of the **Follower.h** section. The three mines also have pointers to
subholding and upperholding mines. Two mines are connected through the “ _connect”_ function
that uses the aforementioned typeconverters to create a chain between the mines if possible.
The mines also have the “ _ismine”_ function that’s used in the mine typeconverters.

A _Stronghold_ is a _Holding_ that has an initial defence and starting honor.

### Player.h:
This file contains the _Province_ and _Player_ classes. A _Province_ has a pointer to a
_BlackCard_ , defence, an isRevealed state and an isDead state and it’s used to represent the
game’s provinces. The _Player_ class represents a player.

A Player has a name, two decks(a pointer to a list of pointers to GreenCards and a pointer to a
list of pointers to BlackCards), a pointer to a _StrongHold ,_ a pointer to a dynamically allocated
array of provinces, a hand -which is implemented through a pointer to a vector of pointers to
GreenCards -, a variable that indicates the number of cards in hand and two boards for
personalities and holdings respectively ( which are implemented through vectors). _Player_ has
accessors, mutators, along with an “ _addPersona_ lit _y_ ” function that is given a pointer to a
_Personality_ as an argument and places it into the board of _Personalities_. “ _addHold_ ” does the
same except, that it also check if the given holding is a mine that can connect to another mine.


### Main:

When the main function is called two dynasty and two fate decks are created and shuffled.
Then, the two players are created and given a fate and dynasty deck each. Afterwards a while
loop starts that checks if either player is dead. Phases 1 through 5 are repeated until a player
loses.


