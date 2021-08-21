//Vocabulary.c
#include"Vocabulary.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

int main(int argc, char* argv[]) {
	Vocabulary vocabulary;
	Long index;
	Long(*indexes);
	Long count;
	Word word;
	Long i = 0;

	Vocabulary_Create(&vocabulary, 3);

	index = Record(&vocabulary, "apple", "명사", "사과", "This apple is good.");
	word = Vocabulary_GetAt(&vocabulary, index);
	printf("%s %s %s %s\n", word.spelling, word.wordClass, word.meaning, word.example);

	index = Record(&vocabulary, "winter", "명사", "겨울", "Someone really likes winter.");
	word = Vocabulary_GetAt(&vocabulary, index);
	printf("%s %s %s %s\n", word.spelling, word.wordClass, word.meaning, word.example);

	index = Record(&vocabulary, "sunny", "형용사", "맑은", "What a sunny day!");
	word = Vocabulary_GetAt(&vocabulary, index);
	printf("%s %s %s %s\n", word.spelling, word.wordClass, word.meaning, word.example);

	index = Record(&vocabulary, "winter", "명사", "겨울", "I hate winter.");
	word = Vocabulary_GetAt(&vocabulary, index);
	printf("%s %s %s %s\n", word.spelling, word.wordClass, word.meaning, word.example);

	FindBySpelling(&vocabulary, "winter", &indexes, &count);
	while (i < count) {
		word = Vocabulary_GetAt(&vocabulary, indexes[i]);
		printf("%s %s %s %s\n", word.spelling, word.wordClass, word.meaning, word.example);
		i++;
	}

	if (indexes != NULL) {
		free(indexes);
		indexes = NULL;
	}

	FindByMeaning(&vocabulary, "겨울", &indexes, &count);
	i = 0;
	while (i < count) {
		word = Vocabulary_GetAt(&vocabulary, indexes[i]);
		printf("%s %s %s %s\n", word.spelling, word.wordClass, word.meaning, word.example);
		i++;
	}

	if (indexes != NULL) {
		free(indexes);
		indexes = NULL;
	}

	index = Correct(&vocabulary, 2, "명사", "(인물)사람이름", "She's name is Sunny");
	word = Vocabulary_GetAt(&vocabulary, index);
	printf("%s %s %s %s\n", word.spelling, word.wordClass, word.meaning, word.example);

	index = Erase(&vocabulary, 0);
	if (index == -1) {
		printf("지워졌습니다.\n");
	}

	Arrange(&vocabulary);
	i = 0;
	while (i < vocabulary.length) {
		word = Vocabulary_GetAt(&vocabulary, i);
		printf("%s %s %s %s\n", word.spelling, word.wordClass, word.meaning, word.example);
		i++;
	}

	Vocabulary_Destroy(&vocabulary);

	return 0;
}

void Vocabulary_Create(Vocabulary* vocabulary, Long capacity) {
	Create(&vocabulary->words, capacity, sizeof(Word));
	vocabulary->capacity = capacity;
	vocabulary->length = 0;
}

Long Load(Vocabulary* vocabulary) {
	Word word;
	Long index;
	FILE* file;
	size_t flag;
	file = fopen("Vocabulary.dat", "rb");
	if (file != NULL) {
		flag = fread(&word, sizeof(Word), 1, file);
		while (!feof(file) && flag != 0) {
			if (vocabulary->capacity > vocabulary->length) {
				index = vocabulary->length;
				Store(&vocabulary->words, index, &word, sizeof(Word));
			}
			else {
				AppendForRear(&vocabulary->words, &word, sizeof(Word));
				vocabulary->capacity++;
			}
			vocabulary->length++;
			flag = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	return vocabulary->length;
}

Long Record(Vocabulary* vocabulary, char(*spelling), char(*wordClass), char(*meaning), char(*example)) {
	Long index;
	Word word;

	//1. 철자, 품사, 의미, 예시를 입력받는다.
	//2. word에 옮겨적는다.
	strcpy(word.spelling, spelling);
	strcpy(word.wordClass, wordClass);
	strcpy(word.meaning, meaning);
	strcpy(word.example, example);

	//3. capacity가 length보다 크면 store를 호출한다.
	if (vocabulary->capacity > vocabulary->length) {
		index = vocabulary->length;
		index = Store(&vocabulary->words, index, &word, sizeof(Word));
	}
	//4. 그 반대이면 AppendForRear를 호출한다.
	else {
		index = AppendForRear(&vocabulary->words, &word, sizeof(Word));
		vocabulary->capacity++;
	}
	vocabulary->length++;
	return index;
}
void FindBySpelling(Vocabulary* vocabulary, char(*spelling), Long* (*indexes), Long* count) {
	LinearSearchDuplicate(&vocabulary->words, spelling, indexes, count, sizeof(Word), CompareSpellings);
}

void FindByMeaning(Vocabulary* vocabulary, char(*meaning), Long* (*indexes), Long* count) {
	LinearSearchDuplicate(&vocabulary->words, meaning, indexes, count, sizeof(Word), CompareMeanings);
}

Long Correct(Vocabulary* vocabulary, Long index, char(*wordClass), char(*meaning), char(*example)) {
	Word word;

	//1. 고칠 번호를 입력받는다.
	word = Vocabulary_GetAt(&vocabulary->words, index);
	//2. 입력받은 품사, 의미, 예시를 word에 옮겨적는다.
	strcpy(word.wordClass, wordClass);
	strcpy(word.meaning, meaning);
	strcpy(word.example, example);

	//3. Modify함수를 호출한다.
	index = Modify(&vocabulary->words, index, &word, sizeof(Word));
	return index;
}

Word Vocabulary_GetAt(Vocabulary* vocabulary, Long index) {
	Word word;

	//1. 번호를 입력받는다.
	GetAt(&vocabulary->words, index, &word, sizeof(Word));
	//2. word를 반환한다.
	return word;
}

Long Erase(Vocabulary* vocabulary, Long index) {
	index = Delete(&vocabulary->words, index, sizeof(Word));
	vocabulary->capacity--;
	vocabulary->length--;
	return index;
}

void Arrange(Vocabulary* vocabulary) {
	SelectionSort(&vocabulary->words, sizeof(Word), CompareWords);
}

Long Save(Vocabulary* vocabulary) {
	Word word;
	Long index;
	FILE* file;
	Long i = 0;

	file = fopen("Vocabulary.dat", "wb");
	if (file != NULL) {
		while (i < vocabulary->length) {
			GetAt(&vocabulary->words, i, &word, sizeof(Word));
			fwrite(&word, sizeof(Word), 1, file);
			i++;
		}
		fclose(file);
	}
	return vocabulary->length;
}

void Vocabulary_Destroy(Vocabulary* vocabulary) {
	Destroy(&vocabulary->words);
}

int CompareSpellings(void* one, void* other) {
	Word* one_ = (Word*)one;
	char(*other_) = (char(*))other;
	int ret;
	ret = strcmp(one_->spelling, other_);
	return ret;
}

int CompareMeanings(void* one, void* other) {
	Word* one_ = (Word*)one;
	char(*other_) = (char(*))other;
	int ret;
	ret = strcmp(one_->meaning, other_);
	return ret;
}

int CompareWords(void* one, void* other) {
	Word* one_ = (Word*)one;
	Word* other_ = (Word*)other;
	int ret;
	ret = strcmp(one_->spelling, other_->spelling);
	return ret;
}