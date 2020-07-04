#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 11
struct DataItem {
	int data;
	int key;
};
int iteration = 0;
struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashFunction(int key) {
	return key % SIZE;
}

struct DataItem* search(int key) {
	int hashIndex = hashFunction(key);
	int temp = hashIndex;
	int s = 0;
	while (hashArray[hashIndex] != NULL) {
		if (s == iteration) {
			break;
		}
		if (hashArray[hashIndex]->key == key)
			return hashArray[hashIndex];

		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex = hashFunction(hashIndex);
		s++;
	}

	return NULL;

}
void insert(int key, int data) {

	struct DataItem* item = (struct DataItem*) malloc(sizeof(struct DataItem));
	item->data = data;
	item->key = key;

	//get the hash
	int hashIndex = hashFunction(key);

	//move in array until an empty or deleted cell
	while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex = hashFunction(hashIndex);
	}

	hashArray[hashIndex] = item;
	iteration++;
}
struct DataItem* deleted(struct DataItem* item) {
	if (item == NULL) {
		return NULL;
	}
	struct DataItem* abc = search(item->key);
	printf("abc is %d" + abc->key);
	if (abc == NULL) {
		return NULL;
	}
	int key = item->key;
	//get the hash
	int hashIndex = hashFunction(key);

	//move in array until an empty
	while (hashArray[hashIndex] != NULL) {

		if (hashArray[hashIndex]->key == key) {
			struct DataItem* temp = hashArray[hashIndex];

			//assign a dummy item at deleted position
			hashArray[hashIndex] = dummyItem;
			return temp;
		}

		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex = hashFunction(hashIndex);
	}

	return NULL;
}

void display() {
	int i = 0;

	for (i = 0; i < SIZE; i++) {

		if (hashArray[i] != NULL)
			printf(" (%d,%d)", hashArray[i]->key, hashArray[i]->data);
		else
			printf(" Blank ");
	}

	printf("\n");
}

int main() {

	dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
	dummyItem->data = -1;
	dummyItem->key = -1;

	insert(1, 20);
	insert(2, 70);
	insert(42, 80);
	insert(4, 25);
	insert(12, 44);
	insert(14, 32);
	insert(17, 11);
	insert(13, 78);
	insert(37, 97);

	display();
	item = search(37);

	if (item != NULL) {
		printf("Element found: %d\n", item->data);
	}
	else {
		printf("Element not found\n");
	}
	deleted(item);
	insert(17, 100);
	item = search(37);
	printf("After deletion of 37 key and inserting 17 key with data 100\n");
	display();
	printf("Now searching 37 key in table\n");
	if (item != NULL) {
		printf("Element found: %d\n", item->data);
	}
	else {
		printf("Element not found\n");
	}
	system("pause");
}
