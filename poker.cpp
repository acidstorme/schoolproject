#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<iomanip.h>
#include<process.h>

int N=52;
int currentbet=0;
int hicard[5];
char tmps[10];
int hcstrt[5];
int hcflush[5];
int hcko3[5];
int hcko4[5];
int hcp[5];
int hands[5];
int loglines=0;
int fp,f1,f2,f3,f4;

class Move
{
	public:
	char move[15];
	void show() {cout<<move;}
}M;

struct deck
{
	int rank;
	char suit[10];
}d[53];

struct tempcard
{
	int tempr;
	char temps[10];
}tc;

struct PlayerHand
{
	tempcard card1, card2;
}phand;

struct BotHand
{
	tempcard card1, card2;
}bhand[4];

struct Tablecards
{
	int rank;
	char suit[10];
}tcard[5];

void CreateDeck()
{
			for(int j=0; j<4; j++)
				{
					for(int i=1; i<14; i++)
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
				}
}

void ShowDeck()
{
		for(int i=0;i<N;i++)
		{cout<<d[i].rank<<" of ";
		 puts(d[i].suit);
		 cout<<endl;
		}
}

void ShuffleDeck()
{ int c1;
 randomize();
 for(int i=0; i<N; i++)
	{
		c1=random(N);
		tc.tempr=d[c1].rank;
		strcpy(tc.temps,d[c1].suit);
		d[c1].rank=d[i].rank;
		strcpy(d[c1].suit,d[i].suit);
		d[i].rank=tc.tempr;
		strcpy(d[i].suit,tc.temps);
	}
}

void Burn()
{
	for(int i=0;i<N;i++)
		{
			d[i].rank=d[i+1].rank;
			strcpy(d[i].suit,d[i+1].suit);
		}
	N--;
}

void Deal(int n)
{
	phand.card1.tempr=d[0].rank;
	strcpy(phand.card1.temps,d[0].suit);
	Burn();
	for(int i=0; i<n; i++)
		{
			bhand[i].card1.tempr=d[0].rank;
			strcpy(bhand[i].card1.temps,d[0].suit);
			Burn();
		}
	phand.card2.tempr=d[0].rank;
	strcpy(phand.card2.temps,d[0].suit);
	Burn();
	for(i=0; i<n; i++)
		{
			bhand[i].card2.tempr=d[0].rank;
			strcpy(bhand[i].card2.temps,d[0].suit);
			Burn();
		}
}

void ShowMyHand()
{
	cout<<"\t\t\t  "<<phand.card1.tempr<<" of    "<<phand.card2.tempr<<" of"<<endl;
	cout<<"\t\t\t "<<phand.card1.temps<<"   "<<phand.card2.temps<<endl;
}

void ShowBotHand(int x)
{
	cout<<"Bot no. "<<(x+1)<<"'s hand is :\n";
	cout<<bhand[x].card1.tempr<<" of "<<bhand[x].card1.temps<<endl;
	cout<<bhand[x].card2.tempr<<" of "<<bhand[x].card2.temps<<endl;
}


void AssignHiCard()
{
	int tmp,i,j,k;
	if(phand.card1.tempr>phand.card2.tempr)
			{tmp=phand.card1.tempr;
			 strcpy(tmps,phand.card1.temps);
			}
	else {tmp=phand.card2.tempr;
			strcpy(tmps,phand.card2.temps);
		  }
	for(i=0;i<5;i++)
		{
			if(tmp<tcard[i].rank)
			{tmp=tcard[i].rank;
			strcpy(tmps,tcard[i].suit); }
		}

	hicard[0]=tmp;

	for(i=1,j=0;i<5,j<4;i++,j++)
		{
			if(bhand[j].card1.tempr>bhand[j].card2.tempr)
					tmp=bhand[j].card1.tempr;
			else  tmp=bhand[j].card2.tempr;
			for(k=0;k<5;k++)
				{
					if(tmp<tcard[k].rank)
					tmp=tcard[k].rank;
				}
			hicard[i]=tmp;

		}
}

void CreateStash()
{
	ofstream ofile("Stash.txt", ios::out|ios::noreplace);
	ofile<<"10000\n10000\n10000\n10000\n10000\n";
	ofile.close();
}

void ModifyStash(int k, int n)
{
	char line[10];
	int stash;
	ifstream ifile("Stash.txt", ios::in);
	for(int i=0;i<n;i++)
	{ifile.getline(line,10,'\n');}
	ifile>>stash;
	ofstream ofile("Stash.txt", ios::out|ios::ate);
	stash=stash-k;															//add an int totalbet in func to decrease/increase stash value
	for(i=0;i<n;i++)
	{ifile.getline(line,10,'\n');}
	ofile<<stash<<endl;
	ifile.close();
	ofile.close();
}

void ShowStash(int n)
{
	char line[10];
	int stash;
	ifstream ifile("Stash.txt", ios::in);
	cout<<"Your current stash is :\n";
	for(int i=0;i<n;i++)
	{ifile.getline(line,10);}
	ifile>>stash;
	cout<<stash<<endl;
	ifile.close();
}



void showtablerank(int x)
{
	if(tcard[x].rank==0)
	{
		cout<<"  ";
	}
	else
	{
		if(tcard[x].rank>=10 && tcard[x].rank<=13)
			{
				cout<<tcard[x].rank;
			}
		else if(tcard[x].rank>=1 && tcard[x].rank<=9)
			{
				cout<<tcard[x].rank<<" ";
			}
	}
}

void showtablesuit(int y)
{
	if(tcard[y].rank==0)
	{
		cout<<"\t";
	}
	else
	{
		if(strcmp(tcard[y].suit,"Hearts")==0||strcmp(tcard[y].suit,"Spades")==0)
			{
				cout<<" "<<tcard[y].suit<<" ";
			}

		else if(strcmp(tcard[y].suit,"Clubs")==0)
				{
					cout<<" "<<tcard[y].suit<<"  ";
				}
		else if(strcmp(tcard[y].suit,"Diamonds")==0)
				{
					cout<<tcard[y].suit;
				}

	}
}





void CreatePot()
{
	int x=0;
	ofstream ofile("Pot.txt", ios::out);
	ofile<<x;
	ofile.close();
}

void AddPot(int b)
{
	int x;
	ifstream ifile("Pot.txt", ios::in);
	ifile>>x;
	ifile.close();
	ofstream ofile("Pot.txt", ios::out|ios::trunc);
	int n=x+b;
	ofile<<n;
	ofile.close();
}

void InputBet(int bet, int n)
{
	int x;
	if(bet==-1)
		{cout<<"Please enter your bet: 100/200/500";
		 cin>>x;
		 bet=x;
		}
	currentbet=bet;
	AddPot(bet);
	ModifyStash(bet,n);
}

void ShowPot()
{
	int x;
	ifstream ifile("Pot.txt", ios::in);
	ifile>>x;
	if(x>=0&&x<10)
		 {
			cout<<" "<<x<<"      ";
		 }
		else if(x>=10&&x<100)
				{
					cout<<" "<<x<<"     ";
				}
			else if(x>=100&&x<1000)
					{
						cout<<" "<<x<<"    ";
					}
						else if(x>=1000&&x<10000)
							{
								cout<<" "<<x<<"   ";
							}
}

void UpdateLog(int ch, int player)
{
	Move M;
	ofstream ofile("LOG.dat",ios::out|ios::ate|ios::binary);
	if(ch==1)
	{
	if(player==0)
	{strcpy(M.move,"Player called! ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==1)
	{strcpy(M.move,"Bot 1 called!  ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==2)
	{strcpy(M.move,"Bot 2 called!  ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==3)
	{strcpy(M.move,"Bot 3 called!  ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==4)
	{strcpy(M.move,"Bot 4 called!  ");
	 ofile.write((char*)&M,sizeof(M));}
	}
	if(ch==2)
	{
	if(player==0)
	{strcpy(M.move,"Player raised! ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==1)
	{strcpy(M.move,"Bot 1 raised!  ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==2)
	{strcpy(M.move,"Bot 2 raised!  ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==3)
	{strcpy(M.move,"Bot 3 raised!  ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==4)
	{strcpy(M.move,"Bot 4 raised!  ");
	 ofile.write((char*)&M,sizeof(M));}
	}
	if(ch==3)
	{
	if(player==0)
	{strcpy(M.move,"Player folded! ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==1)
	{strcpy(M.move,"Bot 1 folded!  ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==2)
	{strcpy(M.move,"Bot 2 folded!  ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==3)
	{strcpy(M.move,"Bot 3 folded! ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==4)
	{strcpy(M.move,"Bot 4 folded!  ");
	 ofile.write((char*)&M,sizeof(M));}
	}
	if(ch==4)
	{
	if(player==0)
	{strcpy(M.move,"Player - blind!");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==1)
	{strcpy(M.move,"Bot 1 - blind! ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==2)
	{strcpy(M.move,"Bot 2 - blind! ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==3)
	{strcpy(M.move,"Bot 3 - blind! ");
	 ofile.write((char*)&M,sizeof(M));}
	if(player==4)
	{strcpy(M.move,"Bot 4 - blind! ");
	 ofile.write((char*)&M,sizeof(M));}
	}
	loglines++;
	ofile.close();
}



void Flop()
{  int i=0;
	Burn();
	while(i<3)
			{
				tcard[i].rank=d[0].rank;
				strcpy(tcard[i].suit,d[0].suit);
				Burn();
				i++;
			}
}

void RivTurn(int x)
{
	Burn();
	Burn();
	tcard[x].rank=d[0].rank;
	strcpy(tcard[x].suit,d[0].suit);
	Burn();
}

void ShowTableCards()
{
	for(int i=0; i<5; i++)
		{
			cout<<tcard[i].rank<<" of "<<tcard[i].suit<<"\t";
		}
}


void fdisplay()
{

	Flop();
	RivTurn(3);
	RivTurn(4);

	clrscr();
	cout<<"\t.----------------------------------------------.\n";         // 6 \t's, 48 dashes
	cout<<"       (\t\t\t\t\t\t) \n";
	cout<<"      (\t\t\t\t\t\t\t ) \n";
	cout<<"     (\t\t\t\t\t\t\t  ) \n";
	cout<<"     |\t       ";
	showtablerank(0);
	cout<<"    \t       ";
	showtablerank(2);
	cout<<"    \t       ";
	showtablerank(4);
	cout<<"         | \n";                         // eol 1              \t is 8 spaces
	cout<<"     |\t     ";
	showtablesuit(0);
	cout<<"  ";
	showtablerank(1);
	cout<<"    ";
	showtablesuit(2);
	cout<<"  ";
	showtablerank(3);
	cout<<"    ";
	showtablesuit(4);
	cout<<"     | \n";                           //eol2
	cout<<"     |\t\t     ";
	showtablesuit(1);
	cout<<"\t     ";
	showtablesuit(3);
	cout<<"\t          | \n";                         //eol3
	cout<<"     (\t\t\t\t\t\t\t  ) \n";
	cout<<"      (\t\t\t  Pot=";
	ShowPot();
	cout<<"  \t\t ) \n";
	cout<<"       (\t\t\t\t\t\t) \n";
	cout<<"\t'----------------------Me----------------------'\n";
	ShowMyHand();
	cout<<"\n\n";


}




void display(int h)
{
	int i,x=(5*sizeof(M));
	char line[15];
	ifstream ifile("LOG.dat",ios::in|ios::binary|ios::ate);

	cout<<"\t.----------------------------------------------.\n";         // 6 \t's, 48 dashes
	cout<<"       (\t\t\t\t\t\t)    ";

	cout<<".---------------.\n";

	cout<<"     BOT 4     \t\t\t\t\t       BOT 1";

	cout<<" |    GameLog    |\n";

	cout<<"     (\t\t\t\t\t\t\t  ) ";

	cout<<" '---------------'\n";

	cout<<"     |\t       ";
	showtablerank(0);
	cout<<"    \t       ";
	showtablerank(2);
	cout<<"    \t       ";
	showtablerank(4);
	cout<<"         | ";                         // eol 1              \t is 8 spaces

	cout<<" |";

	if(loglines>5)
	{
		ifile.seekg(-x,ios::end);
	}
	ifile.read((char*)&M,sizeof(M));
	M.show();
	cout<<" |"<<endl;

	cout<<"     |\t     ";
	showtablesuit(0);
	cout<<"  ";
	showtablerank(1);
	cout<<"    ";
	showtablesuit(2);
	cout<<"  ";
	showtablerank(3);
	cout<<"    ";
	showtablesuit(4);
	cout<<"          | ";                           //eol2

	cout<<" |";

	ifile.read((char*)&M,sizeof(M));
	M.show();

	cout<<" |"<<endl;


	cout<<"     |\t\t     ";
	showtablesuit(1);
	cout<<"\t     ";
	showtablesuit(3);
	cout<<"\t          | ";                         //eol3

	cout<<" |";

	ifile.read((char*)&M,sizeof(M));
	M.show();

	cout<<" |"<<endl;



	cout<<"     (\t\t\t\t\t\t\t  )";

	cout<<"  |";

	ifile.read((char*)&M,sizeof(M));
	M.show();

	cout<<" |"<<endl;


	cout<<"     BOT 3     \t\t    Pot=";
	ShowPot();
	cout<<"\t       BOT 2 ";

	cout<<"|";

	ifile.read((char*)&M,sizeof(M));
	M.show();

	cout<<" |"<<endl;


	cout<<"       (\t\t\t\t\t\t)    '---------------'\n";
	cout<<"\t'----------------------Me----------------------'\n";
	ShowMyHand();
	cout<<"\n\t\t\tCurrent ";

		if(h==0) {cout<<"  "<<hicard[0]<<" of ";
					 cout.write(tmps,10);}
		else if(h==2) cout<<"  One Pair      ";
		else if(h==3) cout<<"  Two Pair      ";
		else if(h==4) cout<<"  Three of a Kind";
		else if(h==5) cout<<"  Straight      ";
		else if(h==6) cout<<"  Flush         ";
		else if(h==7) cout<<"  Full House    ";
		else if(h==8) cout<<"  Four of a Kind";
		else if(h==9) cout<<"  Straight Flush";
	cout<<"\n\t\t\t Hand \t\t\t\n";
	cout<<"\n";


}


int ConvertSuit(char suit[])
{
	if(strcmp(suit,"Hearts")==0)
				return(1);
	else if(strcmp(suit,"Spades")==0)
				return(2);
	else if(strcmp(suit,"Diamonds")==0)
				return(3);
	else if(strcmp(suit,"Clubs")==0)
				return(4);
	else return(0);
}

void SortCards(int a[],int b[])                    //while calling function, enter the array to sort wrt first
{
	int small, pos, tmp1, tmp2;
	for(int i=0;i<7;i++)
	{
		small=a[i];
		pos=i;
		for(int j=i+1;j<7;j++)
			{
				if(a[j]<small)
				{small=a[j]; pos=j;}
			}
		tmp1=a[i];
		a[i]=a[pos];
		a[pos]=tmp1;
		tmp2=b[i];
		b[i]=b[pos];
		b[pos]=tmp2;
	}

}


int EvaluateHand(int player, int rank1, char suit1[], int rank2, char suit2[]) //add parameters(rank,suit) that take each players cards and add them to the function.
{
	int suits[7],ranks[7],i,j,straight=0,full=0,ko3=0,t3=0,ko4=0,t4=0,noofpairs=0,t2=0,tst=0,tf=0,flush=0, stflush=0;

		suits[0]=ConvertSuit(suit1);                                         //storing cards to arrays
		ranks[0]=rank1;
		suits[1]=ConvertSuit(suit2);
		ranks[1]=rank2;
		for(i=2,j=0;i<7,j<5;i++,j++)
			{
				suits[i]=ConvertSuit(tcard[j].suit);
				ranks[i]=tcard[j].rank;
			}

		SortCards(ranks,suits);                                   //sort cards according to rank

		for(i=0;i<7;i++)                                                   //check for 4 of a kind, 3 of a kind, and pairs
			{

				if(ranks[i]!=0 && ranks[i-1]!=ranks[i] && ranks[i]==ranks[i+1] && ranks[i]!=ranks[i+2])
						 { noofpairs+=1;
							t2=ranks[i];
						  if(t2>=hcp[player])
							hcp[player]=t2;
							}
				if(ranks[i]!=0 && ranks[i-1]!=ranks[i] && ranks[i]==ranks[i+1] && ranks[i]==ranks[i+2] && ranks[i]!=ranks[i+3])
					{ko3=1;
					t3=ranks[i];
						if(t3>=hcko3[player])
							hcko3[player]=t3;
							}
				if(ranks[i]!=0 && ranks[i-1]!=ranks[i] && ranks[i]==ranks[i+1] && ranks[i]==ranks[i+2] && ranks[i]==ranks[i+3] && ranks[i]!=ranks[i+4])
					{ko4=1;
					t4=ranks[i];
						if(t4>=hcko4[player])
							hcko4[player]=t4;
							}

				}




		 if(ko3==1&&noofpairs==1)                        //checking fullhouse
			{
				full=1;
			}

		 for(i=0;i<7;i++)                              //checking straight
			{
				if(ranks[i]!=0 && ranks[i-1]!=ranks[i] && ranks[i]==(ranks[i+1]-1) && ranks[i]==(ranks[i+2]-2) && ranks[i]==(ranks[i+3]-3) && ranks[i]==(ranks[i+4]-4) && ranks[i]!=(ranks[i+5]-5))
				{straight=1;
				 tst=ranks[i+4];
						if(tst>=hcstrt[player])
							hcstrt[player]=tst;
				 }

		 if(straight==1)                                 //checking for straight flush after straight is true
			{
				for(i=0;i<7;i++)
			{

				if(ranks[i]!=0 && ranks[i]==(hcstrt[player]-4) && suits[i-1]!=ranks[i] && suits[i]==suits[i+1] && suits[i]==suits[i+2] && suits[i]==suits[i+3] && suits[i]==suits[i+4] && suits[i]!=suits[i+5])
					{  stflush=1;}

			}
			}


		 SortCards(suits,ranks);                      //sorting cards according to suits

		 for(i=0;i<7;i++)                              //checking flush
			{

				if(ranks[i]!=0 && suits[i-1]!=ranks[i] && suits[i]==suits[i+1] && suits[i]==suits[i+2] && suits[i]==suits[i+3] && suits[i]==suits[i+4] && suits[i]!=suits[i+5])
					{  flush=1;
						tf=ranks[i+4];
						if(tf>=hcflush[player])
							hcflush[player]=tf;
					}
			}
		 }

				if(stflush==1)
					 return(9);
				if(ko4==1)
					 return(8);
				if(full==1)
					 return(7);
				if(flush==1)
					 return(6);
				if(straight==1)
					 return(5);
				if(ko3==1)
					 return(4);
				if(noofpairs==2)
					 return(3);
				if(noofpairs==1)
					 return(2);

				return(0);



}

int DecideWinner(int a, int b, int c, int d, int e)
{
	int winner=0;
	if(a>winner)	winner=0;
	if(b>winner)	winner=1;
	if(c>winner)	winner=2;
	if(d>winner)	winner=3;
	if(e>winner)	winner=4;

	return(winner);
}

int MyTurn()
{
	int choice(0);
	cout<<"\t\t   .------------------------.   \t\n";
	cout<<"\t\t   |    \t\t    |\t\n";
	cout<<"\t\t   |  1.Check/Call 2.Raise  |\t\n";
	cout<<"\t\t   |    \t\t    |\t\n";
	cout<<"\t\t   |         3.Fold         |\t\n";
	cout<<"\t\t   |    \t\t    |\t\n";
	cout<<"\t\t   `------------------------`   \t\n";
	cout<<"\t\t\t Choice: ";
	cin>>choice;
	return(choice);
}

int BotChoice(int p)
{
	 int i=1, ar[25]={1,2,3,1,1,2,3,2,1,1,1,2,1,2,1,1,1,1,1,1,2,1,1,1,2}, arr[20]={50,50,50,100,100,100,50,50,500,100,200,200,100,50,200,200,100,50,500,200}, r=0;
	 randomize();
	 r=random(25);
	 if(ar[r]==2)
	 {
	 r=random(20);
	  while(i)
	  {if(currentbet<=arr[r])
	  {
		InputBet(arr[r],p);
		UpdateLog(3,p);
		return(0);
	  }
     }
	 }
	 else return(ar[r]);
}

int Play(int n, int p)
{
	if(n!=0)
	{
	switch(n)
		{
			case 1 : InputBet(currentbet,p);
						break;
			case 2 : InputBet(-1,p);
						break;
			case 3 :	return(1);
		}
	}
	return(0);
}

void Round(int roundno)
{
	int X=0, ch, call1=0,call2=0,call3=0,call4=0,call5=0, pass=0;
	 ofstream ofile("LOG.txt",ios::out|ios::app);


	  if(roundno==0)
	  {
		cout<<"Commencing preflop betting...\n";
		getch();
	  }
	  else
	  {
		cout<<"Round "<<roundno<<"....\n";
		getch();
	  }

	  do
	  {

		if(call1!=1)
	  { cout<<"Bot 1's Turn\n";	getch();
		if(f1!=1)
	  {
			if(roundno==0 && pass==0)
				{
					InputBet(50,1);                              //small blind
					call1=0;
					UpdateLog(4,1);
					clrscr();
					display(hands[0]);
					getch();
				}
			else if(roundno==0 && pass==1)
				{
					InputBet(50,1);
					clrscr();
					display(hands[0]);
					UpdateLog(1,1);
					call1=1;
					getch();
				}
			else
			{
			ch=BotChoice(1);                                   //bot1 choosing
			UpdateLog(ch,1);
			if(ch==2)
			{
			  call1=1;
			  call2=0;
			  call3=0;
			  call4=0;
			  call5=0;
			}
			else {call1=1;}
			f1=Play(ch,1);
			clrscr();
			display(hands[0]);
			getch();
			}
	  }
	  else { call1=1; }
	  }


		if(call2!=1)
	  { cout<<"Bot 2's Turn\n";  getch();
		if(f2!=1)
	  {
			if(roundno==0 && pass==0)
				{
					InputBet(100,2);                                  //large blind
					UpdateLog(4,2);
					clrscr();
					display(hands[0]);
					call2=1;
					getch();
				}
			else
			{
			ch=BotChoice(1);                                   //bot2 choosing
			UpdateLog(ch,2);
			if(ch==2)
			{
			  call1=0;
			  call2=1;
			  call3=0;
			  call4=0;
			  call5=0;
			}
			else call2=1;
			f2=Play(ch,2);
			clrscr();
			display(hands[0]);
			getch();
			}
		}
	  else call2=1;
		}

	  if(call3!=1)
	  { cout<<"Player's Turn\n";  getch();
	  if(fp!=1)
	  {
			ch=MyTurn();                                      //player choosing
			UpdateLog(ch,0);
			if(ch==2)
			{
			  call1=0;
			  call2=0;
			  call3=1;
			  call4=0;
			  call5=0;
			}
			else call3=1;
			fp=Play(ch,0);
			clrscr();
			display(hands[0]);
			getch();
	  }
	  else call3=1;
	  }

	  if(call4!=1)
	  { cout<<"Bot 3's Turn\n";  getch();
	  if(f3!=1)
	  {
			ch=BotChoice(3);                                   //bot3 choosing
			UpdateLog(ch,3);
			if(ch==1||ch==3) call4=1;
			if(ch==2)
			{
			  call1=0;
			  call2=0;
			  call3=0;
			  call4=1;
			  call5=0;
			}
			f3=Play(ch,3);
			clrscr();
			display(hands[0]);
			getch();
	  } 
	  else call4=1;
	  }

	  if(call5!=1)
	  {  cout<<"Bot 4's Turn\n";  getch();
	  if(f4!=1)
	  {
			ch=BotChoice(4);                                   //bot4 choosing
			UpdateLog(ch,4);
			if(ch==1||ch==3) call5=1;
			if(ch==2)
			{
			  call1=0;
			  call2=0;
			  call3=0;
			  call4=0;
			  call5=1;
			}
			f4=Play(ch,4);
			clrscr();
			display(hands[0]);
			getch();
	  } 
	  else call5=1;
	  }
	  cout<<call1<<call2<<call3<<call4<<call5;
	 X=call1+call2+call3+call4+call5;
	 pass++;
	}while(X!=5);


 ofile<<"Round "<<roundno<<" Over \n";
 ofile.close();
}


void main()
{
		ofstream ofile("LOG.dat",ios::out|ios::binary|ios::trunc);
		ofile.close();
		clrscr();
		cout<<"Welcome!! This is a program for a game of Texas Hold 'em Poker.\nPress any key to start playing\n";
		getch();
		CreateDeck();
		cout<<"Creating deck...\n";
		ShuffleDeck();
		ShuffleDeck();
		cout<<"Shuffling...\n";
		cout<<"Press any key to deal";
		getch();
		Deal(4);
		AssignHiCard();


		hands[0]=EvaluateHand(0,phand.card1.tempr, phand.card1.temps, phand.card2.tempr, phand.card2.temps);
		if(hands[0]!=2) hands[0]=0;

		CreatePot();
		CreateStash();

		clrscr();
		display(hands[0]);

		Round(0);
		currentbet=0;

		Flop();
		AssignHiCard();
		hands[0]=EvaluateHand(0,phand.card1.tempr, phand.card1.temps, phand.card2.tempr, phand.card2.temps);
		getch();
		clrscr();
		display(hands[0]);

		Round(1);
		currentbet=0;

		RivTurn(3);
		AssignHiCard();
		hands[0]=EvaluateHand(0,phand.card1.tempr, phand.card1.temps, phand.card2.tempr, phand.card2.temps);
		getch();
		clrscr();
		display(hands[0]);

		Round(2);
      currentbet=0;

		RivTurn(4);
		AssignHiCard();
		hands[0]=EvaluateHand(0,phand.card1.tempr, phand.card1.temps, phand.card2.tempr, phand.card2.temps);
		getch();
		clrscr();
		display(hands[0]);

		Round(3);
      currentbet=0;

	 cout<<"***********************END***************************\n";
	 getch();

}






/*
 cout<<ranks[i]<<" "<<ranks[j]<<"\t";




for(i=0;i<7;i++)
	cout<<"Rank - "<<ranks[i]<<" Suit - "<<suits[i]<<endl;
to display suits
*/











/*
void main()
{
	int bet;
	char ch='y';
	int choice, noofbots, no;
	cout<<"Please enter number of bots you would like to play with(Max 4)\n";
	cin>>noofbots;
	if(noofbots>4||noofbots<=0)
		{
			cout<<"Invalid number chosen!! Exiting program...";
			exit(0);
		}
while(ch=='y'||ch=='Y')
{
	cout<<"What would you like to do?\n1->Create a new Deck\n2->Shuffle the Deck\n3->Burn a card\n4->Show the deck\n5->Deal Cards\n6->Show my hand\n7->Show a Bot's Hand\n8->Flop\n9->River\n10->Turn\n11->Show Table Cards\n12->Show my stash\n13->Display\n14->Full Display\n15->Create Pot\n16->Place bet\n17->Show pot\n0->Exit\n";
	cin>>choice;
		switch(choice)
			{
				case 0 : exit(0);
							break;
				case 1 : CreateDeck();
							cout<<"Your Deck is being created.....";
							break;
				case 2 : ShuffleDeck();
							cout<<"Your Deck is being shuffled....";
							break;
				case 3 : Burn();
							break;
				case 4 : ShowDeck();
							break;
				case 5 : Deal(noofbots);
							cout<<"Cards have been dealt....\n";
							break;
				case 6 : ShowMyHand();
							break;
				case 7 : cout<<"Please enter the number of the bot whose hand you want to see\n";
							cin>>no;
							ShowBotHand(no-1);
							break;
				case 8 : Flop();
							break;
				case 9 : RivTurn(3);
							break;
				case 10 : RivTurn(4);
							break;
				case 11: ShowTableCards();
							break;
				case 12: ShowStash();
							break;
				case 13: display();
							break;
				case 14: fdisplay();
							break;
				case 15: CreatePot();
							break;
				case 16: InputBet();
							break;
				case 17: ShowPot();
							break;
				default : cout<<"Invalid choice!!\n";
							 break;
			}
	cout<<"Press any key to continue\n";
	getch();
}

}
*/
