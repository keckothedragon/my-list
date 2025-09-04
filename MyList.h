#ifndef MYLIST_H
#define MYLIST_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct MyList {
	void* data;
	size_t size;
	size_t capacity;
	size_t chunk_size;
} MyList;

MyList* MyList_CreateSizeDefault(size_t chunk_size, size_t initial_length, void* default_item);
MyList* MyList_Create(size_t chunk_size) {
	return MyList_CreateSizeDefault(chunk_size, 0, NULL);
}
MyList* MyList_CreateSize(size_t chunk_size, size_t initial_length) {
	return MyList_CreateSizeDefault(chunk_size, initial_length, NULL);
}
void MyList_Destroy(MyList* obj);

void* MyList_Get(MyList* obj, size_t index);
void MyList_Set(MyList* obj, size_t index, void* item);
void MyList_Append(MyList* obj, void* item);
void MyList_Append_List(MyList* obj, MyList* other);

void* MyList_Front(MyList* obj);
void* MyList_Back(MyList* obj);

size_t MyList_Size(MyList* obj);
size_t MyList_Capacity(MyList* obj);


// Uses pointer arithmetic to find the desired location
void* get_pointer(void* original, size_t index, size_t chunk_size) {
	// need to convert to char* bc visual c++ doesn't like pointer arithmetic with void*
	return (char*)original + index * chunk_size;
}

size_t next_power_of_two(size_t value) {
	if (value <= 0) return 1;
	size_t res = 1;
	while (res < value) {
		res <<= 1; // double the value
	}
	return res;
}

void MyList_Reallocate(MyList* obj, size_t new_capacity) {
	new_capacity = next_power_of_two(new_capacity);

	void* new_data = (void*)malloc(obj->chunk_size * new_capacity);
	if (new_data == NULL) {
		printf("Data allocation failed!\n");
		return;
	}

	for (size_t i = 0; i < obj->size; i++) {
		void* old_data_ptr = get_pointer(obj->data, i, obj->chunk_size);
		void* new_data_ptr = get_pointer(new_data, i, obj->chunk_size);
		memcpy(new_data_ptr, old_data_ptr, obj->chunk_size);
	}

	if (obj->data != NULL) {
		free(obj->data);
	}

	obj->data = new_data;
	obj->capacity = new_capacity;
}

MyList* MyList_CreateSizeDefault(size_t chunk_size, size_t initial_length, void* default_item) {
	MyList* obj = (MyList*)malloc(sizeof(MyList));
	if (obj == NULL) {
		printf("Object allocation failed!");
		return NULL;
	}

	obj->size = 0;
	obj->capacity = 0;
	obj->chunk_size = chunk_size;

	// Initialize with initial capacity
	if (initial_length > 0) {
		obj->capacity = next_power_of_two(initial_length);
		obj->data = malloc(obj->chunk_size * obj->capacity);
		if (obj->data == NULL) {
			printf("Data allocation failed!\n");
			free(obj);
			return NULL;
		}

		// If a default item is provided, fill the list with it
		if (default_item != NULL) {
			for (size_t i = 0; i < initial_length; i++) {
				void* ptr = get_pointer(obj->data, i, obj->chunk_size);
				memcpy(ptr, default_item, obj->chunk_size);
			}
		}

		obj->size = initial_length;
	} else {
		obj->data = NULL; // No data allocated yet
	}

	return obj;
}


void MyList_Destroy(MyList* obj) {
	free(obj->data);
	free(obj);
}

void* MyList_Get(MyList* obj, size_t index) {
	if (index < 0 || index > obj->size) {
		printf("Invalid index %zu for size %zu!", index, obj->size);
		return NULL;
	}
	return get_pointer(obj->data, index, obj->chunk_size);
}

void MyList_Set(MyList* obj, size_t index, void* item) {
	if (index < 0 || index > obj->size) {
		printf("Invalid index %zu for size %zu!", index, obj->size);
		return;
	}
	void* curr_ptr = get_pointer(obj->data, index, obj->chunk_size);
	memcpy(curr_ptr, item, obj->chunk_size);
}

void MyList_Append(MyList* obj, void* item) {
	if (obj->size == obj->capacity) {
		MyList_Reallocate(obj, obj->capacity * 2);
	}

	void* curr_ptr = get_pointer(obj->data, obj->size, obj->chunk_size);
	memcpy(curr_ptr, item, obj->chunk_size);
	obj->size++;
}

size_t MyList_Size(MyList* obj) {
	return obj->size;
}

size_t MyList_Capacity(MyList* obj) {
	return obj->capacity;
}

void MyList_Append_List(MyList* obj, MyList* other) {
	if (other->chunk_size != obj->chunk_size) {
		printf("Invalid types for append list! (Must be same chunk size)");
		return;
	}
	for (size_t i = 0; i < MyList_Size(other); i++) {
		MyList_Append(obj, MyList_Get(other, i));
	}
}

void* MyList_Front(MyList* obj) {
	return MyList_Get(obj, 0);
}

void* MyList_Back(MyList* obj) {
	return MyList_Get(obj, obj->size - 1);
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !MYLIST_H
