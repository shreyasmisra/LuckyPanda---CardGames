#ifndef BLACKJACK_H_IS_INCLUDED
#define BLACKJACK_H_IS_INCLUDED

#include <string>
#include <iostream>

#include "generic.h"
#include "graphics.h"
#include "fssimplewindow.h"

// classes for blackjack

class Player;
class Dealer;
class BlackJack;

class Dealer : public Deck {
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

	// drawing functions
	void initCoordinates();
	void drawOne(const MainData&);
	void drawTwo(const MainData&);
	void showSum() const;
	void setCoordinates();
};

class Player : public Deck {
private:
	Deck hand;
	int sum=0;
	int move;
	int bet;
	int totalMoney = 1000;
	std::string name;
public:

	void setName(std::string);
	void createHand(const Deck&);
	void showHand();
	int getSum() const;
	void setSum(const int);
	void countHand();
	int getMove() const;
	void setMove(const int);
	Deck getHand() const;
	void addCard(const Card&);
	void setBet(const int);
	void setRemMoney(const int);
	int getBet() const;
	int getRemMoney() const;

	// Drawing functions
	void initCoordinates();
	void drawHand(const MainData&);
	void showSum() const;
	void setCoordinates();
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
	Player user;
	Dealer comp;
	

	bool playerTurn = true;
	bool dealerTurn = false;
	bool goToWinner = false;
	int playerState = 0;
	int betdx = 50;

	int numHits = 0;
	int bet = 0;
	char userIn;
	int userMove;
public:
	const char* playerName;
	bool playGame = false;
	bool getBet = false;

	BlackJack();

	void PlayerTurn();
	void DealerTurn();

	void setHands();
	int checkWinner() const;
	void getUserInput() const;
	int playBlackJack(MainData&, int);
	void playBlackJackMultipleTimes(const MainData&);

	// Drawing functions
	void DisplayOptions() const;
	void DisplayMoney() const;
	void DisplayCards(const MainData&);
	void EndGameOptions() const;
	void DisplayBlackJackBackground(const MainData&) const;
};

#endif
