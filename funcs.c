#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //used by rand()
#include <sys/time.h> //gettimeofday
#include <stdio_ext.h> //allow __fpurge - clears buffer

#define LOW 268435456
#define HIGH 4294967295

void invalidDigit();
void textGreen();
void textRed();
void textYellow();
void resetText();
void save();
int checkDupeTitle();

int registerMovie()
{
	printf("====== REGISTER MOVIE ======\n\n");

	struct movie
	{
		char title[100];
		char ID[10];
		char isRent[10];
	};

	struct movie newMovie;

	//set movie title
	do{
		printf("Title: ");
		__fpurge(stdin); // clears buffer
		fgets(newMovie.title, sizeof(newMovie.title), stdin);
		strtok(newMovie.title, "\n");

		if(strlen(newMovie.title) <= 4)
		{
			system("clear");
			textRed();
			printf("Title must have more than 4 characters! Try again...\n");
			resetText();
		}

	}while(strlen(newMovie.title) <= 4);

	//create movie ID
	srand(time(NULL));
	int num1;
  	num1 = (LOW+rand()%(HIGH-LOW+1)); //create random number that have 8 bit in hex

    sprintf(newMovie.ID, "%x", num1); //pass number to hex
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

	char fileName[25] = "files/register.txt";

	myFile = fopen(fileName, "a");
	fprintf(myFile, "%s|%s;%s\n", newMovie.title, newMovie.ID, newMovie.isRent); //save movie info
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

	char fileName[25] = "files/register.txt";

	if((myFile = fopen(fileName, "r")) == NULL)
	{
		system("clear");
		textRed();
		printf("You need to have at least one movie registered. Backing to menu...\n");
		resetText();
		return;
	}

	myFile = fopen(fileName, "r+");

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
	  	textYellow();
	  	printf("\n     TITLE\t\tCODE\t\tRENTED?");
	  	resetText();
	  	strtok(search, "\n"); //remove \n that fgets insert

	  	int count = 1;

	  	char title[200];
	  	char code[10];
	  	char status[10];
	  	
	  	int codeHelper;
	  	int codeIndex = 0;

	  	int statusHelper;
	  	int statusIndex = 0;

	  	while(fgets(line, sizeof(line), myFile))
	  	{
	  		if(strstr(line, search) != NULL) //check if the word exists in the file
		  	{  	
		  		
		  		for(int x=0; x<sizeof(title); x++) //clear title
		  			title[x] = '\0';

		  		for(int x = 0; x<strlen(line); x++) //get movie title
		  		{
		  			if(line[x] == '|')
		  				continue;
		  			
		  			title[x] = line[x];
		  		}

		  		for(int y=0; y<sizeof(code); y++) //clear code
		  			code[y] = '\0';

		  		for(int y=0; y<strlen(line); y++) //get code
		  		{
		  			if(line[y] == '|')
		  			{
		  				codeHelper = 1;
		  			}

		  			if(line[y] == ';')
		  			{
		  				codeHelper = 0;
		  				continue;
		  			}

		  			if(codeHelper == 1)
		  			{
		  				code[codeIndex] = line[y+1];
		  				
		  				if(code[codeIndex] == ';')
		  					code[codeIndex] = '\0';

		  				codeIndex++;
		  			}
		  		}

		  		for(int z=0; z<sizeof(status); z++) //clear status
		  			status[z] = '\0';

		  		for(int z=0; z<strlen(line); z++) //get status
		  		{
		  			if(line[z] == ';')
		  			{
		  				statusHelper = 1;
		  			}

		  			if(line[z] == '\n')
		  			{
		  				statusHelper = 0;
		  				continue;
		  			}

		  			if(statusHelper == 1)
		  			{
		  				status[statusIndex] = line[z+1];
		  				
		  				if(status[statusIndex] == '\n')
		  					status[statusIndex] = '\0';

		  				statusIndex++;
		  			}
		  		}

		  		if(count < 10)
		  			printf("\n00%d. %.10s\t\t%s\t%s", count, title, code, status); //print line content
		  		else if(count >= 10 && count < 100)
		  			printf("\n0%d. %.10s\t\t%s\t%s", count, title, code, status); //print line content
		  		else if(count >= 100)
		  			printf("\n%d. %.10s\t\t%s\t%s", count, title, code, status); //print line content
		  		
		  		count++;

		  		codeHelper = 0;
		  		codeIndex = 0;

		  		statusHelper = 0;
		  		statusIndex = 0;

		  		found=1;
		  	}
	  	}

	  	if(found==0) //if haven't found anything, show an error
	  	{
	  		//system("clear");
	  		textRed();
	  		printf("\n\nMovie not found! Try again or press CTRL + C to abort...\n");
	  		resetText();
	  		_haveToClean = 'y';
	  	}

	  	if(found == 1)
	  	{
	  		do
	  		{
		  		printf("\n\nSearch for another movies? Y/N\n");
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
	printf("====== EDIT MOVIE ======\n");

	FILE *myFile;

	char fileName[25] = "files/register.txt";

	if((myFile = fopen(fileName, "r")) == NULL)
	{
		system("clear");
		textRed();
		printf("You need to have at least one movie registered. Backing to menu...\n");
		resetText();
		return;
	}

	myFile = fopen(fileName, "r+");

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

  		//memset(search, 0, sizeof(search)); //clear search variable
  		memset(line, 0, sizeof(line)); //clear line variable

  		fseek(myFile, 0, SEEK_SET); //point to the beggining of the file

	  	printf("Type the title of the movie you would like to edit: ");
	  	__fpurge(stdin);
	  	fgets(search, sizeof(search), stdin); //get word to search
	  	textYellow();
	  	printf("\n   TITLE\t\tCODE\t\tRENTED?\n");
	  	resetText();
	  	strtok(search, "\n"); //remove \n that fgets insert

	  	int count = 1;

	  	char title[200];
	  	char code[10];
	  	char status[10];
	  	
	  	int codeHelper;
	  	int codeIndex = 0;

	  	int statusHelper;
	  	int statusIndex = 0;

	  	char editWhat[10];
	  	char newTitle[200];
	  	char willSave;

	  	while(fgets(line, sizeof(line), myFile)) //check every line of the file
	  	{
	  		for(int x=0; x<sizeof(title); x++) //clear title
	  			title[x] = '\0';

	  		for(int x = 0; x<strlen(line); x++) //get movie title
	  		{
	  			if(line[x] == '|')
	  				continue;
	  			
	  			title[x] = line[x];
	  		}

	  		for(int y=0; y<sizeof(code); y++) //clear code
	  			code[y] = '\0';

	  		for(int y=0; y<strlen(line); y++) //get code
	  		{
	  			if(line[y] == '|')
	  			{
	  				codeHelper = 1;
	  			}

	  			if(line[y] == ';')
	  			{
	  				codeHelper = 0;
	  				continue;
	  			}

	  			if(codeHelper == 1)
	  			{
	  				code[codeIndex] = line[y+1];
	  				
	  				if(code[codeIndex] == ';')
	  					code[codeIndex] = '\0';

	  				codeIndex++;
	  			}
	  		}

	  		for(int z=0; z<sizeof(status); z++) //clear status
	  			status[z] = '\0';

	  		for(int z=0; z<strlen(line); z++) //get status
	  		{
	  			if(line[z] == ';')
	  			{
	  				statusHelper = 1;
	  			}

	  			if(line[z] == '\n')
	  			{
	  				statusHelper = 0;
	  				continue;
	  			}

	  			if(statusHelper == 1)
	  			{
	  				status[statusIndex] = line[z+1];
	  				
	  				if(status[statusIndex] == '\n')
	  					status[statusIndex] = '\0';

	  				statusIndex++;
	  			}
	  		}

		  		if((strcmp(search, title) == 0 || strcmp(search,code) == 0) && checkDupeTitle(search, myFile) == 0) //check if there is a title with the word searched
	  		{
				printf("\n%d. %.12s\t\t%s\t%s\n", count, title, code, status); 

				found = 1;

				do{
					printf("\nWhat would like to edit? title / status: ");
					__fpurge(stdin);
				  	fgets(editWhat, sizeof(editWhat), stdin); //get word to search
				  	strtok(editWhat, "\n"); //remove \n that fgets insert

				  	if(strcmp(editWhat, "Title") == 0 || strcmp(editWhat, "title") == 0) //edit title
				  	{
				  		do
				  		{
					  		printf("New title: ");
					  		__fpurge(stdin);
					  		fgets(newTitle, sizeof(newTitle), stdin); //get word to search
					  		strtok(newTitle, "\n"); //remove \n that fgets insert

					  		if(strlen(newTitle) <= 4)
					  		{
		  						system("clear");
								textRed();
								printf("Title must have more than 4 characters! Try again...\n");
								resetText();
					  		}

						}while (strlen(newTitle) <= 4);

						textRed();
				  		printf("\nCurrent title = %s", title);
				  		textGreen();
				  		strcpy(title, newTitle);
				  		printf("\nNew title = %s", newTitle);
				  		resetText();

				  	}
				    else if(strcmp(editWhat, "Status") == 0 || strcmp(editWhat, "status") == 0) //edit status
				  	{
				  		textYellow();
				  		printf("\nChanging status to false needs to remove manually the user log on user.txt\n");
				  		resetText();

				  		textRed();
				  		printf("\nCurrent status = %s", status);
				  		resetText();

				  		if(strcmp(status,"true") == 0)
				  		{
				  			strcpy(status, "false");

				  			textGreen();
				  			printf("\nNew status = %s", status);
				  			resetText();
				  		}
				  		else if(strcmp(status, "false") == 0)
				  		{
				  			strcpy(status, "true");

				  			textGreen();
				  			printf("\nNew status = %s", status);
				  			resetText();
				  		}
				  		resetText();
				  		printf("\nStatus can only be true or false!");
				  	}
				  	else
				  	{
				  		printf("\n");
				  		invalidDigit();
				  	}
			  	}while(strcmp(editWhat, "Title") != 0 && strcmp(editWhat, "title") != 0 && (strcmp(editWhat, "Status") != 0 && strcmp(editWhat, "status") != 0));

				do
				{
				  	printf("\n\nWould you like to save this changes? Y/N\n");
			  		__fpurge(stdin);
			  		scanf("%s", &willSave); //get word to search

			  		if(willSave == 'y' || willSave == 'Y')
			  		{
			  			save(editWhat, title, code, status, count, line); //call function to save the changes
			  		}
			  		else if(willSave == 'n' || willSave == 'N')
			  		{
			  			system("clear");
			  			textYellow();
			  			printf("Changes discarded!");
			  			resetText();
			  		}
			  		else
			  		{
			  			invalidDigit();
			  		}
				}while(willSave != 'y' && willSave != 'Y' && willSave != 'N' && willSave != 'n');
	  		}
	  		
	  		count++;

	  		codeHelper = 0;
	  		codeIndex = 0;

	  		statusHelper = 0;
	  		statusIndex = 0;
	  	}

	  	if(found==0 && checkDupeTitle(search, myFile) == 0) //if haven't found anything, show an error
	  	{
	  		textRed();
	  		printf("\n\nMovie not found! Try again or press CTRL + C to abort...\n");
	  		resetText();
	  		_haveToClean = 'y';
	  	}

	  	if(found == 1)
	  	{
	  		do
	  		{
		  		printf("\n\nWill you edit anything else? Y/N\n");
		  		__fpurge(stdin);
		  		scanf("%c", &newSearch);

		  		if(newSearch != 'y' && newSearch != 'Y' && newSearch != 'n' && newSearch != 'N'){
		  			system("clear");
		  			invalidDigit();
		  		}

		  		if(newSearch == 'y' || newSearch == 'Y')
		  		{
		  			fclose(myFile);
		  			myFile = fopen(fileName, "r+");
		  			found = 0;
		  		}

	  		}while(newSearch != 'y' && newSearch != 'Y' && newSearch != 'n' && newSearch != 'N');
	  	}
  	}while(found==0 || checkDupeTitle(search, myFile) == 1);

  	getchar();
  	system("clear");
	fclose(myFile);	
}

void checkInfo()
{
	FILE *myFile;

	char fileName[25] = "files/register.txt";

	if((myFile = fopen(fileName, "r")) == NULL)
	{
		system("clear");
		textRed();
		printf("You need to have at least one movie registered.\n");
		resetText();
		return;
	}

	myFile = fopen(fileName, "r+");

  	int found = 0;
  	char line[200];

	memset(line, 0, sizeof(line));

	fseek(myFile, 0, SEEK_SET);

  	textYellow();
  	printf("\n     TITLE\t\tCODE\t\tRENTED?\n");
  	resetText();

  	int count = 1;

  	char title[200];
  	char code[10];
  	char status[10];
  	
  	int codeHelper;
  	int codeIndex = 0;

  	int statusHelper;
  	int statusIndex = 0;

  	while(fgets(line, sizeof(line), myFile))
  	{	  		
  		for(int x=0; x<sizeof(title); x++) //clear title
  			title[x] = '\0';

  		for(int x = 0; x<strlen(line); x++) //get movie title
  		{
  			if(line[x] == '|')
  				continue;
  			
  			title[x] = line[x];
  		}

  		for(int y=0; y<sizeof(code); y++) //clear code
  			code[y] = '\0';

  		for(int y=0; y<strlen(line); y++) //get code
  		{
  			if(line[y] == '|')
  			{
  				codeHelper = 1;
  			}

  			if(line[y] == ';')
  			{
  				codeHelper = 0;
  				continue;
  			}

  			if(codeHelper == 1)
  			{
  				code[codeIndex] = line[y+1];
  				
  				if(code[codeIndex] == ';')
  					code[codeIndex] = '\0';

  				codeIndex++;
  			}
  		}

  		for(int z=0; z<sizeof(status); z++) //clear status
  			status[z] = '\0';

  		for(int z=0; z<strlen(line); z++) //get status
  		{
  			if(line[z] == ';')
  			{
  				statusHelper = 1;
  			}

  			if(line[z] == '\n')
  			{
  				statusHelper = 0;
  				continue;
  			}

  			if(statusHelper == 1)
  			{
  				status[statusIndex] = line[z+1];
  				
  				if(status[statusIndex] == '\n')
  					status[statusIndex] = '\0';

  				statusIndex++;
  			}
  		}

  		if(count < 10)
	  		printf("\n00%d. %.10s\t\t%s\t%s", count, title, code, status); //print line content
  		else if(count >= 10 && count < 100)
  			printf("\n0%d. %.10s\t\t%s\t%s", count, title, code, status); //print line content
  		else if(count >= 100)
  			printf("\n%d. %.10s\t\t%s\t%s", count, title, code, status); //print line content
  		
  		count++;

  		codeHelper = 0;
  		codeIndex = 0;

  		statusHelper = 0;
  		statusIndex = 0;
	}

	printf("\n");
	fclose(myFile);
}

void rent()
{
	FILE *myFile;

	char fileName[25] = "files/register.txt";

	if((myFile = fopen(fileName, "r")) == NULL)
	{
		system("clear");
		textRed();
		printf("You need to have at least one movie registered. Backing to menu...\n");
		resetText();
		return;
	}

	myFile = fopen(fileName, "r+");

  	int found = 0;
  	char search[100];
  	char line[200];
  	char _haveToClean = '\0';
  	char newSearch;
  	char cpf[15];


  	do{
  		if(_haveToClean == 'y')
  		{
  			getchar();
  			system("clear");
  			_haveToClean = 'n';
  		}

  		printf("====== RENT MOVIE ======\n");

  		checkInfo();

  		//memset(search, 0, sizeof(search)); //clear search variable
  		memset(line, 0, sizeof(line)); //clear line variable

  		fseek(myFile, 0, SEEK_SET); //point to the beggining of the file

	  	printf("\nEnter the movie you would like to rent: ");
	  	__fpurge(stdin);
	  	fgets(search, sizeof(search), stdin); //get word to search
	  	strtok(search, "\n"); //remove \n that fgets insert

	  	int count = 1;

	  	char title[200];
	  	char code[10];
	  	char status[10];
	  	
	  	int codeHelper;
	  	int codeIndex = 0;

	  	int statusHelper;
	  	int statusIndex = 0;

	  	char editWhat[10];
	  	char newTitle[200];
	  	char willSave;

	  	while(fgets(line, sizeof(line), myFile)) //check every line of the file
	  	{
	  		for(int x=0; x<sizeof(title); x++) //clear title
	  			title[x] = '\0';

	  		for(int x = 0; x<strlen(line); x++) //get movie title
	  		{
	  			if(line[x] == '|')
	  				continue;
	  			
	  			title[x] = line[x];
	  		}

	  		for(int y=0; y<sizeof(code); y++) //clear code
	  			code[y] = '\0';

	  		for(int y=0; y<strlen(line); y++) //get code
	  		{
	  			if(line[y] == '|')
	  			{
	  				codeHelper = 1;
	  			}

	  			if(line[y] == ';')
	  			{
	  				codeHelper = 0;
	  				continue;
	  			}

	  			if(codeHelper == 1)
	  			{
	  				code[codeIndex] = line[y+1];
	  				
	  				if(code[codeIndex] == ';')
	  					code[codeIndex] = '\0';

	  				codeIndex++;
	  			}
	  		}

	  		for(int z=0; z<sizeof(status); z++) //clear status
	  			status[z] = '\0';

	  		for(int z=0; z<strlen(line); z++) //get status
	  		{
	  			if(line[z] == ';')
	  			{
	  				statusHelper = 1;
	  			}

	  			if(line[z] == '\n')
	  			{
	  				statusHelper = 0;
	  				continue;
	  			}

	  			if(statusHelper == 1)
	  			{
	  				status[statusIndex] = line[z+1];
	  				
	  				if(status[statusIndex] == '\n')
	  					status[statusIndex] = '\0';

	  				statusIndex++;
	  			}
	  		}

		  		if((strcmp(search, title) == 0 || strcmp(search,code) == 0) && checkDupeTitle(search, myFile) == 0) //check if there is a title/code with the word searched
	  		{

				found = 1;

		  		if(strcmp(status,"true") == 0)
		  		{
		  			textRed();
		  			system("clear");
		  			printf("The movie typed is already rented! Try again with another movie...\n");
		  			resetText();
		  			return;
		  		}
		  		else
		  		{
		  			textGreen();
		  			printf("\nMovie found!");
		  			resetText();
		  			strcpy(status, "true");
			  	}

				do
				{
				  	printf("\n\nAre you sure you want to rent this movie? Y/N\n");
			  		__fpurge(stdin);
			  		scanf("%s", &willSave); //get word to search

			  		if(willSave == 'y' || willSave == 'Y')
			  		{	
			  			char userCheck[500];

			  			FILE *users;
			  			users = fopen("files/rented.txt", "a");

			  			printf("\nUser name: ");
			  			char userName[50];
			  			__fpurge(stdin);
			  			fgets(userName, sizeof(userName), stdin);
			  			strtok(userName, "\n");

			  			system("clear");

			  			char buffer[30];
						struct timeval tv;

						time_t curtime;

						gettimeofday(&tv, NULL); 
						curtime=tv.tv_sec;

						strftime(buffer,30,"%m/%d/%Y-%T",localtime(&curtime));

			  			fprintf(users, "%s*%s;%s#%s\n",userName, title, code, buffer);			  			

			  			fclose(users);

			  			textYellow();
			  			printf("Movie '%s' rented on %s", title, buffer);
			  			printf(" to %s", userName);
			  			resetText();

						save("status", title, code, status, count, line); //call function to save the changes
			  		}
			  		else if(willSave == 'n' || willSave == 'N')
			  		{
			  			system("clear");
			  			textYellow();
			  			printf("Changes discarded!");
			  			resetText();
			  		}
			  		else
			  		{
			  			invalidDigit();
			  		}
				}while(willSave != 'y' && willSave != 'Y' && willSave != 'N' && willSave != 'n');
	  		}
	  		
	  		count++;

	  		codeHelper = 0;
	  		codeIndex = 0;

	  		statusHelper = 0;
	  		statusIndex = 0;
	  	}

	  	if(found==0 && checkDupeTitle(search, myFile) == 0) //if haven't found anything, show an error
	  	{
	  		textRed();
	  		printf("\n\nMovie not found! Try again or press CTRL + C to abort...\n");
	  		resetText();
	  		_haveToClean = 'y';
	  	}

	  	if(found == 1)
	  	{
	  		do
	  		{
		  		printf("\n\nWill you rent another movie? Y/N\n");
		  		__fpurge(stdin);
		  		scanf("%c", &newSearch);

		  		if(newSearch != 'y' && newSearch != 'Y' && newSearch != 'n' && newSearch != 'N'){
		  			system("clear");
		  			invalidDigit();
		  		}

		  		if(newSearch == 'y' || newSearch == 'Y')
		  		{
		  			fclose(myFile);
		  			myFile = fopen(fileName, "r+");
		  			found = 0;
		  			_haveToClean = 'y';
		  		}

	  		}while(newSearch != 'y' && newSearch != 'Y' && newSearch != 'n' && newSearch != 'N');
	  	}
  	}while(found==0 || checkDupeTitle(search, myFile) == 1);

  	system("clear");
}

void rentedMovies()
{
	printf("====== RENTED MOVIES ======\n\n");

	FILE *userFile;

	char fileName[25] = "files/rented.txt";

	if((userFile = fopen(fileName, "r")) == NULL)
	{
		system("clear");
		textRed();
		printf("You have no movies rented. \n");
		resetText();
		return;
	}

	userFile = fopen(fileName, "r+");

  	int found = 0;
  	char line[200];

	memset(line, 0, sizeof(line));

	fseek(userFile, 0, SEEK_SET);

  	textYellow();
  	printf("NAME\t\t\tTITLE \t\tCODE \t\tRENT DATE\n");
  	resetText();

  	int count = 1;

  	char name[50];
  	char title[200];
  	char code[10];
  	char date[10];
  	
  	int titleHelper;
  	int titleIndex = 0;

  	int codeHelper;
  	int codeIndex = 0;

  	int dateHelper;
  	int dateIndex = 0;

  	while(fgets(line, sizeof(line), userFile))
  	{	  		
  		for(int w=0; w<sizeof(name); w++)
  			name[w] = '\0';

  		for(int w=0; w<strlen(line); w++)
  		{
  			if(line[w] == '*')
  				continue;

  			name[w] = line[w];
  		}

  		for(int x=0; x<sizeof(title); x++) //clear code
  			title[x] = '\0';

  		for(int x=0; x<strlen(line); x++) //get code
  		{
  			if(line[x] == '*')
  			{
  				titleHelper = 1;
  			}

  			if(line[x] == ';')
  			{
  				titleHelper = 0;
  				continue;
  			}

  			if(titleHelper == 1)
  			{
  				title[titleIndex] = line[x+1];
  				
  				if(title[titleIndex] == ';')
  					title[titleIndex] = '\0';

  				titleIndex++;
  			}
  		}

  		for(int y=0; y<sizeof(code); y++) //clear code
  			code[y] = '\0';

  		for(int y=0; y<strlen(line); y++) //get code
  		{
  			if(line[y] == ';')
  			{
  				codeHelper = 1;
  			}

  			if(line[y] == '#')
  			{
  				codeHelper = 0;
  				continue;
  			}

  			if(codeHelper == 1)
  			{
  				code[codeIndex] = line[y+1];

  				if(code[codeIndex] == '#')
  					code[codeIndex] = '\0';
  				
  				if(code[codeIndex] == ';')
  					code[codeIndex] = '\0';

  				codeIndex++;
  			}
  		}

  		for(int z=0; z<sizeof(date); z++) //clear status
  			date[z] = '\0';

  		for(int z=0; z<strlen(line); z++) //get status
  		{
  			if(line[z] == '#')
  			{
  				dateHelper = 1;
  			}

  			if(line[z] == '\n')
  			{
  				dateHelper = 0;
  				continue;
  			}

  			if(dateHelper == 1)
  			{
  				date[dateIndex] = line[z+1];
  				
  				if(date[dateIndex] == '\n')
  					date[dateIndex] = '\0';

  				dateIndex++;
  			}
  		}

  		for(int i=0; i<15; i++)
  		{
  			if(strlen(name) < 15)
  				strcat(name, " ");

  			if(strlen(title) < 10)
  				strcat(title, " ");
  		}

	  	printf("\n%.15s\t\t%.10s\t%s\t%s", name, title, code, date); //print line content
  		
  		count++;

  		titleHelper;
  		titleIndex = 0;

  		codeHelper = 0;
  		codeIndex = 0;

  		dateHelper = 0;
  		dateIndex = 0;
	}

	printf("\n");
	fclose(userFile);


	__fpurge(stdin);
	getchar();
	system("clear");
}

void returnMovie()
{
	printf("====== RETURN MOVIES ======\n\n");

	FILE *userFile;

	char fileName[25] = "files/rented.txt";

	if((userFile = fopen(fileName, "r")) == NULL)
	{
		system("clear");
		textRed();
		printf("You have no movies rented. \n");
		resetText();
		return;
	}

	userFile = fopen(fileName, "r+");


}

void invalidDigit()
{
	textRed();
	printf("Digit invalid! Insert a valid digit or press CTRL + C to abort...\n");
	resetText();
}

void save(char *change, char *title, char *code, char *status, char *index, char *line)
{
	char newLine[200] = "";
	
	strcat(newLine, title);
	strcat(newLine, "|");
	strcat(newLine, code);
	strcat(newLine, ";");
	strcat(newLine, status);
	strcat(newLine, "\n");
		
	FILE *myFile;
	FILE *tempFile;

	char fileName[25] = "files/register.txt";
	char tempName[25] = "files/temp.txt";

	if((myFile = fopen(fileName, "r")) == NULL)
	{
		system("clear");
		textRed();
		printf("You need to have at least one movie registered. Backing to menu...\n");
		resetText();
		return;
	}

	myFile = fopen(fileName, "r+");

	fseek(myFile, 0, SEEK_SET);

	int count = 0;
	char fileLine[200];

	//int newLineCount = strlen(newLine)+1;

	while (fgets(fileLine, sizeof(fileLine), myFile))
	{
	    count = strlen(fileLine) + count;
    }

	fseek(myFile, 0, SEEK_SET);

	char fileContent[count];	

	strcpy(fileContent, "a");

	memset(fileContent, 0, sizeof(fileContent));

	while(fgets(fileLine, sizeof(fileLine), myFile)) //check every line of the file
	{
		if(strcmp(line, fileLine) ==  0)
		{
			strcat(fileContent, newLine);
		}
		else
		{
			strcat(fileContent, fileLine); //when finish the loop, fileContent will have the new whole file content
		} 
	}

	fclose(myFile);

	tempFile = fopen(tempName, "a");
	fprintf(tempFile, "%s", fileContent);
	fclose(tempFile);

	int del;
	int rnm;

	del = remove(fileName);
	rnm = rename(tempName, fileName);

	getchar();

	if(del == 0 && rnm == 0)
	{
		textGreen();
		printf("\nSaved successfully!");
		resetText();		
	}
	else
	{
		textRed();
		printf("Something went wrong... Aborting...");
		resetText();
		return;
	}
}

void textGreen()
{
	printf("\033[0;32m");
}

void textRed()
{
	printf("\033[0;31m");
}

void textYellow()
{
	printf("\033[0;33m");
}

void resetText()
{
	printf("\033[0m");
}

int checkDupeTitle(char *search, FILE *myFile)
{
  	int found = 0;
  	char line[200];

	memset(line, 0, sizeof(line)); //clear line variable

	fseek(myFile, 0, SEEK_SET); //point to the beggining of the file

  	char title[200];

  	while(fgets(line, sizeof(line), myFile)) //check every line of the file
  	{
  		for(int x=0; x<sizeof(title); x++) //clear title
  			title[x] = '\0';

  		for(int x = 0; x<strlen(line); x++) //get movie title
  		{
  			if(line[x] == '|')
  				continue;
  			
  			title[x] = line[x];
  		}

	  		if(strcmp(search, title) == 0) //check if there is a title with the word searched
  		{
			found++;
		}
  	}

  	if(found > 1)
  	{
  		system("clear");
  		textRed();
  		printf("More than one movie has this title, you must search by movie ID...\n");
  		resetText();
  		return 1;
  	}
  	else
  	{
  		return 0;
  	}

  	system("clear");
}