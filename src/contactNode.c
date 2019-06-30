*
 * contactNode.c
 *
 *  Created on: Apr 25, 2018
 *      Author: carlos
 */

#include "contactNode.h"

int nodeCount = 0;
char input[BUFSIZ];
pNode curNode = NULL;
pNode top = NULL;

void insertContact() {
	int insertAt;
	pNode prev = NULL;
	pNode node = NULL;

	// create mem
	node = malloc(sizeof(contactStructNode));

	// position to insert at
	insertAt = atoi(fgets(input, BUFSIZ, stdin));

	// save info to node
	store(node);

	// assigns null to new node.next
	node->nextPointer = NULL;

	// if list empty
	if (top == NULL) {

		// if you try to pull a sneaky one and insert at an awk pos
		if (insertAt != 0)
			return;

		// indicating you should start adding by zero-ith pos
		else {
			top = node;
			nodeCount++;
			return;
		}
	}
	// list is already present but you want to insert
	// at the beginning
	if (top != NULL && insertAt == 0) {
		node->nextPointer = top;
		top = node;
		nodeCount++;
		return;
	}

	// start from the top
	curNode = top;

	int i = 0;
	// iterating through
	while (i < insertAt) {

		// prev follows
		prev = curNode;
		curNode = curNode->nextPointer;

		// * hit the end
		if (curNode == NULL)
			break;
		i++;
	}
	// reassign directions
	node->nextPointer = curNode;
	prev->nextPointer = node;
	nodeCount++;
}

// "elegant" way to store data from user
void store(pNode storeThis) {
	char breakHere[999] = ",";
	char *pDelim;

	fgets(input, BUFSIZ, stdin);

	// typical strok method
	pDelim = strtok(input, breakHere);
	while (pDelim) {
		curNode = storeThis;
		strcpy(curNode->lastName, pDelim);
		pDelim = strtok(NULL, breakHere);
		strcpy(curNode->firstName, pDelim);
		pDelim = strtok(NULL, breakHere);
		strcpy(curNode->email, pDelim);
		pDelim = strtok(NULL, breakHere);
		pDelim[strlen(pDelim) - 1] = '\0';
		curNode->number = atol(pDelim);
		pDelim = strtok(NULL, breakHere);

	}

}
void deleteContact() {

	pNode next = NULL;
	int position = 0;

	// get pos to delete from
	position = atoi(fgets(input, BUFSIZ, stdin));
	if (position > nodeCount)
		return;
	else {

		// if you try to pull a fast one
		if (top == NULL)
			return;

		// delete head node
		if (position == 0) {
			free(top);
			top = top->nextPointer;
			nodeCount--;
			return;
		}

		// points to top of linked list
		curNode = top;

		// iterate through
		int i = 0;
		while (curNode != NULL && i < position - 1) {
			curNode = curNode->nextPointer;
			i++;
		}
		// hit end of list
		if (curNode == NULL || curNode->nextPointer == NULL)
			return;

		// direct accordingly
		next = curNode->nextPointer->nextPointer;
		curNode->nextPointer = next;
		nodeCount--;
	}
}
void getContact() {
	int getFrom;
	int i = 0;

	getFrom = atoi(fgets(input, BUFSIZ, stdin));

	// start from top
	curNode = top;

	while (i < getFrom) {
		curNode = curNode->nextPointer;
		i++;
	}

	printf("%s,%s,", curNode->lastName, curNode->firstName);
	printf("%s,%ld\n", curNode->email, curNode->number);

}
void getField() {
	int get;

	// get position to grab from
	get = atoi(fgets(input, BUFSIZ, stdin));

	int i = 0;

	// start at top node
	curNode = top;
	while (i < get) {
		curNode = curNode->nextPointer;
		i++;
	}

// get field
	fgets(input, BUFSIZ, stdin);
	switch (input[0]) {

// kinda strange but also lazy way
	case 'l':
		printf("%s\n", curNode->lastName);
		break;
	case 'f':
		printf("%s\n", curNode->firstName);
		break;
	case 'e':
		printf("%s\n", curNode->email);
		break;
	case 'p':
		printf("%ld\n", curNode->number);
		break;
	}
}
void getNumberOf() {
// keeps count :)
	printf("%d\n", nodeCount);

}
void loadF() {
	FILE * fileToOpen;

	char fileTitle[60];

	char content[BUFSIZ];

	// file name
	fgets(fileTitle, 59, stdin);

	// edits
	fileTitle[strlen(fileTitle) - 1] = '\0';

	// open to read
	fileToOpen = fopen(fileTitle, "r");

	// if file valid
	if (fileToOpen) {
		nodeCount = 0;

		curNode = top;
		pNode new;

		// skips header
		fgets(content, BUFSIZ, fileToOpen);

		while (!feof(fileToOpen)) {
			// clear content memory
			memset(content, 0, strlen(content));

			// grab line
			fgets(content, BUFSIZ, fileToOpen);

			// check if hit end
			if (content[0] == '\0')
				return;

			// create mem
			new = malloc(sizeof(contactStructNode));

			//if file valid
			if (new) {
				char breakHere[999] = ",";
				char *pDelim;

				// typical strok method
				pDelim = strtok(content, breakHere);
				while (pDelim) {

					strcpy(new->lastName, pDelim);
					pDelim = strtok(NULL, breakHere);
					strcpy(new->firstName, pDelim);
					pDelim = strtok(NULL, breakHere);
					strcpy(new->email, pDelim);
					pDelim = strtok(NULL, breakHere);
					pDelim[strlen(pDelim) - 1] = '\0';
					new->number = atol(pDelim);
					pDelim = strtok(NULL, breakHere);

				}

				// if empty
				if (top == NULL) {
					top = new;
					curNode = top;
					nodeCount++;

				} else {
					// not empty
					curNode->nextPointer = new;
					curNode = new;
					nodeCount++;
				}
			}

		}
		// house cleaning
		fclose(fileToOpen);
	} else
		puts("No File");
}
void save() {
	FILE *saveTo;
	char fileTitle[80];

	fgets(fileTitle, 80, stdin);

	fileTitle[strlen(fileTitle) - 1] = '\0';

	saveTo = fopen(fileTitle, "w");

	int i = 0;

	if (saveTo) {
		curNode = top;

		// header
		fprintf(saveTo, "lastName,firstName,email,phoneNumber\n");

		for (i = 0; i < nodeCount; i++) {

			// txt to file
			fprintf(saveTo, "%s,%s,%s,%ld\n", curNode->lastName,
					curNode->firstName, curNode->email, curNode->number);
			curNode = curNode->nextPointer;
		}

		fclose(saveTo);
	} else
		puts("No File");
}
void quit() {
	// most difficult method
	puts("Complete");

}

void edit() {
// EAAAAAAAAAAASY EXTRA CREDIT
	int get = 0;
// gets where you want to edit
	get = atoi(fgets(input, BUFSIZ, stdin));

	int i = 0;
// obvi start at top
	curNode = top;

// iterate
	while (i < get) {
		curNode = curNode->nextPointer;
		i++;
	}
// extremely lazy but also creative
	fgets(input, BUFSIZ, stdin);
	switch (input[0]) {
	case 'l':
		fgets(input, BUFSIZ, stdin);
		input[strlen(input) - 1] = '\0';
		strcpy(curNode->lastName, input);
		break;
	case 'f':
		fgets(input, BUFSIZ, stdin);
		input[strlen(input) - 1] = '\0';
		strcpy(curNode->firstName, input);

		break;
	case 'e':
		fgets(input, BUFSIZ, stdin);
		input[strlen(input) - 1] = '\0';
		strcpy(curNode->email, input);

		break;
	case 'p':
		fgets(input, BUFSIZ, stdin);
		input[strlen(input) - 1] = '\0';
		curNode->number = atol(input);
		break;
	}

}
void sort() {
	puts("No tengo tiempo");

}

