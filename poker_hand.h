#ifndef POKER_HAND_H_IS_INCLUDED
#define POKER_HAND_H_IS_INCLUDED

#include <vector>
#include <iostream>

#include "generic.h"

using namespace std;

// classes for poker 


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
void playpokerhand(int&, int&);

#endif
