#ifndef TEXT_INPUT_H_IS_INCLUDED
#define TEXT_INPUT_H_IS_INCLUDED

#include <string.h>

#include "fssimplewindow.h"
#include "ysglfontdata.h"

class TextString;
class TextInput;

class TextString
{
protected:
	char* str = nullptr;

public:
	TextString();
	~TextString();
	void CleanUp();

	TextString(const char from[]);
	TextString(const TextString& str);
	TextString& operator=(const TextString& from);

	void Set(const char from[]);
	void Add(const char from[]);
	void Add(const char c);
	void BackSpace(void);
	const char* GetPointer(void) const;
	const int Strlen(void) const;
	void Print(void) const;

	const char* Fgets(FILE* fp);
};

class TextInput
{
protected:
	TextString str;
public:
	const TextString& GetText(void) const;

	int RunOneStep(void);
	void Draw(void) const;
};

#endif
