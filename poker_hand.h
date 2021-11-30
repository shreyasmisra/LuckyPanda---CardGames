#ifndef POKER_HAND_H_IS_INCLUDED
#define POKER_HAND_H_IS_INCLUDED

#include <vector>
#include <iostream>
#include "graphics.h"
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
	Card pcards[7];
	player();
	~player();
	void pbalance(int pbalance, int pbet);
	int getScore() const;
	int getMoney() const;
	void addcard(int position, int rank, int suit);
	void printcard() const;
	void sort();
	void addscore(int p);
	int checkorraise(bool& raise, int onecpubet, int pbet, int cpubet, const int pindex[2], const int cpuindex[2], const int openindex[2], int, MainData&);
	int fcheckorraise(bool& raise, int onecpubet, int pbet, int cpubet, const int pindex[2], const int cpuindex[2], const int openindex[2], int, MainData&);
};

//CPU Class
class Cpu {
private:
	int cbet = 0;
	int cpumoney = 0;
	int cpuscore = 0;
public:
	Card cpucards[7];
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

int pairs(Card cards[7]);
int nofkinds(Card cards[7]);
int straight(Card cards[7]);
int fullhouse(Card cards[7]);
void tiebreaker(int& cpupoints, int& ppoints, Card ccards[7], Card pcards[7]);
//int pokerhand(Cpu cpu, player player, int& pbalance, int& cpubalance, MainData dat);
int playpokerhand(int, int, MainData& dat);
void playertag(int pbet, int cpubet, int pbalance);
#endif
