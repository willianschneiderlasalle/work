#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //
#include<stdio_ext.h> //allow __fpurge - clears buffer

void invalidDigit();
void textGreen();
void textRed();
void resetText();

int registerMovie()
{
	printf("====== REGISTER MOVIE ======\n\n");

	struct movie
	{
		char title[100];
		char ID[16];
		char isRent[10];
		float tax;
	};

	struct movie newMovie;

	//set movie title
	printf("Title: ");
	__fpurge(stdin); // clears buffer
	fgets(newMovie.title, sizeof(newMovie.title), stdin);
	strtok(newMovie.title, "\n");

	//create movie ID
	srand(time(NULL));
	int i = rand();
	snprintf(newMovie.ID, 16, "%x", i);
	printf("ID: %s", newMovie.ID);

	//set movie status
	strcpy(newMovie.isRent, "false"); //false because it is not rented while you are registering it
	printf("\nStatus: %s", newMovie.isRent);

	//set movie tax by day
	printf("\nTax by day: ");
	scanf("%f", &newMovie.tax);

	char isInfoRight; 

	do{
		printf("\nSave the data above? Y/N\n");
		__fpurge(stdin);
		scanf("%c", &isInfoRight);

		if(isInfoRight == 'y' || isInfoRight == 'Y')
		{
			break;
		}
		else if(isInfoRight == 'n' || isInfoRight == 'N')
		{
			printf("\nPress Enter to go back to menu or press CTRL + C to abort...\n");
			__fpurge(stdin);
			getchar();
			system("clear");
			return 1;
		}
		else
		{
			invalidDigit();
		}

	}while(isInfoRight != 'y' && isInfoRight != 'Y' && isInfoRight != 'n' && isInfoRight != 'N');

	FILE *myFile;
	myFile = fopen("files/register.txt", "a");
	fprintf(myFile, "%s|%s|%s|%.2f;", newMovie.ID, newMovie.title, newMovie.isRent, newMovie.tax); //save movie info
	fclose(myFile);

	textGreen();
	printf("\nMovie registered successfully!!\n");
	resetText();

	char userChoice;

	do{
		printf("\nWanna register a new movie? Y/N\n");
		__fpurge(stdin);
		scanf("%c", &userChoice);

		if(userChoice == 'y' || userChoice == 'Y')
		{	
			system("clear");
			registerMovie();
		}
		else if(userChoice == 'n' || userChoice == 'N')
		{
			printf("\nPress Enter to go back to menu or press CTRL + C to abort...\n");
			__fpurge(stdin);
			getchar();
			system("clear");
			return 1;
		}
		else
		{
			invalidDigit();
		}
	}while(userChoice != 'y' && userChoice != 'Y' && userChoice != 'n' && userChoice != 'N');

	system("clear");
	return 0;
}

void editMovie()
{
	printf("====== EDIT MOVIE ======\n\n");
}

void searchMovie()
{
	printf("====== SEARCH MOVIE ======\n\n");
}

void checkInfo()
{
	printf("====== CHECK MOVIE INFO ======\n\n");
}

void generateTXT()
{
	printf("====== GENERATE TXT ======\n\n");
}

void generatePDF()
{
	printf("====== GENERATE PDF ======\n\n");
}

void invalidDigit()
{
	textRed();
	printf("Digit invalid! Insert a valid digit or press CTRL + C to abort...\n");
	resetText();
}

void textGreen()
{
	printf("\033[0;32m");
}

void textRed()
{
	printf("\033[0;31m");
}

void resetText()
{
	printf("\033[0m");
}