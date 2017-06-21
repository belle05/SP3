#include "SPArrayList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

SPArrayList* spArrayListCreate(int maxSize){
	SPArrayList *newArray;
	if(maxSize <= 0){
		return NULL;
	}
	newArray = (SPArrayList*)malloc(sizeof(SPArrayList));
	if (newArray == NULL) {
		printf("Error: spArrayListCreate has failed\n");
		return NULL;
	}
	newArray -> maxSize = maxSize;
	for (int i=0; i < maxSize; i++){
                newArray -> elements[i] = 9;
        }

	newArray -> actualSize = 0;
	return newArray;
}


/**
 *      Creates an exact copy of the src array list. Elements in the new copy will
 *      be in the same order as they appeared in the source list.
 *      @param src - the source array list.
 *      @return
 *      NULL if either an allocation error occurs or src == NULL.
 *      A new copy of the source array list, otherwise.
 */
SPArrayList* spArrayListCopy(SPArrayList* src) {
	SPArrayList *newArray;
	newArray = (SPArrayList*)malloc(sizeof(SPArrayList));
        if (newArray == NULL) {
                return NULL;
        }
        newArray -> actualSize = src -> actualSize;
        newArray -> maxSize = src -> maxSize;
	for (int i=0; i < src -> maxSize; i++){
                newArray -> elements[i] = src -> elements[i];
        }
        return newArray;
}
 

/**
 * Frees all memory resources associated with the source array list. If the
 * source array is NULL, then the function does nothing.
 * @param src - the source array list
 */
void spArrayListDestroy(SPArrayList* src) {
	if (src != NULL) {
		free(src);
	}
}
/**
 * Clears all elements from the source array list. After invoking this function,
 * the size of the source list will be reduced to zero and maximum capacity is
 * not affected.
 * @param src - the source array list
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT if src == NULL
 * SP_ARRAY_LIST_SUCCESS otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src) {
	if (src == NULL) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}
	for (int i=0; i < src -> maxSize; i++){
                src -> elements[i] = 9;
        }
	src -> actualSize = 0;
	return SP_ARRAY_LIST_SUCCESS;
}


/**
 * Inserts element at a specified index. The elements residing at and after the
 * specified index will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @param index - the index where the new element will be placed. The index is
 *                0-based.
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index){
	if (src == NULL) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}
	if (src -> actualSize == src -> maxSize) {
		return SP_ARRAY_LIST_FULL;
	}

	int arrSize = src -> actualSize;
	for (int i = arrSize ; i > index; i--) {
		src -> elements[i] = src -> elements[i-1];
	}
	src -> elements[index] = elem;
	src -> actualSize = arrSize + 1;
	return SP_ARRAY_LIST_SUCCESS;
}
           
/**
 * Inserts element at a the beginning of the source element. The elements
 * will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem) {
	if (src == NULL) {
		//TODO: add check to index is out of bound
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (src -> actualSize == src -> maxSize) {
		return SP_ARRAY_LIST_FULL;
	}
	spArrayListAddAt(src, elem, 0);
	return SP_ARRAY_LIST_SUCCESS;
}
/**
 * Inserts element at a the end of the source element. If the array list
 * reached its maximum capacity and error message is returned and the source
 * list is not affected.
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem) {
	 if (src == NULL) {
                return SP_ARRAY_LIST_INVALID_ARGUMENT;
        }
        if (src -> actualSize == src -> maxSize) {
                return SP_ARRAY_LIST_FULL;
        }

	spArrayListAddAt(src, elem, src -> actualSize);
//	src -> elements[src -> actualSize] = elem;
	return SP_ARRAY_LIST_SUCCESS;
}
/**
 * Removes an element from a specified index. The elements residing after the
 * specified index will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @param index - The index from where the new element will be removed.
 *                The index is 0-based.
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index) {
/* check if we need to check the index */
	if (src == NULL) {
                return SP_ARRAY_LIST_INVALID_ARGUMENT;
        }
        if (src -> actualSize == 0) {
                return SP_ARRAY_LIST_EMPTY;
        }
	int arrSize = src -> actualSize;
	for (int i = index; i < arrSize; i++) {
		if (i == arrSize -1) {
			src -> elements[i] = 9;
		}
		else {
			src -> elements[i] = src -> elements[i+1];
		}
	}
	src -> actualSize = arrSize - 1;
	return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Removes an element from a the beginning of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src) {
	if (src == NULL) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (src -> actualSize == 0) {
		return SP_ARRAY_LIST_EMPTY;
	}
	spArrayListRemoveAt(src, 0);
	return SP_ARRAY_LIST_SUCCESS;
}
/**
 * Removes an element from a the end of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise.
 */
SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src) {
	if (src == NULL) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (src -> actualSize == 0) {
		return SP_ARRAY_LIST_EMPTY;
	}
	spArrayListRemoveAt(src, src -> actualSize-1);
	return SP_ARRAY_LIST_SUCCESS;
}
/**
 * Returns the element at the specified index. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @param index - the specified index, the index is 0-based.
 * @return
 * Undefined value if either src == NULL or index out of bound.
 * Otherwise, the element at the specified index is returned.
 */
int spArrayListGetAt(SPArrayList* src, int index) {
/* TODO: what is undefined?*/
	if (src == NULL) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}
	if (index >= src -> actualSize) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}
	return src -> elements[index];
}

/**
 * Returns the element at the beginning of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
 */
int spArrayListGetFirst(SPArrayList* src) {
/* TODO: what is undefined?*/
	if (src == NULL) {
		return '\0';
	}
	return spArrayListGetAt(src, 0);
}

/**
 * Returns the element at the end of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the end of the list is returned.
 */
int spArrayListGetLast(SPArrayList* src) {
/* TODO: what is undefined?*/
	if ((src == NULL) || (src -> actualSize == 0)) {
		return '\0';
	}
	return spArrayListGetAt(src, (src -> actualSize)-1);
}

/**
 * Returns the maximum capacity of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the maximum capacity of the list is returned.
 */
int spArrayListMaxCapacity(SPArrayList* src) {
	int undefined = 0;
        if (src == NULL) {
                return undefined;
        }
	return src -> maxSize;
}
/**
 * Returns the number of elements in the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the number of the elements in the list is returned.
 */
int spArrayListSize(SPArrayList* src) {
	int undefined = 0;
        if (src == NULL) {
                return undefined;
        }
        return src -> actualSize;
}


/**
 * Returns true if the list is full, that is the number of elements in the list
 * equals its maximum capacity.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is less
 * than its maximum capacity.
 * Otherwise, true is returned.
 */
bool spArrayListIsFull(SPArrayList* src) {
	if (src == NULL) {
                return false;
        }
	if ((src -> actualSize) == (src -> maxSize)) {
		return true;
	}
	return false;
}
/**
 * Returns true if the list is empty, that is the number of elements in the list
 * equals to zero.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is not zero.
 * Otherwise, true is returned.
 */
bool spArrayListIsEmpty(SPArrayList* src) {
	if (src == NULL) {
                return false;
        }
        if ((src -> actualSize) == 0) {
                return true;
        }
        return false;
}


