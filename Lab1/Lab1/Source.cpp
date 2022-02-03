#include <iostream>

int main() {
	//initial stage
	int i = 0, j = 0, k = 0; // for loops
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
	int* newArrayInt;
	char* newArrayChar;
	char** newArrayCharChars;

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
			newArrayChar = new char[allTextLen];
			j = 0;
		expand_char_rewrite1:
			newArrayChar[j] = allText[j];
			j++;
			if (j < allTextLen / 2)
				goto expand_char_rewrite1;
			delete[] allText;
			allText = newArrayChar;

		}
		if (allText[i] == ' ' || allText[i] == '\n' || allText[i] == EOF) //parse word
		{
			nextWord = i;
			if (nextWord == prevWord)
			{
				prevWord++;
				goto continue_reading;
			}
			j = 0;
		copy_word: // copy by symbols
			wordsArray[currentWordsArrayLen][j] = allText[prevWord + j];
			currentWordsLen[currentWordsArrayLen]++;
			if (currentWordsLen[currentWordsArrayLen] >= wordsLen[currentWordsArrayLen]) // expand word
			{	
				wordsLen[currentWordsArrayLen] *= 2;
				newArrayChar = new char[wordsLen[currentWordsArrayLen]];
				k = 0;
			expand_char_rewrite2:
				newArrayChar[k] = wordsArray[currentWordsArrayLen][k];
				k++;
				if (k < wordsLen[currentWordsArrayLen] / 2)
					goto expand_char_rewrite2;
				delete[] wordsArray[currentWordsArrayLen];
				wordsArray[currentWordsArrayLen] = newArrayChar;
			}
			continue_pushing_word:
					j++;
					if (j < nextWord - prevWord)
						goto copy_word;
			prevWord = nextWord + 1;
			currentWordsArrayLen++;

			if (currentWordsArrayLen >= wordsArrayLen) //expand word array
			{
				wordsArrayLen *= 2;	//expand max length
				newArrayInt = new int[wordsArrayLen]();
				j = 0;
			expand_int_rewrite1:
				newArrayInt[i] = wordsLen[i];
				j++;
				if (j < wordsArrayLen / 2)
					goto expand_int_rewrite1;
			initialize_starter_len:
					newArrayInt[j] = 10;
					j++;
					if (j < wordsArrayLen)
						goto initialize_starter_len;
				delete[] wordsLen;
				wordsLen = newArrayInt;

				newArrayInt = new int[wordsArrayLen](); //expand current length
				j = 0;
			expand_int_rewrite2:
				newArrayInt[j] = currentWordsLen[j];
				j++;
				if (j < wordsArrayLen / 2)
					goto expand_int_rewrite2;
				delete[] currentWordsLen;
				currentWordsLen = newArrayInt;

				newArrayCharChars = new char* [wordsArrayLen]; //expand word array
				j = 0;
			expand_initialize_words1:
				newArrayCharChars[j] = new char[wordsLen[j]];
				j++;
				if (j < wordsArrayLen)
					goto expand_initialize_words1;

				j = 0;
			expand_char_of_chars_rewrite1:
				newArrayCharChars[j] = wordsArray[j];
				j++;
				if (j < wordsArrayLen / 2)
					goto expand_char_of_chars_rewrite1;
				delete[]wordsArray;
				wordsArray = newArrayCharChars;
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