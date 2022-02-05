#include<stdio.h>
#include<iostream>

int main() {
	//initial stage
	int i = 0, j = 0, k = 0; // for loops
	bool isOldWord = false;
	bool isStopWord = false;
	int prevWord = 0;
	int nextWord = 0;

	const int N = 45; // strings in one page
	const int maxPages = 100; // strings in one page
	int currentString = 0;

	int allTextLen = 101;
	int currentAllTextLen = 0;
	char* allText = new char[allTextLen];

	int wordsArrayLen = 15;
	int currentWordsArrayLen = 0;
	char** wordsArray = new char* [wordsArrayLen];

	int* wordsLen = new int[wordsArrayLen];
	int* currentWordsLen = new int[wordsArrayLen]();
	char* intToString;


	int** pagesArray = new int*[wordsArrayLen];
	int* pagesLen = new int[wordsArrayLen]();
	int* currentPagesLen = new int[wordsArrayLen]();

	i = 0;
initialize_words:
	wordsLen[i] = 10;
	wordsArray[i] = new char[wordsLen[i]];
	pagesLen[i] = 10;
	pagesArray[i] = new int[pagesLen[i]]();
	i++;
	if (i < wordsArrayLen)
		goto initialize_words;


	const char* stopWords[] = { "i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now" };
	int stopWordsLen = 127;

	FILE* fp;
	//for expand
	int* newArrayInt;
	char* newArrayChar;
	char** newArrayCharChars;
	int** newArrayIntInts;
	//for sort
	int temp;
	char* tempWord;
	int* wordPages;
	bool isNeedSwap = false;


	//for output
	int copyInt;
	int count;


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
		if (currentAllTextLen >= allTextLen) //expand allText
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
		if (allText[i] == '\n')
			currentString++;
		if (allText[i] < 97 || allText[i] > 122) //parse word
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

			wordsArray[currentWordsArrayLen][j] = '\0';
			currentWordsLen[currentWordsArrayLen]++;

			prevWord = nextWord + 1;


			pagesArray[currentWordsArrayLen][0] = (currentString / N) + 1;
			currentPagesLen[currentWordsArrayLen] = 1;
			

			j = 0;   //find a word in the array
			if (currentWordsArrayLen != 0)
			{
				isStopWord = false;
				isOldWord = false;
			finding_word:
				isOldWord = true;
				if (currentWordsLen[currentWordsArrayLen] != currentWordsLen[j])
					isOldWord = false;
				if (isOldWord)
				{
					k = 0;
				compare_words:
					if (wordsArray[currentWordsArrayLen][k] != wordsArray[j][k])
					{
						isOldWord = false;
					}
					k++;
					if (isOldWord && k < currentWordsLen[currentWordsArrayLen])
						goto compare_words;
				}


				if (isOldWord) //dont remember word
				{
					currentWordsLen[currentWordsArrayLen] = 0;
					currentPagesLen[currentWordsArrayLen] = 0;
					if (currentPagesLen[j] <= maxPages + 1)
					{
						pagesArray[j][currentPagesLen[j]] = (currentString / N) + 1; // remeber a page
						currentPagesLen[j]++;
						if (currentPagesLen[j] >= pagesLen[j]) {
							pagesLen[j] *= 2;
							newArrayInt = new int[pagesLen[j]]();
							k = 0;
						expand_int_rewrite0:
							newArrayInt[k] = pagesArray[j][k];
							k++;
							if (k < pagesLen[j] / 2)
								goto expand_int_rewrite0;
							delete[] pagesArray[j];
							pagesArray[j] = newArrayInt;
						}
					}
					currentWordsArrayLen--;
				}
				j++;
				if (!isOldWord && j < currentWordsArrayLen)
					goto finding_word;

			}
			if (!isOldWord) //find word in stop words
			{
				j = 0;
			finding_stop_words:
				isStopWord = true;
				k = 0;
			compare_with_stop_words:
				if (stopWords[j][k] != '\0' && stopWords[j][k] == wordsArray[currentWordsArrayLen][k])
				{
					k++;
					goto compare_with_stop_words;
				}
				if (stopWords[j][k] != wordsArray[currentWordsArrayLen][k])
				{
					isStopWord = false;
				}
				j++;
				if (!isStopWord && j + 1 < stopWordsLen)
					goto finding_stop_words;
			}
			if (isStopWord)
			{
				currentWordsLen[currentWordsArrayLen] = 0;
				currentWordsArrayLen--;
			}



			/*if (currentWordsArrayLen >= 0)
			{
				pagesArray[currentWordsArrayLen][currentPagesLen[currentWordsArrayLen]] = (currentString / N) + 1;
				currentPagesLen[currentWordsArrayLen]++;
				if (currentPagesLen[currentWordsArrayLen] >= pagesLen[currentWordsArrayLen]) {
					pagesLen[currentWordsArrayLen] *= 2;
					newArrayInt = new int[pagesLen[currentWordsArrayLen]]();
					j = 0;
				expand_int_rewrite0:
					newArrayInt[j] = pagesArray[currentWordsArrayLen][j];
					j++;
					if (j < pagesLen[currentWordsArrayLen] / 2)
						goto expand_int_rewrite0;
					delete[] pagesArray[currentWordsArrayLen];
					pagesArray[currentWordsArrayLen] = newArrayInt;
				}
			}*/


			currentWordsArrayLen++;
			if (currentWordsArrayLen >= wordsArrayLen) //expand word array
			{
				wordsArrayLen *= 2;	//expand max length
				newArrayInt = new int[wordsArrayLen]();
				j = 0;
			expand_int_rewrite1:
				newArrayInt[j] = wordsLen[j];
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



				newArrayInt = new int[wordsArrayLen](); // expand pages max len
				j = 0;
			expand_int_rewrite2:
				newArrayInt[j] = pagesLen[j];
				j++;
				if (j < wordsArrayLen / 2)
					goto expand_int_rewrite2;
			initialize_starter_len1:
				newArrayInt[j] = 10;
				j++;
				if (j < wordsArrayLen)
					goto initialize_starter_len1;
				delete[] pagesLen;
				pagesLen = newArrayInt;



				newArrayInt = new int[wordsArrayLen](); //expand current length
				j = 0;
			expand_int_rewrite3:
				newArrayInt[j] = currentWordsLen[j];
				j++;
				if (j < wordsArrayLen / 2)
					goto expand_int_rewrite3;
				delete[] currentWordsLen;
				currentWordsLen = newArrayInt;


				newArrayInt = new int[wordsArrayLen](); //expand current pages length
				j = 0;
			expand_int_rewrite4:
				newArrayInt[j] = currentPagesLen[j];
				j++;
				if (j < wordsArrayLen / 2)
					goto expand_int_rewrite4;
				delete[] currentPagesLen;
				currentPagesLen = newArrayInt;


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


				newArrayIntInts = new int* [wordsArrayLen]; //expand int** array
				j = 0;
			expand_initialize_ints1:
				newArrayIntInts[j] = new int[pagesLen[j]];
				j++;
				if (j < wordsArrayLen)
					goto expand_initialize_ints1;

				j = 0;
			expand_int_of_ints_rewrite1:
				newArrayIntInts[j] = pagesArray[j];
				j++;
				if (j < wordsArrayLen / 2)
					goto expand_int_of_ints_rewrite1;
				delete[]pagesArray;
				pagesArray = newArrayIntInts;
			}
		}
	continue_reading:
		if (allText[i] != EOF)
		{
			i++;
			goto reading;
		}


		//sort
		i = 0;
	sort_outer_loop:
		j = i + 1;
	sort_inner_loop:
		k = 0;
		isNeedSwap = false;
		while (wordsArray[i][k] != 0 && wordsArray[i][k] == wordsArray[j][k])
		{
			k++;
		}
		isNeedSwap = wordsArray[i][k] > wordsArray[j][k];
		if (isNeedSwap)
		{
			wordPages = pagesArray[i]; //swap pages
			pagesArray[i] = pagesArray[j];
			pagesArray[j] = wordPages;

			temp = pagesLen[i]; //swap mex len pages
			pagesLen[i] = pagesLen[j];
			pagesLen[j] = temp;


			temp = currentPagesLen[i]; //swap current len pages
			currentPagesLen[i] = currentPagesLen[j];
			currentPagesLen[j] = temp;


			tempWord = wordsArray[i]; //swap words
			wordsArray[i] = wordsArray[j];
			wordsArray[j] = tempWord;

			temp = wordsLen[i]; //swap mex len words
			wordsLen[i] = wordsLen[j];
			wordsLen[j] = temp;

			temp = currentWordsLen[i]; //swap current len words
			currentWordsLen[i] = currentWordsLen[j];
			currentWordsLen[j] = temp;
		}
		j++;
		if (j < currentWordsArrayLen)
			goto sort_inner_loop;
		i++;
		if (i < currentWordsArrayLen - 1)
			goto sort_outer_loop;
	}
	fclose(fp);



	//output result

	//if (fopen_s(&fp, "D:\\output.txt", "w") == 0 && currentWordsArrayLen) {
	//	i = 0;
	//output_result:
	//	wordsArray[i][currentWordsLen[i] - 1] = ' ';
	//	wordsArray[i][currentWordsLen[i]] = '-';
	//	currentWordsLen[i]++;
	//	wordsArray[i][currentWordsLen[i]] = ' ';
	//	currentWordsLen[i]++;
	//	copyInt = termFreequency[i] + 1;
	//	count = 0;;
	//	intToString = new char[10];

	//	j = 0;
	//copy_int_in_string:
	//	intToString[j] = (char)48 + (copyInt % 10);
	//	copyInt = copyInt / 10;
	//	j++;
	//	count++;
	//	if (copyInt > 0)
	//		goto copy_int_in_string;

	//	j = 0;
	//add_int_to_string:
	//	wordsArray[i][currentWordsLen[i]] = intToString[count - 1 - j];
	//	currentWordsLen[i]++;

	//	if (currentWordsLen[currentWordsArrayLen] >= wordsLen[currentWordsArrayLen]) // expand string
	//	{
	//		wordsLen[currentWordsArrayLen] *= 2;
	//		newArrayChar = new char[wordsLen[currentWordsArrayLen]];
	//		k = 0;
	//	expand_char_rewrite3:
	//		newArrayChar[k] = wordsArray[currentWordsArrayLen][k];
	//		k++;
	//		if (k < wordsLen[currentWordsArrayLen] / 2)
	//			goto expand_char_rewrite3;
	//		delete[] wordsArray[currentWordsArrayLen];
	//		wordsArray[currentWordsArrayLen] = newArrayChar;
	//	}
	//	j++;
	//	if (j < count)
	//		goto add_int_to_string;


	//	wordsArray[i][currentWordsLen[i]] = '\n';
	//	currentWordsLen[i]++;
	//	wordsArray[i][currentWordsLen[i]] = '\0';
	//	fputs(wordsArray[i], fp);
	//	delete[] intToString;
	//	i++;
	//	if (i < currentWordsArrayLen && i < N)
	//		goto output_result;
	//}
	for (int i = 0; i < currentWordsArrayLen; i++)
	{
		if (wordsArray[i][0] == 'm' && wordsArray[i][1] == 'r')
			int k = currentPagesLen[i];
		if (currentPagesLen[i] < maxPages + 1)
		{
			std::cout << wordsArray[i] << " ";
			for (int j = 0; j < currentPagesLen[i]; j++)
			{
				std::cout << pagesArray[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
	return 0;
}