#ifndef MYLIST_TYPES_H
#define MYLIST_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#include "MyList.h"
#include <stdio.h>
#include <string.h>

// Int List
MyList* IntList_Create() {
	return MyList_Create(sizeof(int));
}

MyList* IntList_CreateSize(size_t initial_length) {
	return MyList_CreateSize(sizeof(int), initial_length);
}

MyList* IntList_CreateSizeDefault(size_t initial_length, int default_item) {
	int* ptr = (int*)malloc(sizeof(int));
	if (ptr == NULL) {
		printf("int allocation failed!\n");
		return NULL;
	}
	*ptr = default_item;
	MyList* obj = MyList_CreateSizeDefault(sizeof(int), initial_length, ptr);

	free(ptr);

	return obj;
}

int IntList_Get(MyList* obj, size_t index) {
	return *(int*)MyList_Get(obj, index);
}

void IntList_Set(MyList* obj, size_t index, int item) {
	int* ptr = (int*)malloc(sizeof(int));
	if (ptr == NULL) {
		printf("int allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Set(obj, index, ptr);

	free(ptr);
}

void IntList_Append(MyList* obj, int item) {
	int* ptr = (int*)malloc(sizeof(int));
	if (ptr == NULL) {
		printf("int allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Append(obj, ptr);

	free(ptr);
}

int IntList_Front(MyList* obj) {
	return *(int*)MyList_Front(obj);
}

int IntList_Back(MyList* obj) {
	return *(int*)MyList_Back(obj);
}

void IntList_Print(MyList* obj) {
	const char* FORMAT = "%d";
	printf("[");
	for (int i = 0; i < MyList_Size(obj) - 1; i++) {
		printf(FORMAT, IntList_Get(obj, i));
		printf(", ");
	}
	printf(FORMAT, IntList_Back(obj));
	printf("]\n");
}

// Double list
MyList* DoubleList_Create() {
	return MyList_Create(sizeof(double));
}

MyList* DoubleList_CreateSize(size_t initial_length) {
	return MyList_CreateSize(sizeof(double), initial_length);
}

MyList* DoubleList_CreateSizeDefault(size_t initial_length, double default_item) {
	double* ptr = (double*)malloc(sizeof(double));
	if (ptr == NULL) {
		printf("double allocation failed!\n");
		return NULL;
	}
	*ptr = default_item;
	MyList* obj = MyList_CreateSizeDefault(sizeof(double), initial_length, ptr);

	free(ptr);

	return obj;
}

double DoubleList_Get(MyList* obj, double index) {
	return *(double*)MyList_Get(obj, index);
}

void DoubleList_Set(MyList* obj, size_t index, double item) {
	double* ptr = (double*)malloc(sizeof(double));
	if (ptr == NULL) {
		printf("double allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Set(obj, index, ptr);

	free(ptr);
}

void DoubleList_Append(MyList* obj, double item) {
	double* ptr = (double*)malloc(sizeof(double));
	if (ptr == NULL) {
		printf("double allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Append(obj, ptr);

	free(ptr);
}

double DoubleList_Front(MyList* obj) {
	return *(double*)MyList_Front(obj);
}

double DoubleList_Back(MyList* obj) {
	return *(double*)MyList_Back(obj);
}

void DoubleList_Print(MyList* obj) {
	const char* FORMAT = "%f";
	printf("[");
	for (int i = 0; i < MyList_Size(obj) - 1; i++) {
		printf(FORMAT, DoubleList_Get(obj, i));
		printf(", ");
	}
	printf(FORMAT, DoubleList_Back(obj));
	printf("]\n");
}

// Float list
MyList* FloatList_Create() {
	return MyList_Create(sizeof(float));
}

MyList* FloatList_CreateSize(size_t initial_length) {
	return MyList_CreateSize(sizeof(float), initial_length);
}

MyList* FloatList_CreateSizeDefault(size_t initial_length, float default_item) {
	float* ptr = (float*)malloc(sizeof(float));
	if (ptr == NULL) {
		printf("float allocation failed!\n");
		return NULL;
	}
	*ptr = default_item;
	MyList* obj = MyList_CreateSizeDefault(sizeof(float), initial_length, ptr);

	free(ptr);

	return obj;
}

float FloatList_Get(MyList* obj, float index) {
	return *(float*)MyList_Get(obj, index);
}

void FloatList_Set(MyList* obj, size_t index, float item) {
	float* ptr = (float*)malloc(sizeof(float));
	if (ptr == NULL) {
		printf("float allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Set(obj, index, ptr);

	free(ptr);
}

void FloatList_Append(MyList* obj, float item) {
	float* ptr = (float*)malloc(sizeof(float));
	if (ptr == NULL) {
		printf("float allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Append(obj, ptr);

	free(ptr);
}

float FloatList_Front(MyList* obj) {
	return *(float*)MyList_Front(obj);
}

float FloatList_Back(MyList* obj) {
	return *(float*)MyList_Back(obj);
}

void FloatList_Print(MyList* obj) {
	const char* FORMAT = "%f";
	printf("[");
	for (int i = 0; i < MyList_Size(obj) - 1; i++) {
		printf(FORMAT, FloatList_Get(obj, i));
		printf(", ");
	}
	printf(FORMAT, FloatList_Back(obj));
	printf("]\n");
}

// Char list
MyList* CharList_Create() {
	return MyList_Create(sizeof(char));
}

MyList* CharList_CreateSize(size_t initial_length) {
	return MyList_CreateSize(sizeof(char), initial_length);
}

MyList* CharList_CreateSizeDefault(size_t initial_length, char default_item) {
	char* ptr = (char*)malloc(sizeof(char));
	if (ptr == NULL) {
		printf("char allocation failed!\n");
		return NULL;
	}
	*ptr = default_item;
	MyList* obj = MyList_CreateSizeDefault(sizeof(char), initial_length, ptr);

	free(ptr);

	return obj;
}

char CharList_Get(MyList* obj, char index) {
	return *(char*)MyList_Get(obj, index);
}

void CharList_Set(MyList* obj, size_t index, char item) {
	char* ptr = (char*)malloc(sizeof(char));
	if (ptr == NULL) {
		printf("char allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Set(obj, index, ptr);

	free(ptr);
}

void CharList_Append(MyList* obj, char item) {
	char* ptr = (char*)malloc(sizeof(char));
	if (ptr == NULL) {
		printf("char allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Append(obj, ptr);

	free(ptr);
}

char CharList_Front(MyList* obj) {
	return *(char*)MyList_Front(obj);
}

char CharList_Back(MyList* obj) {
	return *(char*)MyList_Back(obj);
}

void CharList_Print(MyList* obj) {
	const char* FORMAT = "%c";
	printf("[");
	for (int i = 0; i < MyList_Size(obj) - 1; i++) {
		printf(FORMAT, CharList_Get(obj, i));
		printf(", ");
	}
	printf(FORMAT, CharList_Back(obj));
	printf("]\n");
}

// String list
MyList* StringList_Create() {
	return MyList_Create(sizeof(char*));
}

MyList* StringList_CreateSize(size_t initial_length) {
	return MyList_CreateSize(sizeof(char*), initial_length);
}

MyList* StringList_CreateSizeDefault(size_t initial_length, char* default_item) {
	char** ptr = (char**)malloc(sizeof(char*));
	if (ptr == NULL) {
		printf("char* allocation failed!\n");
		return NULL;
	}
	*ptr = default_item;
	MyList* obj = MyList_CreateSizeDefault(sizeof(char*), initial_length, ptr);

	free(ptr);

	return obj;
}

char* StringList_Get(MyList* obj, char* index) {
	return *(char**)MyList_Get(obj, index);
}

void StringList_Set(MyList* obj, size_t index, char* item) {
	char** ptr = (char**)malloc(sizeof(char*));
	if (ptr == NULL) {
		printf("char* allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Set(obj, index, ptr);

	free(ptr);
}

void StringList_Append(MyList* obj, char* item) {
	char** ptr = (char**)malloc(sizeof(char*));
	if (ptr == NULL) {
		printf("char* allocation failed!\n");
		return;
	}
	*ptr = item;
	MyList_Append(obj, ptr);

	free(ptr);
}

char* StringList_Front(MyList* obj) {
	return *(char**)MyList_Front(obj);
}

char* StringList_Back(MyList* obj) {
	return *(char**)MyList_Back(obj);
}

void StringList_Print(MyList* obj) {
	const char* FORMAT = "%s";
	printf("[");
	for (int i = 0; i < MyList_Size(obj) - 1; i++) {
		printf(FORMAT, StringList_Get(obj, i));
		printf(", ");
	}
	printf(FORMAT, StringList_Back(obj));
	printf("]\n");
}

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // !MYLIST_TYPES_H

