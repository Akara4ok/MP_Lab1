#include <iostream>
#include <stdio.h>

int main() {
	//initial stage
	int i = 0;

	int allTextLen = 10;
	int currentAllTextLen = 0;
	char* allText = new char[allTextLen];

	FILE* fp;
	//for expand
	int* newLen;
	int** oldArrayInt;
	char** oldArrayChar;
	int* newArrayInt;
	char* newArrayChar;

	goto skipFunctions;
	// expand arrays dynamically
expand_int:
	*newLen *= 2;
	newArrayInt = new int[*newLen];

	 i = 0;
expand_int_rewrite:
	newArrayInt[i] = (*oldArrayInt)[i];
	i++;
	if (i < *newLen / 2)
		goto expand_int_rewrite;
	delete[] *oldArrayInt;
	*oldArrayInt = newArrayInt;
	__asm {
		pop eax
		pop i
		jmp eax;
	}


expand_char:
	*newLen *= 2;
	newArrayChar = new char[*newLen];
	i = 0;
expand_char_rewrite:
	newArrayChar[i] = (*oldArrayChar)[i];
	++i;
	if ( i < *newLen / 2)
		goto expand_char_rewrite;
	delete[] * oldArrayChar;
	*oldArrayChar = newArrayChar;
	__asm {
		pop eax
		pop i
		jmp eax;
	}

	// end expand arrays dynamically

// main
skipFunctions:
	
	//read input
if (fopen_s(&fp, "D:\\input.txt", "r") == 0) {
	i = 0;
	reading:
		allText[i] = fgetc(fp);
		currentAllTextLen++;
		if (currentAllTextLen >= allTextLen)
		{
			__asm push i;
			newLen = &allTextLen;
			oldArrayChar = &allText;
			__asm {
				push offset continueReading
			}
			goto expand_char;
		}
	continueReading:
		if (allText[i] != EOF)
		{
			i++;
			goto reading;
		}

		for (int i = 0; i < currentAllTextLen; i++)
		{
			std::cout << allText[i];
		}
	}
	// end of reading input
	return 0;
}