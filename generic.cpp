#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "generic.h"


// Member functions for Card class 

Card::Card() {
	suit = 0;
	rank = 0;
}

Card::Card(int s, int r) {
	suit = s; rank = r;
}

void Card::print() const {
	std::vector<std::string> suits(4);
	std::vector<std::string> ranks(14);

	suits[0] = "Clubs";
	suits[1] = "Diamonds";
	suits[2] = "Hearts";
	suits[3] = "Spades";

	ranks[1] = "Ace";
	ranks[2] = "2";
	ranks[3] = "3";
	ranks[4] = "4";
	ranks[5] = "5";
	ranks[6] = "6";
	ranks[7] = "7";
	ranks[8] = "8";
	ranks[9] = "9";
	ranks[10] = "10";
	ranks[11] = "Jack";
	ranks[12] = "Queen";
	ranks[13] = "King";

	std::cout << ranks[rank] << "\t of \t" << suits[suit] << std::endl;
}

bool Card::isGreater(const Card& c2) const
{
	if (suit > c2.suit) return true;
	if (suit < c2.suit) return false;

	if (rank == 1 && c2.rank != 1) return true;
	if (rank != 1 && c2.rank == 1) return false;

	if (rank > c2.rank) return true;
	if (rank < c2.rank) return false;
	return false;
}

bool Card::equals(const Card& c1) const 
{
	return (c1.rank == rank && c1.suit == suit);
}

int Card::getSuit() const
{
	return suit;
}

int Card::getRank() const
{
	return rank;
}

void Card::setSuit(int s)
{
	suit = s;
}

void Card::setRank(int r)
{
	rank = r;
}

// Member functions for Deck class.

Deck::Deck(int n)
{
	std::vector<Card> temp(n);
	cards = temp;
}

Deck::Deck() {
	std::vector <Card> tmp(52);
	cards = tmp;

	int i = 0;
	for (int suit = 0; suit < 4; suit++) {
		for (int r = 1; r < 14; r++) {
			cards[i].setSuit(suit);
			cards[i].setRank(r);
			i++;
		}
	}
}
void Deck::print() const {
	for (int i = 0; i < cards.size(); i++) {
		cards[i].print();
	}
}
void Deck::shuffleDeck()
{
	for (int i = 0; i < cards.size(); i++) {
		int ind = rand() % (cards.size() - i) + i;
		Card tmp = cards[ind];
		cards[ind] = cards[i];
		cards[i] = tmp;
	}
}
Deck Deck::subDeck(int low, int high) const
{
	Deck sub(high - low + 1);

	for (int i = 0; i < sub.cards.size(); i++) {
		sub.cards[i] = cards[low + i];
	}
	return sub;
}
std::vector<Card>& Deck::getCards()
{
	// can modify the cards inside a deck or hand with this function. Use with caution.
	return cards;
}
int Deck::find(const Card& c) const
{
	for (int i = 0; i < cards.size(); i++) {
		if (c.equals(cards[i])) return true;
	}
	return false;
}
Card Deck::getRandomCard(const Deck& deck1, const Deck& deck2) const{
	int deck1Size = deck2.getDeckSize();
	int deck2Size = deck1.getDeckSize();

	int ind = deck1Size + deck2Size;

	int randomInd = rand() % (getDeckSize() - ind) + ind;

	Card randomCard = cards[randomInd];
	return randomCard;
}
int Deck::getDeckSize() const
{
	return cards.size();
}
