#include <iostream>

int main() {
	//initial stage
	int i = 0;
	int prevWord = 0;
	int nextWord = 0;

	int allTextLen = 10;
	int currentAllTextLen = 0;
	char* allText = new char[allTextLen];

	int wordsArrayLen = 10;
	int currentWordsArrayLen = 0;
	char** wordsArray = new char* [wordsArrayLen];
	int* termFreequency = new int[wordsArrayLen];

	int* wordsLen = new int[wordsArrayLen];
	int* currentWordsLen = new int[wordsArrayLen]();

	i = 0;
initialize_words:
	wordsLen[i] = 10;
	wordsArray[i] = new char[wordsLen[i]];
	i++;
	if (i < wordsArrayLen)
		goto initialize_words;

	FILE* fp;
	//for expand
	int newLen;
	int** oldArrayInt;
	char** oldArrayChar;
	char*** oldArrayCharChars;
	int* newArrayInt;
	char* newArrayChar;
	char** newArrayCharChars;

	goto skipFunctions;
	// expand arrays dynamically
expand_int:
	newArrayInt = new int[newLen]();

	i = 0;
expand_int_rewrite:
	newArrayInt[i] = (*oldArrayInt)[i];
	i++;
	if (i < newLen / 2)
		goto expand_int_rewrite;
	delete[] * oldArrayInt;
	*oldArrayInt = newArrayInt;
	__asm {
		pop eax
		pop i
		jmp eax;
	}


expand_char:
	newArrayChar = new char[newLen];
	i = 0;
expand_char_rewrite:
	newArrayChar[i] = (*oldArrayChar)[i];
	++i;
	if (i < newLen / 2)
		goto expand_char_rewrite;
	delete[] * oldArrayChar;
	*oldArrayChar = newArrayChar;
	__asm {
		pop eax
		pop i
		jmp eax;
	}


expand_char_of_chars:
	newArrayCharChars = new char* [newLen];

	i = 0;
expand_initialize_words:
	newArrayCharChars[i] = new char[wordsLen[i]];
	i++;
	if (i < newLen)
		goto expand_initialize_words;

	i = 0;
expand_char_of_chars_rewrite:
	newArrayCharChars[i] = (*oldArrayCharChars)[i];
	++i;
	if (i < newLen / 2)
		goto expand_char_of_chars_rewrite;
	delete[](*oldArrayCharChars);
	*oldArrayCharChars = newArrayCharChars;
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
		if (allText[i] <= 90 && allText[i] >= 65)
		{
			allText[i] += 32;
		}
		currentAllTextLen++;
		if (currentAllTextLen >= allTextLen)
		{
			allTextLen *= 2;
			newLen = allTextLen;
			oldArrayChar = &allText;
			__asm {
				push i;
				push offset continue_reading
			}
			goto expand_char;
		}
		if (allText[i] == ' ' || allText[i] == '\n' || allText[i] == EOF) //parse word
		{
			nextWord = i;
			if (nextWord == prevWord)
			{
				prevWord++;
				goto continue_reading;
			}
			__asm push i;
			i = 0;
		copy_word: // copy by symbols
			wordsArray[currentWordsArrayLen][i] = allText[prevWord + i];
			currentWordsLen[currentWordsArrayLen]++;
			if (currentWordsLen[currentWordsArrayLen] >= wordsLen[currentWordsArrayLen]) // expand word
			{	
				wordsLen[currentWordsArrayLen] *= 2;
				newLen = wordsLen[currentWordsArrayLen];
				oldArrayChar = &wordsArray[currentWordsArrayLen];
				__asm {
					push i
					push offset continue_pushing_word
				}
				goto expand_char;
			}
			continue_pushing_word:
					i++;
					if (i < nextWord - prevWord)
						goto copy_word;
			__asm pop i;
			prevWord = nextWord + 1;
			currentWordsArrayLen++;

			if (currentWordsArrayLen >= wordsArrayLen) //expand word array
			{
				wordsArrayLen *= 2;
				newLen = wordsArrayLen;
				oldArrayInt = &wordsLen;
				__asm {
					push i;
					push offset expand_current_length
				}
				goto expand_int;
			expand_current_length:
				__asm push i;
				i = 0;
			initialize_starter_len:
					if (wordsLen[i] == 0)
						wordsLen[i] = 10;
					i++;
					if (i < wordsArrayLen)
						goto initialize_starter_len;
				__asm pop i;
				oldArrayInt = &currentWordsLen;
				__asm {
					push i;
					push offset expand_words_array
				}
				goto expand_int;

			expand_words_array:
				oldArrayCharChars = &wordsArray;
				__asm {
					push i;
					push offset continue_reading
				}
				goto expand_char_of_chars;
			}
		}
	continue_reading:
		if (allText[i] != EOF)
		{
			i++;
			goto reading;
		}

		for (int i = 0; i < currentWordsArrayLen; i++)
		{
			for (int j = 0; j < currentWordsLen[i]; j++)
			{
				std::cout << wordsArray[i][j];
			}
			std::cout << "\n";
		}
	}
	// end of reading input
	return 0;
}