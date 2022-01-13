#include<iostream.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<iomanip.h>
#include<process.h>
struct deck
{
	int rank;
	char suit[10];
}d[52];
void CreateDeck(int i, int j)
{
	static int k=0;
	d[k].rank=i;
	switch(j)
	{
		case 0 : strcpy(d[k].suit,"Hearts");
					break;
		case 1 : strcpy(d[k].suit,"Diamonds");
					break;
		case 2 : strcpy(d[k].suit,"Spades");
					break;
		case 3 : strcpy(d[k].suit,"Clubs");
					break;
	}
	k++;
}
void ShowDeck()
{
		for(int i=0;i<52;i++)
		{cout<<d[i].rank<<" of ";
		 puts(d[i].suit);
		 cout<<endl;
		}
}


void main()
{
		for(int j=0; j<4; j++)
				{
					for(int i=1; i<14; i++)
						{
							CreateDeck(i,j);
						}
				}
cout<<"Your Deck is being created.....Press Enter to continue\n";
getch();
cout<<"Your deck is:\n";
ShowDeck();
}

