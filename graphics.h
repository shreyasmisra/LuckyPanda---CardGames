#ifndef GRAPHICS_H_IS_INCLUDED
#define GRAPHICS_H_IS_INCLUDED

#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
#include "ysglfontdata.h"
#include "generic.h"

// Includes all the classes for graphics.
// Still under progress
// Solitaire uses graphics for the intial debugging

// Add all graphics functions here
// Try to add game-specific functions in respective header files

// Push on github any time you update so that everyone can use the latest version

class MainData
{
private:
	YsRawPngDecoder* png;
	GLuint* texId;
	int nPics;

public:

	MainData();
	MainData(const int);
	void CleanUp();
	~MainData();
	YsRawPngDecoder* getPNGPointer() const; // store all png files
	GLuint* getTexPointer() const; // for texture mapping
	int getNumPics() const;
	void Create(const int); // dynamically allocates memory to pointers
	void DecodeImages(); // decodes images
};

void Render(const MainData& dat, const double x, const double y, const int index); // main render function
void ColorBackGround(); // Gree color for now
void SetIndexForGraphics(Card& card); // Work ongoing
void PrintCardSolitaire(const Card, double cx1, double cy1); // solitaire

#endif
