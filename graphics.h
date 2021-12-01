#ifndef GRAPHICS_H_IS_INCLUDED
#define GRAPHICS_H_IS_INCLUDED

#include "generic.h"
#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
#include "ysglfontdata.h"

// Still under progress
// Solitaire uses graphics for the intial debugging

// Add all graphics functions here
// Try to add game-specific functions in respective header files

// Push on github any time you update so that everyone can use the latest version

class Card; // Do NOT remove. Program will fail if removed.

class MainData
{
private:
	YsRawPngDecoder* png;
	GLuint* texId;
	int nPics;
	std::vector<int> windowDims;
	int money;
	std::string playerName;

public:
	bool* rendered; // do not modify
	std::string soundName;

	MainData();
	MainData(const int);
	void CleanUp();
	~MainData();
	YsRawPngDecoder* getPNGPointer() const; // store all png files
	GLuint* getTexPointer() const; // for texture mapping
	int getNumPics() const;
	void Create(const int); // dynamically allocates memory to pointers
	void DecodeImages(); // decodes images
	std::vector<int> getWindowDimensions() const;
	void setWindowDimensions(const int, const int);
	void setPlayerName(std::string);
	void setMoney(const int num); // send num as the amount you want to decrease or increase the money
	int getMoney() const;
	std::string getPlayerName()const;
	std::string getMoneyChar() const;

};

void Render(const MainData& dat, const double x, const double y, const int index); // main render function
void Render(const MainData& dat, const double x, const double y, const int index, double scale); // overloaded function with scale
void ColorBackGround(); 
void ColorGreenBackGround();
void ColorGameBackGround();
void PrintCardSolitaire(const MainData& dat, const Card, double, double, int);
int getIndexForGraphics(const Card);
void DisplayGames();
void DisplayMoneyAndName(const MainData&);
void EndGameOptions();
#endif
