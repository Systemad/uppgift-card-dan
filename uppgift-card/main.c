#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "safeinput.h"
#include <stdbool.h>

typedef struct
{
	int cardName;
	char dateAccess[20];
	bool access;
} CARD;

typedef struct
{
	CARD* allUsers;
	int amountOfUsers;
}SYSTEM_STATE;

void listAllCardsInSystem(SYSTEM_STATE* state)
{
	printf("\tLIST OF ALL CARDS IN SYSTEM\n");
	for (int i = 0; i < state->amountOfUsers; i++)
	{
		CARD p = state->allUsers[i];
		printf("\n%d.", p.cardName);
		if (p.access == true)
			printf("Access");
		else
			printf("No access");
		printf("Added to system: %s", p.dateAccess);
	}
	getch();
}

void listUsers(SYSTEM_STATE* state)
{
	printf("Listing all users...\n");
	for (int i = 0; i < state->amountOfUsers; i++)
	{
		CARD p = state->allUsers[i];
		printf("\n%d ", p.cardName);
		if (p.access == true)
			printf("has access - ");
		else
			printf("has no access - ");
		printf("added to system: %s", p.dateAccess);
	}
	printf("\nPress enter to return\n");
	getch();
}

void newUsers(SYSTEM_STATE* state)
{
	printf("--New User--\n");

	int index;
	if (state->amountOfUsers == 0)
	{
		state->allUsers = malloc(sizeof(CARD));
		state->amountOfUsers = 1;
		index = 0;
	}
	else
	{
		state->allUsers = realloc(state->allUsers,
			sizeof(CARD) * (state->amountOfUsers + 1));
		index = state->amountOfUsers;
		state->amountOfUsers++;
	}

	int newCard;
	GetInputInt("\nEnter card number: ", &newCard);

	printf("What access should user have: \n");
	int choice;
	printf("1. Access\n2. No Access\nChoose an option: ");
	scanf("%d", &choice);

	if (choice == 1) {
		state->allUsers[index].access = true;
	}
	else {
		state->allUsers[index].access = false;
	}

	time_t justNu = time(NULL);
	struct tm* datum = localtime(&justNu);

	state->allUsers[index].cardName = newCard;
	char accessDate[20];
	snprintf(accessDate, 20, "%d-%d-%02d %02d:%02d", datum->tm_year + 1900, datum->tm_mon + 1, datum->tm_mday, datum->tm_hour, datum->tm_min);
	strcpy(state->allUsers[index].dateAccess, accessDate);
}

void remoteOpen(SYSTEM_STATE* state)
{
	printf("\nLamp is currently: GREEN\n");
}

/*
Placebo


string cardtest;
	printf("Enter a cardnumber or X to exit\n");
	GetInput("---> ", &cardtest, sizeof(cardtest));
	if (strcmp(&cardtest) == "x") {
		return;
	}

*/

void fakeTest(SYSTEM_STATE* state)
{
	int cardtest;
	printf("Enter a cardnumber or X to exit\n");
	GetInputInt("---> ", &cardtest);
	if (strcmp(&cardtest) == "x") {
		return;
	}
	else
	{
		for (int i = 0; i < state->amountOfUsers; i++)
		{
			if (state->allUsers[i].cardName == cardtest)
			{
				if (state->allUsers[i].access == true)
				{
					printf("\nLAMP: GREEN\n");
					printf("Access granted!\n");
					getch();
					return;
				}
				else if (state->allUsers[i].access == false)
				{
					printf("\nLAMP: RED\n");
					printf("Access denied!\n");
					getch();
				}
				else
					printf("Card does not exist in the system\n");
			}
		}
	}
		//getch();
}

void adminPanel(SYSTEM_STATE* state)
{
	while (true)
	{
		printf("\n---Admin Panel---\n");
		printf("1. Remote open door\n2. List users\n3. New User\n");
		printf("4. Fake test\n5. Exit\n");
		int selection;
		if (!GetInputInt("Choose an option: ", &selection))
			continue;
		switch (selection)
		{
		case 1:
			remoteOpen(state);
			break;
		case 2:
			listUsers(state);
			break;
		case 3:
			newUsers(state);
			break;
		case 4:
			fakeTest(state);
			break;
		case 5:
			return;
		}
	}
}

int main()
{
	SYSTEM_STATE state;
	state.allUsers = NULL;
	state.amountOfUsers = 0;
	adminPanel(&state);

	return 0;
}
