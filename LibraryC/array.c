#include <stdlib.h>
#include "array.h"

typedef struct Array
{
	size_t size;
	Data* array;
	FFree* deleter;
} Array;

// create array
Array* array_create(size_t size, FFree f)
{
	if (size > 0) {
		Array* newarray = (Array*)malloc(sizeof(Array));
		newarray->size = size;
		newarray->array = (Data*)malloc(sizeof(Data) * size);
		newarray->deleter = f;
		return newarray;
	}
	return NULL;
}

// delete array, free memory
void array_delete(Array* arr)
{
	if (arr != NULL) {
		if (arr->deleter != NULL)
			for (size_t i = 0; i < arr->size;i++) {
				arr->deleter(arr->array[i]);
			}
		else
			for (size_t i = 0; i < arr->size;i++) {
				free(arr->array[i]);
			}
		free(arr->array);
		free(arr);
	}
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
	if ((arr != NULL) && (index < arr->size))
		return arr->array[index];
	return (Data)0;
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
	if ((arr != NULL) && (index < arr->size))
		arr->array[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
	if (arr != NULL)
		return arr->size;
	return 0;
}
