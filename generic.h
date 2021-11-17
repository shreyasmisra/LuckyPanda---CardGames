#ifndef GENERIC_H_IS_INCLUDED
#define GENERIC_H_IS_INCLUDED

#include <vector>
#include "fssimplewindow.h"
#include "ysglfontdata.h"

class Card;
class Deck;

class Card {
public:
	int suit, rank;
	
	Card();
	Card(int s, int r);
	void print() const;
	bool isGreater(const Card& c2) const;
	bool equals(const Card& c1) const;
	int getSuit() const;
	int getRank() const;
	void setSuit(int);
	void setRank(int);
	void PrintCard(double cx1, double cy1);
};

class Deck {
public:
	std::vector<Card> cards;

	Deck(int n);
	Deck();

	void print() const;
	void shuffleDeck();
	Deck subDeck(int, int) const;
	int find(const Card& c) const;
	std::vector<Card>& getCards();
	Card getRandomCard(const Deck&, const Deck&) const;
	int getDeckSize() const;
};

#endif
