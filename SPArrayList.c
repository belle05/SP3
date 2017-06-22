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

void spArrayListDestroy(SPArrayList* src) {
	if (src != NULL) {
		free(src);
	}
}

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

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem) {
	if (src == NULL) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (src -> actualSize == src -> maxSize) {
		return SP_ARRAY_LIST_FULL;
	}
	spArrayListAddAt(src, elem, 0);
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem) {
	 if (src == NULL) {
                return SP_ARRAY_LIST_INVALID_ARGUMENT;
        }
        if (src -> actualSize == src -> maxSize) {
                return SP_ARRAY_LIST_FULL;
        }

	spArrayListAddAt(src, elem, src -> actualSize);
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index) {
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

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src) {
	if (src == NULL) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (src -> actualSize == 0) {
		return SP_ARRAY_LIST_EMPTY;
	}
	spArrayListRemoveAt(src, 0);
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src) {
	if (src == NULL) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	} else if (src -> actualSize == 0) {
		return SP_ARRAY_LIST_EMPTY;
	}
	spArrayListRemoveAt(src, src -> actualSize-1);
	return SP_ARRAY_LIST_SUCCESS;
}

int spArrayListGetAt(SPArrayList* src, int index) {
	if (src == NULL) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}
	if (index >= src -> actualSize) {
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}
	return src -> elements[index];
}

int spArrayListGetFirst(SPArrayList* src) {
	if (src == NULL) {
		return '\0';
	}
	return spArrayListGetAt(src, 0);
}


int spArrayListGetLast(SPArrayList* src) {
	if ((src == NULL) || (src -> actualSize == 0)) {
		return '\0';
	}
	return spArrayListGetAt(src, (src -> actualSize)-1);
}

int spArrayListMaxCapacity(SPArrayList* src) {
	int undefined = 0;
        if (src == NULL) {
                return undefined;
        }
	return src -> maxSize;
}

int spArrayListSize(SPArrayList* src) {
	int undefined = 0;
        if (src == NULL) {
                return undefined;
        }
        return src -> actualSize;
}

bool spArrayListIsFull(SPArrayList* src) {
	if (src == NULL) {
                return false;
        }
	if ((src -> actualSize) == (src -> maxSize)) {
		return true;
	}
	return false;
}

bool spArrayListIsEmpty(SPArrayList* src) {
	if (src == NULL) {
                return false;
        }
        if ((src -> actualSize) == 0) {
                return true;
        }
        return false;
}


