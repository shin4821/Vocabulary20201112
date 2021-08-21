//Vocabulary.h
#ifndef _VOCABULARY_H
#define _VOCABULARY_H
#include"array.h"

typedef struct _word {
    char spelling[32];
    char wordClass[12];
    char meaning[32];
    char example[64];
}Word;

typedef struct _vocabulary {
    Array words;
    Long capacity;
    Long length;
}Vocabulary;

void Vocabulary_Create(Vocabulary* vocabulary, Long capacity);
Long Load(Vocabulary* vocabulary);
Long Record(Vocabulary* vocabulary, char(*spelling), char(*wordClass), char(*meaning), char(*example));
void FindBySpelling(Vocabulary* vocabulary, char(*spelling), Long* (*indexes), Long* count);
void FindByMeaning(Vocabulary* vocabulary, char(*meaning), Long* (*indexes), Long* count);
Long Correct(Vocabulary* vocabulary, Long index, char(*wordClass), char(*meaning), char(*example));
Word Vocabulary_GetAt(Vocabulary* vocabulary, Long index);
Long Erase(Vocabulary* vocabulary, Long index);
void Arrange(Vocabulary* vocabulary);
Long Save(Vocabulary* vocabulary);
void Vocabulary_Destroy(Vocabulary* vocabulary);
int CompareSpellings(void* one, void* other);
int CompareMeanings(void* one, void* other);
int CompareWords(void* one, void* other);

#endif//_VOCABULARY_H