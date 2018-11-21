#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h> //allow __fpurge - clears buffer
#include "funcs.h"

int menu();

int main(int argc, char *argv[])
{
	system("clear");

	menu();

	return 0;
}

int menu()
{
	char menuChoice;

	printf("====== VIDEO RENTAL SOFTWARE ======\n\n");
	
	printf("1 - Register new movie\n");
	printf("2 - Rent movie\n");
	printf("3 - Edit an existent movie\n");
	printf("4 - Search movie by title or ID\n");
	printf("5 - Check all movies info\n");
	printf("6 - Movies rented list \n");
	printf("7 - Return movie \n");
	printf("8 - Exit\n\n");

	__fpurge(stdin);
	scanf("%c", &menuChoice);

	switch(menuChoice)
	{
		case '1':
			system("clear");
			registerMovie();
			break;
		case '2':
			system("clear");
			rent();
			break;
		case '3':
			system("clear");
			editMovie();
			break;
		case '4':
			system("clear");
			searchMovie();
			break;
		case '5':
			system("clear");
			printf("====== MOVIES REGISTERED ======\n");
			checkInfo();
			__fpurge(stdin);
  			getchar();
  			system("clear");
			break;
		case '6':
			system("clear");
			rentedMovies();
			break;
		case '7':
			system("clear");
			returnMovie();
		case '8':
			printf("Exiting...\n");
			return 0;
			break;
		default:
			system("clear");
			textRed();
			invalidDigit();
			resetText();
			menu();
			break;
	}
	menu();
	return 0;
}