/*
 * main.c
 *
 *  Created on: Apr 26, 2018
 *      Author: carlos
 */
#include <stdio.h>
#include <stdlib.h>
#include "contactNode.h"
#include <string.h>

int main(void) {

	//std stuff what i still have no idea does
	setvbuf(stdout, NULL, _IONBF, 0);

	puts("Ready");

	char input[BUFSIZ];

	// main conditions
	while (fgets(input, BUFSIZ, stdin) != 'q') {

		switch (input[0]) {
		case 'a':
			insertContact();
			break;

		case 'd':
			deleteContact();
			break;
		case 'g':
			getContact();

			break;
		case 'f':
			getField();

			break;
		case 'n':
			getNumberOf();

			break;
		case 'l':
			loadF();

			break;
		case 'q':
			quit();
			break;
		case 's':
			save();

			break;
		case 'e':
			edit();

			break;
		case 'o':
			sort();

			break;
		}
	}

	// q condition
	if (fgets(input, BUFSIZ, stdin) == 'q')
		quit();
}

