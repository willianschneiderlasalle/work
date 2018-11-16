#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //
#include <stdio_ext.h> //allow __fpurge - clears buffer

#define TAX 5 //5 bucks per day

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

	char isInfoRight; 

	do{
		printf("\n\nSave the data above? Y/N\n");
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
	fprintf(myFile, "%s;%s;%s\n", newMovie.title, newMovie.ID, newMovie.isRent); //save movie info
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

  	int found = 0;
  	char search[100];
  	char line[200];
  	char _haveToClean = '\0';
  	char newSearch;

  	do{
  		if(_haveToClean = 'y')
  		{
  			getchar();
  			system("clear");
  			_haveToClean = 'n';
  		}

  		memset(search, 0, sizeof(search));
  		memset(line, 0, sizeof(line));

  		fseek(myFile, 0, SEEK_SET);

	  	printf("Search for a movie by title or code: ");
	  	__fpurge(stdin);
	  	fgets(search, sizeof(search), stdin); //get word to search
	  	strtok(search, "\n"); //remove \n that fgets insert

	  	while(fgets(line, sizeof(line), myFile))
	  	{
	  		if(strstr(line, search) != NULL) //check if the word exists in the file
		  	{  	
		  		for(int x = 0; x<sizeof(line); x++)
		  		{
		  			if(line[x] == ';')
		  				line[x] = '\n'; //replace ; for a break line
		  		}
		  		printf("\n%s", line); //print line content
		  		found=1;
		  	}
	  	}

	  	if(found==0) //if haven't found anything, show an error
	  	{
	  		system("clear");
	  		textRed();
	  		printf("Movie not found! Try again or press CTRL + C to abort...\n");
	  		resetText();
	  		_haveToClean = 'y';
	  	}

	  	if(found == 1)
	  	{
	  		do
	  		{
		  		printf("\nSearch for another movies? Y/N\n");
		  		__fpurge(stdin);
		  		scanf("%c", &newSearch);

		  		if(newSearch != 'y' && newSearch != 'Y' && newSearch != 'n' && newSearch != 'N'){
		  			system("clear");
		  			invalidDigit();
		  		}

		  		if(newSearch == 'y' || newSearch == 'Y')
		  			found = 0;

	  		}while(newSearch != 'y' && newSearch != 'Y' && newSearch != 'n' && newSearch != 'N');
	  	}
  	}while(found==0);

  	getchar();
  	system("clear");
	fclose(myFile);
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

	char buffer[128];
	while((fgets (buffer, 128, myFile))!= NULL) {
    	printf ("%s",buffer);
	}
	
	fclose(myFile);
	//system("clear");
}

void checkInfo()
{
	printf("====== MOVIES REGISTERED ======\n");

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

	char line[200];

	while(fgets(line, sizeof(line), myFile))
	  	{
	  		for(int x = 0; x<sizeof(line); x++)
	  		{
	  			if(line[x] == ';')
	  				line[x] = '\n'; //replace ; for a break line
	  		}
	  		printf("\n%s", line); //print line content
	  	}

	__fpurge(stdin);
	printf("\nPress any key to go back to menu or press CTRL+C to abort...\n");
	getchar();
	system("clear");
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