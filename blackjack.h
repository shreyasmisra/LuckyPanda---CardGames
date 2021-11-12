#ifndef BLACKJACK_H_IS_INCLUDED
#define BLACKJACK_H_IS_INCLUDED

#include <string>
#include <iostream>

#include "generic.h"

class PlayerHand;
class DealerHand;
class BlackJack;

class DealerHand : public Deck {
private:
	Deck hand;
	int sum=0;
	bool showBothCards = false;
public:

	void createHand(const Deck&);
	void showHand(); // Should become drawHand

	int getSum() const;
	void countHand();
	void changeBool(bool);
	Deck getHand() const;
	void addCard(const Card&);
	void setSum(int);
};

class PlayerHand : public Deck {
private:
	Deck hand;
	int sum=0;
	int move;
	std::string name;
public:

	void setName(std::string);
	void createHand(const Deck&);
	void showHand();
	int getSum() const;
	void countHand();
	int getMove() const;
	void setMove(std::istream&);
	Deck getHand() const;
	void addCard(const Card&);
};


class BlackJack {
private:
	const int MAX_HITS = 5;
	const int DEALER_MIN_SUM = 17;
	Card ace1;
	Card ace2;
	Card ace3;
	Card ace4;
	Deck mainDeck;
	PlayerHand user;
	DealerHand comp;

	bool gameOver = false;
	int numHits = 0;

	std::string dealer_name = "Computer";
	std::string player_name;

public:

	BlackJack();

	int checkWinner() const;
	void getUserInput() const;
	void playBlackJack();
};

#endif
