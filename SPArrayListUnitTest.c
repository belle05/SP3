#include "unit_test_util.h"
#include "SPArrayList.h"
#include <stdbool.h>

#define CAPACITY_SIZE 10

static bool spArrayListBasicGetTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddLast(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListGetAt(list, i) == i);
	}
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicCopyTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	SPArrayList* copyList = spArrayListCopy(list);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListGetAt(copyList, i) == spArrayListGetAt(list, i));
	}
	spArrayListDestroy(list);
	spArrayListDestroy(copyList);
	return true;
}

static bool spArrayListBasicRemoveTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
	}
	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListRemoveFirst(list) == SP_ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE - i - 1);
	}
	ASSERT_TRUE(spArrayListIsEmpty(list));
	spArrayListDestroy(list);
	return true;
}

static bool spArrayListBasicAddTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(spArrayListAddFirst(list, i) == SP_ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(spArrayListSize(list) == i + 1);
	}
	ASSERT_TRUE(spArrayListSize(list) == CAPACITY_SIZE);
	spArrayListDestroy(list);
	return true;
}
static bool spArrayListCreateTest() {
	SPArrayList* list = spArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	spArrayListDestroy(list);
	return true;
}

int main() {
	RUN_TEST(spArrayListCreateTest);
	RUN_TEST(spArrayListBasicAddTest);
	RUN_TEST(spArrayListBasicRemoveTest);
	RUN_TEST(spArrayListBasicGetTest);
	RUN_TEST(spArrayListBasicCopyTest);
	return 0;
}
