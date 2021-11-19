#ifndef GENERIC_H_IS_INCLUDED
#define GENERIC_H_IS_INCLUDED

#include <vector>
#include "fssimplewindow.h"
#include "ysglfontdata.h"

// Includes all the common classes and member functions

// Try not to add any game-specific functions here
// If adding anything then push it to github so that everyone can get the updated code

class Card;
class Deck;

class Card {

private:
	int suit, rank;
	std::vector<double> pos;
	int indexForGraphics;


public:
	
	Card();
	Card(int s, int r);
	void print() const;
	bool isGreater(const Card& c2) const;
	bool equals(const Card& c1) const;

	int getSuit() const; // Helper function
	int getRank() const; // Helper function
	void setSuit(int); // Helper function
	void setRank(int); // Helper function
	std::vector<double> getPos() const; // Helper function
	void setPos(const double, const double); // Helper function
	void setPosX(const double); // Helper function
	void setPosY(const double); // Helper function
	int getGraphicsIndex() const; // Helper function
	void setGraphicsIndex(const int); // Helper function
};

class Deck {
private:

	std::vector<Card> cards;

public:
	Deck(int n);
	Deck();

	void print() const;
	void shuffleDeck();
	Deck subDeck(int, int) const;
	int find(const Card& c) const;
	std::vector<Card>& getCards(); // Helper function. Warning: Be careful when using this. Can change the cards.
	Card getRandomCard(const Deck&, const Deck&) const; // Helper function
	Card getRandomCard()const ; // Helper function. Overloaded function.
	int getDeckSize() const;
	void removecard(int p);
};

#endif
