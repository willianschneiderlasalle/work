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
	printf("2 - Edit an existent movie\n");
	printf("3 - Search movie by title or ID\n");
	printf("4 - Check movie info\n");
	printf("5 - Generate TXT report\n");
	printf("6 - Generate PDF report \n");
	printf("7 - Exit\n\n");

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
			editMovie();
			break;
		case '3':
			system("clear");
			searchMovie();
			break;
		case '4':
			system("clear");
			checkInfo();
			break;
		case '5':
			system("clear");
			generateTXT();
			break;
		case '6':
			system("clear");
			generatePDF();
			break;
		case '7':
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