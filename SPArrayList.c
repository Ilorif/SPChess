/*
 * SPArrayList.c
 *
 *  Created on: Aug 16, 2017
 *      Author: adi
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "SPArrayList.h"


SPArrayList* spArrayListCreate() {
	SPArrayList* list = (SPArrayList*) malloc(sizeof(SPArrayList));
	if (list == NULL ) {
		printf(ERROR_FUNC,"malloc");
		return NULL ;
	}
	spArrayListClear(list);
	return list;
}

SPArrayList* spArrayListCopy(SPArrayList* src) {
	if (src == NULL ) return NULL ;
	SPArrayList* copy = spArrayListCreate();
	if (copy == NULL ) {
		printf(ERROR_FUNC,"malloc");
		return NULL ;
	}
	copy->actualSize = src->actualSize;
	for (int i=0; i<SP_LIST_WIDTH; i++) {
		for (int j=0; j<SP_LIST_LENGTH; j++) {
			copy->positions[i][j] = src->positions[i][j];
		}
	}
	for (int j=0; j<SP_LIST_LENGTH; j++) {
		copy->element[j] = src->element[j];
	}
	return copy;
}

void spArrayListDestroy(SPArrayList* src) {
	if (src==NULL) return;
	free(src);
	return;
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src) {
	if (src == NULL ) return SP_ARRAY_LIST_INVALID_ARGUMENT;
	src->actualSize = 0;
	for (int i=0; i<SP_LIST_WIDTH; i++) {
		for (int j=0; j<SP_LIST_LENGTH; j++) {
			src->positions[i][j] = -1;
		}
	}
	for (int j=0; j<SP_LIST_LENGTH; j++) {
		src->element[j] = SP_LIST_EMPTY;
	}
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int index, char elem, int oldRow, int oldCol, int newRow, int newCol) {
	if (src == NULL || index < 0 || index > src->actualSize)
			return SP_ARRAY_LIST_INVALID_ARGUMENT;
	else if (spArrayListIsFull(src))
		return SP_ARRAY_LIST_FULL;
	else if (index == src->actualSize) {
		src->positions[0][index] = oldRow;
		src->positions[1][index] = oldCol;
		src->positions[2][index] = newRow;
		src->positions[3][index] = newCol;
		src->element[index] = elem;
	}
	else {
		for(int i=src->actualSize; i>index; i--) {
			for (int j=0; j<SP_LIST_WIDTH; j++) src->positions[j][i] = src->positions[j][i-1];
			src->element[i] = src->element[i-1];
		}
		src->positions[0][index] = oldRow;
		src->positions[1][index] = oldCol;
		src->positions[2][index] = newRow;
		src->positions[3][index] = newCol;
		src->element[index] = elem;
	}
	src->actualSize++;
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, char elem, int oldRow, int oldCol, int newRow, int newCol) {
	if (src == NULL) return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return spArrayListAddAt(src, 0, elem, oldRow, oldCol, newRow, newCol);
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, char elem, int oldRow, int oldCol, int newRow, int newCol) {
	if (src == NULL) return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return spArrayListAddAt(src, src->actualSize, elem, oldRow, oldCol, newRow, newCol);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index) {
	if (src == NULL || index > src->actualSize || index < 0)
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if (spArrayListIsEmpty(src))
		return SP_ARRAY_LIST_EMPTY;
	if(index < src->actualSize-1) {
		for(int i=index; i<src->actualSize-1; i++) {
			for (int j=0; j<SP_LIST_WIDTH; j++) src->positions[j][i] = src->positions[j][i+1];
			src->element[i] = src->element[i+1];
		}
	}
	for (int i=0; i<SP_LIST_WIDTH; i++) {
		src->positions[i][src->actualSize-1] = -1;
	}
	src->element[src->actualSize-1] = SP_LIST_EMPTY;
	src->actualSize--;
	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src) {
	if (src == NULL) return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if (spArrayListIsEmpty(src)) return SP_ARRAY_LIST_EMPTY;
	return spArrayListRemoveAt(src, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src) {
	if (src == NULL) return SP_ARRAY_LIST_INVALID_ARGUMENT;
	if (spArrayListIsEmpty(src)) return SP_ARRAY_LIST_EMPTY;
	return spArrayListRemoveAt(src, src->actualSize - 1);
}

bool spArrayListIsFull(SPArrayList* src) {
	if (src == NULL || src->actualSize < SP_LIST_LENGTH)
		return false;
	return true;
}

bool spArrayListIsEmpty(SPArrayList* src) {
	if (src == NULL || src->actualSize != 0)
		return false;
	return true;
}

int spArrayListSize(SPArrayList* src) {
	if (src == NULL) return SP_ARRAY_LIST_INVALID_ARGUMENT;
	return src->actualSize;
}
