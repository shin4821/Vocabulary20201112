//array.c
#include"array.h"
#include<memory.h>
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

void Create(Array* array, Long capacity, size_t size) {

	//1. capacity�� �Է¹޴´�.
	//2. array�� capacity��ŭ �迭�� �Ҵ��Ѵ�.
	array->front = calloc(capacity, size);
	//3. array.capacity�� capacity�� ���´�.
	array->capacity = capacity;
	//4. length�� �ʱ�ȭ�Ѵ�.
	array->length = 0;
	//5. ������.
}

Long Store(Array* array, Long index, void* object, size_t size) {
	//1. index, object�� �Է¹޴´�.
	//2. array.front�迭�� index��°�� object�� ���´�.
	memcpy(((char*)array->front) + (index * size), object, size);
	//3. length�� 1�� ������Ų��.
	array->length++;
	//4. index�� ����Ѵ�.
	return index;
	//5. ������.
}

Long Insert(Array* array, Long index, void* object, size_t size) {
	void(*temps);
	Long i = 0;
	Long j = 0;

	//1. index, object�� �Է¹޴´�.
	//2. temps�� capacity+1��ŭ �迭�� �Ҵ��Ѵ�.
	temps = calloc(array->capacity + 1, size);
	//3. array.front�� ���� index��°�� �����ϰ� temps�� �Ű����´�.
	while (i < index) {
		memcpy(((char*)temps) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	j++;
	while (i < array->length) {
		memcpy(((char*)temps) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	//4. array.front �迭�� �Ҵ������Ѵ�.
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	(char(*))array->front = (char(*))temps;
	//5. capacity�� 1�� ������Ų��.
	array->capacity++;
	//6. index��°�� object�� �����.
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	//7. index�� ����Ѵ�.
	return index;
}

Long AppendForFront(Array* array, void* object, size_t size) {
	Long index = 0;
	void(*temps);
	Long i = 0;
	Long j = 1;

	//1. object�� �Է¹޴´�.
	//2. temps�� capacity+1��ŭ �迭�� �Ҵ��Ѵ�.
	temps = calloc(array->capacity + 1, size);
	//3. array.front�� temps�� �ι�°���� �Ű����´�.
	while (i < array->length) {
		memcpy(((char*)temps) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	//4. array.front�迭�� �Ҵ������Ѵ�.
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	(char(*))array->front = (char(*))temps;
	//5. capacity�� 1�� ������Ų��.
	array->capacity++;
	//6. array.front�� index��°�� object�� ���´�.
	memcpy(((char*)array->front) + (index * size), object, size);
	//7. length�� 1�� ������Ų��.
	array->length++;
	//8. index�� ����Ѵ�.
	return index;
	//9. ������.
}

Long AppendForRear(Array* array, void* object, size_t size) {
	Long index;
	void(*temps);
	Long i = 0;

	//1. object�� �Է¹޴´�.
	//2. temps�� capacity+1��ŭ �迭�� �Ҵ��Ѵ�.
	temps = calloc(array->capacity + 1, size);
	//3. array.front�� temps�� ù��°���� �Ű� ���´�.
	while (i < array->length) {
		memcpy(((char*)temps) + (i * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	//4. array.front�迭�� �Ҵ������Ѵ�.
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	(char(*))array->front = (char(*))temps;
	//5. capacity�� 1�� ������Ų��.
	array->capacity++;
	//6. array.front�� index��°�� object�� ���´�.
	index = array->capacity - 1;
	memcpy(((char*)array->front) + (index * size), object, size);
	//7. length�� 1�� ������Ų��.
	array->length++;
	//8. index�� ����Ѵ�.
	return index;
	//9. ������.
}

Long Delete(Array* array, Long index, size_t size) {
	void(*temps) = NULL;
	Long i = 0;
	Long j = 0;

	//1. index�� �д´�.
	//2. capacity�� 1���� Ŭ ���,
	if (array->capacity > 1) {
		//2.1 temps�� capacity-1��ŭ �迭�� �Ҵ��Ѵ�.
		temps = calloc(array->capacity - 1, size);
	}
	//3. array.front�� ���� index���� �����ϰ� temps�� �Ű� ���´�.
	while (i < index) {
		memcpy(((char*)temps) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	i = index + 1;
	while (i < array->length) {
		memcpy(((char*)temps) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	//4. array.front�� �Ҵ������Ѵ�.
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		(char(*))array->front = (char(*))temps;
	}
	array->capacity--;
	array->length--;
	index = -1;
	return index;
}

Long DeleteForFront(Array* array, size_t size) {
	Long index;
	void(*temps)=NULL;
	Long i = 1;
	Long j = 0;

	//1. capacity�� 1���� Ŭ ���,
	if (array->capacity > 1) {
		//1.1 temps�� capacity-1��ŭ �迭�� �Ҵ��Ѵ�.
		temps = calloc(array->capacity - 1, size);
	}
	//2. array.front�� �ι�°���� temps�� �Ű����´�.
	while (i < array->length) {
		memcpy(((char*)temps) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	//3. array.front�� �Ҵ������Ѵ�.
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		(char(*))array->front = (char(*))temps;
	}
	//4. capacity�� 1�� ����.
	array->capacity--;
	//5. length�� 1�� ����.
	array->length--;
	//6. index�� 0�� ���´�.
	index = -1;
	return index;
	//7. ������.
}

Long DeleteForRear(Array* array, size_t size) {
	Long index;
	void(*temps) = NULL;
	Long i = 0;

	//1. capacity�� 1���� Ŭ ���,
	if (array->capacity > 1) {
		//1.1 temps�� capacity-1��ŭ �迭�� �Ҵ��Ѵ�.
		temps = calloc(array->capacity - 1, size);
	}
	//2. length-1��ŭ array.front�� temps�� �Ű����´�.
	while (i < array->capacity - 1) {
		memcpy(((char*)temps) + (i * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	//3. array.front�迭�� �Ҵ������Ѵ�.
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	if (array->capacity > 1) {
		(char(*))array->front = (char(*))temps;
	}
	//4. capacity�� 1�� ���ҽ�Ų��.
	array->capacity--;
	//5. length�� 1�� ���ҽ�Ų��.
	array->length--;
	//6. index�� 0�� ���´�,
	index = -1;
	//7. index�� ����Ѵ�.
	return index;
	//8. ������.
}

void Clear(Array* array) {
	//1. array.front�� �Ҵ������Ѵ�.
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	//2. capacity�� 0���� ����ġ�Ѵ�.
	array->capacity = 0;
	//3. length�� 0���� ����ġ�Ѵ�.
	array->length = 0;

}

Long Modify(Array* array, Long index, void* object, size_t size) {
	//1. index, object�� �Է¹޴´�.
	//2. array.front�� index��°�� object�� ���´�.
	memcpy(((char*)array->front) + (index * size), object, size);
	//3. index�� ����Ѵ�.
	return index;
}

Long LinearSearchUnique(Array* array, void* key, size_t size, int (*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;

	//1. key���� �Է¹޴´�.
	//2. array.length���� �۰ų� ���� array.front�� key�� �ƴѵ��� �ݺ��Ѵ�.
	while (i < array->length && compare(((char*)array->front) + (i * size), key) != 0) {
		i++;
	}
	//3. array.length���� ���� ���,
	if (i < array->length) {
		//3.1 index�� i�� ���´�.
		index = i;
	}
	return index;
}

void LinearSearchDuplicate(Array* array, void* key, Long* (*indexes), Long* count, size_t size,
	int(*compare)(void*, void*)) {

	Long i = 0;
	Long j = 0;
	*count = 0;

	//1. key���� �Է¹޴´�.
	//2. indexes�� length��ŭ �迭�� �Ҵ��Ѵ�.
	*indexes = (Long(*))calloc(array->length, size);
	//3. length��ŭ �ݺ��Ѵ�.
	while (i < array->length) {
		if (compare(((char*)array->front) + (i * size), key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
	//4. indexes�� count�� ����Ѵ�.
	//5. ������.
}

Long BinarySearchUnique(Array* array, void* key, size_t size, int(*compare)(void*, void*)) {
	Long index = -1;
	Long high;
	Long low = 0;
	Long middle;

	//1. key���� �Է¹޴´�.
	//2. low�� high���� ���ų� ����, array.front���� key�� �ƴѵ��� �ݺ��Ѵ�.
	high = array->length - 1;
	middle = (low + high) / 2;
	while (low <= high && compare(((char*)array->front)+(middle*size),key)!= 0) {
		if (compare(((char*)array->front)+(middle*size),key) < 0) {
			low = middle + 1;
		}
		else {
			high = middle - 1;
		}
		middle = (low + high) / 2;
	}
	//3. low�� high���� �۰ų� ���� ���,
	if (low <= high) {
		//3.1 middle�� index�̴�.
		index = middle;
	}
	//4. index�� ����Ѵ�.
	return index;
}

void BinarySearchDuplicate(Array* array, void* key, Long* count, Long* (*indexes), size_t size,
	int(*compare)(void*, void*)) {

	Long low = 0;
	Long high;
	Long middle;
	Long i;
	Long j = 0;
	*count = 0;

	//1. key���� �Է¹޴´�.
	high = array->length - 1;
	//2. indexes�� length��ŭ �迭�� �Ҵ��Ѵ�.
	*indexes = (Long(*))calloc(array->length, size);
	middle = (low + high) / 2;
	//3. low�� high���� �۰ų� ���� array.front���� key�� �ƴҵ��� �ݺ��Ѵ�.
	while (low <= high && compare(((char*)array->front) + (middle * size), key) != 0) {
		if (compare(((char*)array->front) + (middle * size), key) < 0) {
			low = middle + 1;
		}
		else {
			high = middle - 1;
		}
		middle = (low + high) / 2;
	}
	i = middle - 1;
	//4. middle���Ͽ� key���� �ִ��� ã�´�.
	while (i >= 0 && compare(((char*)array->front) + (i * size), key) == 0) {
		i--;
	}
	i++;
	//5. length���� ���ų� ���� array.front�� key���� �ִ��� Ȯ���Ѵ�.
	while (i < array->length && compare(((char*)array->front)+(i*size),key ) == 0) {
		(*indexes)[j] = i;
		j++;
		(*count)++;
		i++;
	}
	//6. indexes�� count�� ����Ѵ�.
	//7. ������.
}

void SelectionSort(Array* array, size_t size, int(*compare)(void*, void*)) {
	void* temp;
	Long i = 0;
	Long j;
	Long index;
	
	//1. length-1��ŭ �ݺ��Ѵ�.
	temp= malloc(size);
	while (i < array->length - 1) {
		index = i;
		j = i + 1;
		//1.1 length��ŭ �ݺ��Ѵ�.
		while (j < array->length) {
			if (compare(((char*)array->front) + (j * size), ((char*)array->front) + (index * size)) < 0) {
				index = j;
			}
			j++;
		}
		//1.1.1.1 ù��° ���� �� Ŭ ���, temp�� ���´�.
		memcpy(temp, ((char*)array->front) + (index * size), size);
		//1.1.1.2 �ι�° ���� ù��° ��ġ�� ���´�.
		memcpy(((char*)array->front) + (index * size), ((char*)array->front) + (i * size), size);
		//1.1.1.3 temp�� �ι�° ��ġ�� ���´�.
		memcpy(((char*)array->front) + (i * size), temp, size);
		i++;
	}
	if (temp != NULL) {
		free(temp);
		temp = NULL;
	}
	//2. ������.
}

void BubbleSort(Array* array, size_t size, int(*compare)(void*, void*)) {
	Boolean temp = FALSE_;
	void* tempFront;
	Long i = 0;
	Long j;

	//1. length-1���� �۰ų� temp�� TRUE�� �ƴѵ��� �ݺ��Ѵ�.
	tempFront = malloc(size);
	while (i < array->length - 1 && temp != TRUE_) {
		temp = TRUE_;
		j = 0;
		//1.1 array.length-i��ŭ �ݺ��Ѵ�.
		while (j < array->length - i-1) {
			if (compare(((char*)array->front) + (j * size), ((char*)array->front) + ((j + 1) * size)) > 0) {
				memcpy(tempFront, ((char*)array->front) + (j * size), size);
				memcpy(((char*)array->front)+(j*size), ((char*)array->front)+((j+1)*size), size);
				memcpy(((char*)array->front) + ((j + 1) * size), tempFront, size);
				temp = FALSE_;
			}
			j++;
		}
		i++;
	}
	if (tempFront != NULL) {
		free(tempFront);
		tempFront = NULL;
	}
	//2. ������.
}

void InsertSort(Array* array, size_t size, int(*compare)(void*, void*)) {
	void* temp;
	Long i = 1;
	Long j;

	//1. length��ŭ �ݺ��Ѵ�.
	temp = malloc(size);
	while (i < array->length) {
		memcpy(temp, ((char*)array->front) + (i * size), size);
		j = i - 1;
		//1.1 j���� ũ�ų� ���� temp�� array.front���� �������� �ݺ��Ѵ�.
		while (j >= 0 && compare(temp, ((char*)array->front) + (j * size)) < 0) {
			memcpy(((char*)array->front) + ((j + 1) * size), ((char*)array->front) + (j * size), size);
			j--;
		}
		memcpy(((char*)array->front) + ((j + 1) * size), temp, size);
		i++;
	}
	if (temp != NULL) {
		free(temp);
		temp = NULL;
	}
	//2. ������.
}

void Merge(Array* array, Array* one, Array* other, size_t size, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;

	//1. one�迭, other�迭�� �Է¹޴´�.
	//2. array.front�� �Ҵ������Ѵ�.
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	//3. one.length�� other.length�� �ո�ŭ array�� �迭�� �Ҵ��Ѵ�.
	array->front = calloc(one->length + other->length, size);
	array->capacity = one->length + other->length;
	array->length = 0;
	//4. one.length���� ���ų� �۰� other.length���� ���ų� ���� ���� �ݺ��Ѵ�.
	while (i < one->length && j < other->length) {
		if (compare(((char*)one->front)+(i*size), ((char*)other->front)+(j*size)) < 0) {
			memcpy(((char*)array->front) + (k * size), ((char*)one->front) + (i * size), size);
			array->length++;
			k++;
			i++;
		}
		else {
			memcpy(((char*)array->front) + (k * size), ((char*)other->front) + (j * size), size);
			array->length++;
			k++;
			j++;
		}
	}
	//5. one.length���� ���ų� ������ front������.
	while (i < one->length) {
		memcpy(((char*)array->front) + (k * size), ((char*)one->front) + (i * size), size);
		array->length++;
		k++;
		i++;
	}
	//6. other.length���� ���ų� ������ front�� ����.
	while (j < other->length) {
		memcpy(((char*)array->front) + (k * size), ((char*)other->front) + (j * size), size);
		array->length++;
		k++;
		j++;
	}
	//7. ������.
}

void GetAt(Array* array, Long index, void *object, size_t size) {

	//1. index�� �Է¹޴´�.
	//2. array.front�� index��° ���� object�� ���´�.
	memcpy(object, ((char*)array->front) + (index * size), size);
	//3. object�� ����Ѵ�.
	//4. ������.
}

void Destroy(Array* array) {
	//1. array, front�� �Ҵ������Ѵ�.
	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	//2. ������.
}
