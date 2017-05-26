#ifndef SPARRAYLIST_H_
#define SPARRAYLIST_H_
#include <stdbool.h>

SPArrayList* spArrayListCreate(int maxSize){
	SPArrayList *my_array_list;
	if(maxSize<=0){
		return NULL;
	}

	int elements[maxSize];
	int actualSize=0;
	for (unsigned int i=0; i<maxSize; i++){
		elements[i] = '\0';
	}
	my_array_list = (SPArrayList*)malloc(sizeof(my_array_list));
	if (my_array_list == NULL) {
		return NULL;
	}
	my_array_list -> elements = elements;
	my_array_list -> actualSize = actualSize;
	my_array_list -> maxSize = maxSize;
	return my_array_list;
}

