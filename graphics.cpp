#include <iostream>
#include <cmath>
#include <string>

#include "graphics.h"

#include "fssimplewindow.h"
#include "yspng.h"
#include "yspngenc.h"
#include "ysglfontdata.h"


MainData::MainData() {
	nPics = 0;
	png = nullptr;
	texId = nullptr;
}
MainData::MainData(const int num) {
	nPics = num;
	png = new YsRawPngDecoder[num];
	texId = new GLuint[num];
}
void MainData::CleanUp() {
	delete[] png;
	delete[] texId;
	png = nullptr;
	texId = nullptr;
}
MainData::~MainData() {
	CleanUp();
}
YsRawPngDecoder* MainData::getPNGPointer() const
{
	if (texId != nullptr) {
		return png;
	}
}
GLuint* MainData::getTexPointer() const
{
	if (texId != nullptr) {
		return texId;
	}
}
int MainData::getNumPics() const
{
	return nPics;
}
void MainData::Create(const int x)
{
	if (png != nullptr || texId != nullptr) {
		CleanUp();
	}
	nPics = x;
	png = new YsRawPngDecoder[nPics];
	texId = new GLuint[nPics];
}
void MainData::DecodeImages() {

	// These indices have to be used to display images.
	// Line 242 -> graphics.cpp -> Function to recover these indices from rank and suit (will update soon).

	std::cout << "Reading the images, please wait...\n";

	this->getPNGPointer()[0].Decode("red_back.png");
	// rank = 1, all suits
	this->getPNGPointer()[1].Decode("AC.png");
	this->getPNGPointer()[2].Decode("AD.png");
	this->getPNGPointer()[3].Decode("AH.png");
	this->getPNGPointer()[4].Decode("AS.png");
	// rank = 2, all suits
	this->getPNGPointer()[5].Decode("2C.png");
	this->getPNGPointer()[6].Decode("2D.png");
	this->getPNGPointer()[7].Decode("2H.png");
	this->getPNGPointer()[8].Decode("2S.png");
	// rank = 3, all suits
	this->getPNGPointer()[9].Decode("3C.png");
	this->getPNGPointer()[10].Decode("3D.png");
	this->getPNGPointer()[11].Decode("3H.png");
	this->getPNGPointer()[12].Decode("3S.png");
	// rank = 4, all suits
	this->getPNGPointer()[13].Decode("4C.png");
	this->getPNGPointer()[14].Decode("4D.png");
	this->getPNGPointer()[15].Decode("4H.png");
	this->getPNGPointer()[16].Decode("4S.png");
	// rank = 5, all suits
	this->getPNGPointer()[17].Decode("5C.png");
	this->getPNGPointer()[18].Decode("5D.png");
	this->getPNGPointer()[19].Decode("5H.png");
	this->getPNGPointer()[20].Decode("5S.png");
	// rank = 6, all suits
	this->getPNGPointer()[21].Decode("6C.png");
	this->getPNGPointer()[22].Decode("6D.png");
	this->getPNGPointer()[23].Decode("6H.png");
	this->getPNGPointer()[24].Decode("6S.png");
	// rank = 7, all suits
	this->getPNGPointer()[25].Decode("7C.png");
	this->getPNGPointer()[26].Decode("7D.png");
	this->getPNGPointer()[27].Decode("7H.png");
	this->getPNGPointer()[28].Decode("7S.png");
	// rank = 8, all suits
	this->getPNGPointer()[29].Decode("8C.png");
	this->getPNGPointer()[30].Decode("8D.png");
	this->getPNGPointer()[31].Decode("8H.png");
	this->getPNGPointer()[32].Decode("8S.png");
	// rank = 9, all suits
	this->getPNGPointer()[33].Decode("9C.png");
	this->getPNGPointer()[34].Decode("9D.png");
	this->getPNGPointer()[35].Decode("9H.png");
	this->getPNGPointer()[36].Decode("9S.png");
	// rank = 10, all suits
	this->getPNGPointer()[37].Decode("10C.png");
	this->getPNGPointer()[38].Decode("10D.png");
	this->getPNGPointer()[39].Decode("10H.png");
	this->getPNGPointer()[40].Decode("10S.png");
	// rank = 11, all suits
	this->getPNGPointer()[41].Decode("JC.png");
	this->getPNGPointer()[42].Decode("JD.png");
	this->getPNGPointer()[43].Decode("JH.png");
	this->getPNGPointer()[44].Decode("JS.png");
	// rank = 12, all suits
	this->getPNGPointer()[45].Decode("QC.png");
	this->getPNGPointer()[46].Decode("QD.png");
	this->getPNGPointer()[47].Decode("QH.png");
	this->getPNGPointer()[48].Decode("QS.png");
	// rank = 13, all suits
	this->getPNGPointer()[49].Decode("KC.png");
	this->getPNGPointer()[50].Decode("KD.png");
	this->getPNGPointer()[51].Decode("KH.png");
	this->getPNGPointer()[52].Decode("KS.png");

	for (int i = 0; i < this->getNumPics(); ++i) {
		this->getPNGPointer()[i].Flip();
	}
}

void Render(const MainData& dat, const double x, const double y, const int index) {

	// Under construction
	// Main function to display each card at given position

	glGenTextures(1, &dat.getTexPointer()[index]);
	glBindTexture(GL_TEXTURE_2D, dat.getTexPointer()[index]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		dat.getPNGPointer()[index].wid,
		dat.getPNGPointer()[index].hei,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		dat.getPNGPointer()[index].rgba);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, dat.getTexPointer()[index]);

	// To scale and translate images use this code below -- 

	/*int xSize = dat.png[index].wid * dat.scales[index];
	int ySize = dat.png[index].hei * dat.scales[index];*/

	/*glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(x - dat.translate[index], y);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(x + xSize - dat.translate[index], y);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(x + xSize - dat.translate[index], y - ySize);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(x - dat.translate[index], y - ySize);
	glEnd();*/

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(x, y);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(x + dat.getPNGPointer()[index].wid, y);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(x + dat.getPNGPointer()[index].wid, y - dat.getPNGPointer()[index].hei);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(x, y - dat.getPNGPointer()[index].hei);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void ColorBackGround()
{
	// Green background. will be replaced with image later

	glColor3ub(0, 90, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(800, 0);
	glVertex2i(800, 800);
	glVertex2i(0, 800);
	glEnd();
	glFlush();
}

void PrintCardSolitaire(const Card c, double cx1, double cy1)
{
	auto r = std::to_string(c.getRank());

	char const* rchar = r.c_str();

	glColor3ub(255, 100, 100);
	glRasterPos2i(cx1, cy1);
	YsGlDrawFontBitmap10x14(rchar);
	glRasterPos2i(cx1, cy1 + 20);
	if (c.getSuit() == 0)
	{
		char const* schar = "Clubs";
		YsGlDrawFontBitmap10x14(schar);
	}
	else if (c.getSuit() == 1)
	{
		char const* schar = "Diamonds";
		YsGlDrawFontBitmap10x14(schar);
	}
	else if (c.getSuit() == 2)
	{
		char const* schar = "Hearts";
		YsGlDrawFontBitmap10x14(schar);
	}
	else if (c.getSuit() == 3)
	{
		char const* schar = "Spades";
		YsGlDrawFontBitmap10x14(schar);
	}
}

int getIndexForGraphics(const Card card)
{
 // To correspond the rank and suit to the indices in which the images are decoded. Line 56 -> graphics.cpp
 
	int r = card.getRank();
	int s = card.getSuit();
	int start_ind = 0 * std::pow(r, 0) + 1.29352467e+00 * std::pow(r, 1) + 1.56013800e+00 * std::pow(r, 2) + 3.42561238e-01 * std::pow(r, 3) +
		-8.22833655e-01 * std::pow(r, 4) + 4.46845893e-01 * std::pow(r, 5) + -1.33165320e-01 * std::pow(r, 6) + 2.50205427e-02 * std::pow(r, 7) +
		-3.09091570e-03 * std::pow(r, 8) + 2.51138004e-04 * std::pow(r, 9) + -1.29372905e-05 * std::pow(r, 10) + 3.83363400e-07 * std::pow(r, 11) +
		-4.97902763e-09 * std::pow(r, 12);


	int graphicsIndex = start_ind + s - 1;

	return graphicsIndex;
}


