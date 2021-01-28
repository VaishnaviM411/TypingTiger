#include<stdio.h>
#include"pro1.h"
int main()
{
	int op;
	system("cls");
	system("color 4F");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tWelcome to VFP!!!\n\n\n");
	op=navigate(4,"Practice","Instruction","Score","Exit");
	switch(op)
	{
		case 0: system("cls");
				username();
				back_to_menu();
				break;
		case 1: ins();
				back_to_menu();
				break;
		case 2: score();
				back_to_menu();
				break;
		case 3: exit(0);
	}
	return 0;
}
