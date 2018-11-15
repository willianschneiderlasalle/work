#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

void menu();

int main(int argc, char *argv[])
{
	system("clear");

	menu();

	return 0;
}

void menu()
{
	char menuChoice;

	printf("====== VIDEO RENTAL SOFTWARE ======\n\n");
	
	printf("1 - Register new movie\n");
	printf("2 - Edit an existent movie\n");
	printf("3 - Search movie by title or ID\n");
	printf("4 - Check movie info\n");
	printf("5 - Generate TXT report\n");
	printf("6 - Generate PDF report \n\n");

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
		default:
			system("clear");
			printf("Digit invalid! Insert a valid digit or press CTRL + C to exit...\n\n");
			menu();
			break;
	}

}