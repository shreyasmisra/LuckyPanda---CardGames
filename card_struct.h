#include <vector>
#include <iostream>

using namespace std;


// Use these classes as a base for the rest (Inheritance)
class Card;
class Deck;

bool equals(const Card& c1, const Card& c2);
Deck merge(const Deck& d1, const Deck& d2);
Deck mergeSort(const Deck& deck);

class Card {
public:
	int suit, rank;

	Card();
	Card(int s, int r);
	void print() const;
	bool isGreater(const Card& c2) const;
};

class Deck {
public:
	vector<Card> cards;

	Deck(int n);
	Deck();

	void print() const; // can be used for printing user cards for blackjack and poker
	int find(const Card& c) const;
	void shuffleDeck();
	Deck subDeck(int, int) const;
	int countHand() const; // can go in blackjack class
	void printDealerHand(bool) const; // blackjack class
	void addCard(const Deck& sub, const Deck& deck); // Blackjack class
	void removecard(int p);
};