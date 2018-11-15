#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //
#include <stdio_ext.h> //allow __fpurge - clears buffer

#define TAX 5 //5 bucks per day
#define SIZE 2048 //define size for reading file

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
	newMovie.tax = TAX; //5 bucks per day
	printf("\nTax by day: %.2f \n", newMovie.tax);

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
	fprintf(myFile, "%s@%s#%s$%.2f;", newMovie.ID, newMovie.title, newMovie.isRent, newMovie.tax); //save movie info
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

	FILE *myFile;

	if((myFile = fopen("files/register.txt", "r")) == NULL)
	{
		system("clear");
		textRed();
		printf("You need to have at least one movie registered. Backing to menu...\n");
		resetText();
		return;
	}

	myFile = fopen("files/register.txt", "r+");
	
	fclose(myFile);
	//system("clear");
}

void searchMovie()
{
	printf("====== SEARCH MOVIE ======\n\n");

	FILE *myFile;

	if((myFile = fopen("files/register.txt", "r")) == NULL)
	{
		system("clear");
		textRed();
		printf("You need to have at least one movie registered. Backing to menu...\n");
		resetText();
		return;
	}

	myFile = fopen("files/register.txt", "r+");

	char search[100];
	char fileContent[500];

	printf("Search: ");
	__fpurge(stdin);
	fgets(search, sizeof(search), stdin);

	char * helper = NULL;

	while(fgets(fileContent, sizeof(fileContent), myFile) != NULL)
	{
		printf("%s", fileContent);
	}

	helper = strstr(fileContent, search);

	if( helper )
	{
		printf("Found!");
	}
	else
	{
		printf("NOT Found!");
	}

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