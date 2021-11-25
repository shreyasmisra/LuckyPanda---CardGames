#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <string.h>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "text_input.h"


TextString::TextString()
{
	str = nullptr;
}
TextString::~TextString()
{
	CleanUp();
}
void TextString::CleanUp()
{
	delete[] str;
	str = nullptr;
}

TextString::TextString(const char from[])
{
	str = nullptr;
	Set(from);
}
TextString::TextString(const TextString& from)
{
	str = nullptr;
	Set(from.GetPointer());
}
TextString& TextString::operator=(const TextString& from)
{
	Set(from.GetPointer());
	return *this;
}

void TextString::Set(const char from[])
{
	if (nullptr == from)
	{
		CleanUp();
	}
	else if (from != str)
	{
		CleanUp();

		int len = strlen(from);
		if (0 != len)
		{
			str = new char[len + 1];
			strcpy(str, from);
		}
	}
}
void TextString::Add(const char from[])
{
	if (from != str)
	{
		for (int i = 0; 0 != from[i]; ++i)
		{
			Add(from[i]);
		}
	}
	else
	{
		TextString tmp;
		tmp.Set(from);
		for (int i = 0; 0 != tmp.GetPointer()[i]; ++i)
		{
			Add(tmp.GetPointer()[i]);
		}
	}
}
void TextString::Add(const char c)
{
	int len = Strlen();

	char* tmp = new char[len + 1 + 1];  // (1) Allocate +1 for terminator, +1 for c

	strcpy(tmp, GetPointer());   // (2) Make a copy
	tmp[len] = c;
	tmp[len + 1] = 0;

	CleanUp();        // (3) Clean up

	str = tmp;   // (4) Re-point
}
void TextString::BackSpace(void)  // <-> std::string::pop_back
{
	int len = Strlen();
	if (0 < len)
	{
		char* tmp = new char[len];  // (1) Allocate
		str[len - 1] = 0;
		strcpy(tmp, GetPointer());  // (2) Make a copy

		CleanUp();  // (3) Clean up

		str = tmp;
	}
}
const char* TextString::GetPointer(void) const
{
	if (nullptr != str)
	{
		return str;
	}
	else
	{
		return "";
	}
}
const int TextString::Strlen(void) const
{
	return strlen(GetPointer());
}
void TextString::Print(void) const
{
	printf("%s\n", GetPointer());
}

const char* TextString::Fgets(FILE* fp)  // <-> std::getline
{
	const int bufLen = 256;
	bool hasContents = false;

	CleanUp();

	char buf[bufLen];
	while (nullptr != fgets(buf, bufLen - 1, fp))
	{
		for (int i = 0; 0 != buf[i]; ++i)
		{
			if (buf[i] == '\n')
			{
				return GetPointer();
			}
			else
			{
				hasContents = true;
				Add(buf[i]);
			}
		}
	}

	return (hasContents == true ? GetPointer() : nullptr);
}


const TextString& TextInput::GetText(void) const
{
	return str;
}

int TextInput::RunOneStep(void)
{
	FsPollDevice();
	auto c = FsInkeyChar();
	if (' ' <= c)
	{
		str.Add(c);
	}
	auto k = FsInkey();
	if (FSKEY_BS == k)
	{
		str.BackSpace();
	}

	return k;
}
void TextInput::Draw(void) const
{
	TextString tmp = str;

	switch (time(nullptr) % 2)
	{
	case 0:
		tmp.Add('_');
		break;
	case 1:
		tmp.Add('|');
		break;
	}

	glColor3ub(255, 0, 0);
	glRasterPos2i(370, 700);
	YsGlDrawFontBitmap20x28(tmp.GetPointer());
}