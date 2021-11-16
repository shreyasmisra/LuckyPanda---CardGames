#ifndef POKER_HAND_H_IS_INCLUDED
#define POKER_HAND_H_IS_INCLUDED

#pragma once
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

//Player Class
class player {
private:
	int pbet = 0;
	int pmoney = 0;
	int pscore = 0;
public:
	Card pcards[5];
	player();
	~player();
	void pbalance(int pbalance, int pbet);
	int getScore() const;
	int getMoney() const;
	void addcard(int position, int rank, int suit);
	void printcard() const;
	void sort();
	void addscore(int p);
	int checkorraise(bool& raise, int onecpubet);
};

//CPU Class
class Cpu {
private:
	int cbet = 0;
	int cpumoney = 0;
	int cpuscore = 0;
public:
	Card cpucards[5];
	Cpu();
	~Cpu();
	void cpubalance(int cpubalance, int cpubet);
	int getScore() const;
	int getMoney() const;
	void addcard(int position, int rank, int suit);
	void printcard() const;
	void sort();
	void addscore(int p);
	bool callorfold(int round, int pscore) const;
	int ifraise(int pscore, int pbalance) const;
};

int pairs(Card cards[5]);
int nofkinds(Card cards[5]);
int straight(Card cards[5]);
int fullhouse(Card cards[5]);
void tiebreaker(int& cpupoints, int& ppoints, Card ccards[5], Card pcards[5]);
void pokerhand(Cpu cpu, player player, int& pbalance, int& cpubalance);

#endif
