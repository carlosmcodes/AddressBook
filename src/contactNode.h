/*
 * contactNode.h
 *
 *  Created on: Apr 25, 2018
 *      Author: carlos
 */

#ifndef CONTACTNODE_H_
#define CONTACTNODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// contact struct w pointer to another struct
typedef struct contact {
	char firstName[25];
	char lastName[25];
	char email[60];
	long number;
	struct contact *nextPointer;
} contactStructNode;

// alias POINTER to contact struct
typedef contactStructNode* pNode;
/*
 *  inserts a new contact into nth  positions
 */
void insertContact();
/*
 * deletes at the nth position
 */
void deleteContact();
/*
 * gets contact w specified position
 */
void getContact();
/*
 * grabs field with nth contact and nth field
 */
void getField();
/*
 * totals up the number of contacts(nodes)
 */
void getNumberOf();

/*
 * loads information from a file
 */
void loadF();
/*
 * saves to specified file
 */
void save();
/*
 * quit task and exits program
 */
void quit();
/*
 * grabs from nth position and allows editing to specific field
 */
void edit();
/*
 *  sorts contacts in ascending order
 */
void sort();

/*
 * simple method to store contact information
 */
void store(pNode storeThis);

#endif /* CONTACTNODE_H_ */
