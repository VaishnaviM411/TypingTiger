#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
typedef struct USER
{
	char name[20];
	float acc;
	float speed;
	float score;
}USER;
void level();
void Highscore();
void ins();
void back_to_menu();
void score();
void username();
USER user;
void ins()
{
	system("cls");
	system("color C0");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tInstructions\n\n\n");
	char s[100];
	FILE *fp;
	fp=fopen("ins.txt","r");
	while(!feof(fp))
	{
		fgets(s,100,fp);
		printf("\t\t\t\t\t\t");
		puts(s);
	}
	fclose(fp);
	return;
}
int navigate(int n,...)
{
	char spc[4]={"   "};
	char arw[4]={"-->"};
	char ch;
	int cur=0;
	int i;
	char **opt,**ptr;
	opt=(char**)malloc(n*sizeof(char*));
	ptr=(char**)malloc(n*sizeof(char*));
	*(ptr+0)=arw;
	for(i=1;i<n;i++)
	{
		*(ptr+i)=spc;
	}
	va_list a;
	va_start(a,n);
	
	for(i=0;i<n;i++)
	{
		*(opt+i)=va_arg(a,char*);
		printf("\t\t\t\t\t\t\t\t\t\t\t\t%s %s\n\n",*(ptr+i),*(opt+i));
	}
	*(ptr+0)=spc;
	ch=getch();
	while(ch!=13)
	{
		system("cls");
		if(n==4)
			printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tWelcome to VFP!!!\n\n\n");
		if(n==3)
			printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tLevel\n\n\n");
		if(ch==72)
			cur=(cur+n-1)%n;
		else if(ch==80)
			cur=(cur+1)%n;
		*(ptr+cur)=arw;
		for(i=0;i<n;i++)
		{
			printf("\t\t\t\t\t\t\t\t\t\t\t\t%s %s\n\n",*(ptr+i),*(opt+i));
		}
		*(ptr+cur)=spc;
		ch=getch();
	}
	return cur;
}

void username()
{
	int flg=0;
	FILE *fp;
	system("cls");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tEnter Username\n\n\t\t\t\t\t\t\t\t\t\t\t\t");
	scanf("%s",user.name);
	level();
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tSCORE\n\n\t\t\t\t\t\t\t\t\t\t\t\t");
	printf("Acccuracy %.2f  Speed %.0f W/min\n\n",user.acc,user.speed);
	printf("\t\t\t\t\t\t\t\t\t\t\t\tScore: %.0f Correct Words per minute\n\n",user.score);
	if(user.score<20)
		printf("\n\t\t\t\t\t\t\t\t\t\t\t\tGood!!! You need to practice\n");
	if(user.score>=20&&user.score<=30)
		printf("\n\t\t\t\t\t\t\t\t\t\t\t\tVery Good!!! Keep practicing\n");
	else if(user.score>30&&user.score<=40)
		printf("\n\t\t\t\t\t\t\t\t\t\t\t\tExecellent!!! Keep it up!\n");
	else if(user.score>40&&user.score<=50)
		printf("\n\t\t\t\t\t\t\t\t\t\t\t\tOutstanding!!! You're reaching professional level!\n");
	else if(user.score>50)
		printf("\n\t\t\t\t\t\t\t\t\t\t\t\tOutstanding!!! You've reached professional level!\n");
	PlaySound("KidsCheer.wav",NULL,SND_SYNC);
	Highscore();
	fp=fopen("score.dat","ab+");
	fseek(fp,0,SEEK_END);
	fwrite(&user,sizeof(USER),1,fp);
	fclose(fp);
	return;
}
void level()
{
	system("cls");
	FILE *fp;
	int n;
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tLevel\n\n\n");
	n=navigate(3,"Beginner","Intermediate","Advanced");
	system("cls");
	system("color C0");
	int rndm;
	int l;
	if(n==0)
		l=1;
	else if(n==1)
		l=4;
	else if(n==2)
		l=7;
	srand(time(0));
	rndm=l+(rand()%3);
	switch(rndm)
	{
		case 1: fp=fopen("b1.txt","r");
				break;
		case 2: fp=fopen("b2.txt","r");
				break;
		case 3: fp=fopen("b3.txt","r");
				break;
		case 4: fp=fopen("i1.txt","r");
				break;
		case 5: fp=fopen("i2.txt","r");
				break;
		case 6: fp=fopen("i3.txt","r");
				break;
		case 7: fp=fopen("a1.txt","r");
				break;
		case 8: fp=fopen("a2.txt","r");
				break;
		case 9: fp=fopen("a3.txt","r");
				break;
	}
	clock_t start, end;
	double time=0;
	float wrong=0,cnt=0;
	char s[250];
	char input[15],word[15];
	while(!feof(fp))
	{
		fgets(s,250,fp);
		puts(s);
	}
	printf("\n");
	fseek(fp,0,SEEK_SET);
	while(!feof(fp))
	{
		fscanf(fp,"%s",word);
		cnt++;
		start=clock();
		scanf("%s",input);
		end=clock();
		time=time+((end-start)/CLOCKS_PER_SEC);
		if(strcmp(word,input)==0)
			continue;
		else
			wrong++;
	}
	fclose(fp);
	user.acc=((cnt-wrong)/cnt)*100;
	user.speed=(cnt*60)/time;
	user.score=(cnt-wrong)*60/time;
	return;
}
void back_to_menu()
{
	int op;
	printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tMenu: 1 | Exit: 0");
	scanf(" %d",&op);
	switch(op)
	{
		case 1: main();
				break;
		case 0: exit(0);
	}
	return;
}
void score()
{
	FILE *fp;
	USER usern;
	system("cls");
	system("color C0");
	fp=fopen("score.dat","rb");
	if(fp==NULL)
		printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tNo users yet\n");
	else
	{
		printf("\n\n\n\n\n\t\tUsername\t\tAccuracy\t\tSpeed(w/min)\t\tScore(w/min)\n\n");
		while(1)
		{
			fread(&usern,sizeof(USER),1,fp);
			if(feof(fp))
				break;
			printf("\n\t\t%-20s\t\t%-6.2f %\t\t%4.2f w/min\t\t%4.2f w/min\n",usern.name,usern.acc,usern.speed,usern.score);
		}
	}
	fclose(fp);
	return;
}
void Highscore()
{
	float highscore;
	FILE *fp;
	fp=fopen("highscore.txt","r");
	if(fp)
	{
		fscanf(fp,"%f",&highscore);
		if(highscore<user.score)
		{
			fclose(fp);
			highscore=user.score;
			printf("\n\t\t\t\t\t\t\t\t\t\t\t\tCONGRATULATIONS!!! We've got a new highscore!\n");
			PlaySound("Ta Da.wav",NULL,SND_SYNC);
			fp=fopen("highscore.txt","w");
			fprintf(fp,"%f\n",highscore);
		}
	}
	else
	{
		fclose(fp);
		fp=fopen("highscore.txt","w");
		highscore=user.score;
		fprintf(fp,"%f\n",highscore);
	}	
	fclose(fp);
	return;
}

