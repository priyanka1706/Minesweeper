#include<fstream.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>

class bomb
{
	int r, c;

	public:

	void getdata()
	{
	cout<<"Enter row no: ";
	cin>>r;
	cout<<"Enter column no: ";
	cin>>c;
	}

	int returnr()
	{return (r);}

	int returnc()
	{return (c);}
};


class regular
{
	int r, c, bmb, flag;

	public:

	regular()
	{
	flag=0;
	}

	void getdata()
	{
	cout<<"Enter row no: ";
	cin>>r;
	cout<<"Enter column no: ";
	cin>>c;
	cout<<"Enter no of bombs in surrounding: ";
	cin>>bmb;
	}

	int returnr()
	{return (r);}

	int returnc()
	{return (c);}

	int returnbmb()
	{return(bmb);}

	int returnflag()
	{return(flag);}

	void trueflag()
	{flag=1;}

};

void disp(regular reg[]);
void check(bomb b[], regular reg[], int cr, int cc);

int bombsfound=0;

void main()
{
randomize();

ifstream fin;
fin.open("bckup.dat", ios::in|ios::binary);


int gd=DETECT, gm;
initgraph(&gd, &gm, "");

cleardevice();
setcolor(4);

bomb b[34];
regular reg[66];
int i;

int gmno=random(5);
fin.seekg(gmno*sizeof(b)+gmno*sizeof(reg), ios::beg);

for(i=0; i<34; ++i)
{fin.read((char*)&b[i], sizeof(b[i]));}

for(i=0; i<66; ++i)
{fin.read((char*)&reg[i], sizeof(reg[i]));}

fin.close();

settextstyle(3,0,7);
outtextxy(140,150,"MINESWEEPER");
settextstyle(0,0,1);
outtextxy(230,240,"PRESS ENTER TO CONTINUE");

getch();
cleardevice();


settextstyle(3,0,5);
outtextxy(190,20,"INSTRUCTIONS");
settextstyle(3,0,2);
outtextxy(10,70,"1) Enter the row no of the indice you wish to access");
outtextxy(10,90,"and press ENTER");
outtextxy(10,110,"(Row nos are on the left end of grid)");
outtextxy(10,130,"2) Enter the column no of the cell you wish to access");
outtextxy(10,150,"and press ENTER");
outtextxy(10,170,"(Column nos are on the top of grid)");
outtextxy(10,190,"3)If not a bomb, the cell will display no of bombs in");
outtextxy(10,210,"immediate surrounding, and game continues on pressing 'C'");
outtextxy(10,230,"4)If it is a bomb, the game will end and then");
outtextxy(10,250,"press 'C' to continue on to score");
outtextxy(10,290,"NOTE: To exit midway, enter 'E' BUT only after entering");
outtextxy(10,310,"row and column no");
outtextxy(180,340,"PRESS ENTER TO CONTINUE");
getch();
cleardevice();


char exitcode;
int cr, cc;
int score=-1;

while (bombsfound==0)
{
	cleardevice();
	disp(reg);
	 gotoxy(52, 8);
	 cout<<"Enter row no: ";
	 gotoxy(52, 9);
	 cin>>cr;
	 gotoxy(52, 10);
	 cout<<"Enter column no: ";
	 gotoxy(52, 11);
	 cin>>cc;

	check(b, reg, cr, cc);
	score++;
	gotoxy(52, 15);
	cin>>exitcode;
	if(exitcode=='E'||exitcode=='e')
	{break;}
}

cleardevice();
gotoxy(32, 13);
cout<<"YOUR SCORE IS: "<<score;
getch();
}






//DISPLAY FUNCTION
void disp(regular reg[])
{
int i, j, l, b, t, r;

for(i=0, t=60, b=92; i<10; ++i, t+=32, b+=32)
{
	for(j=0, l=50, r=82; j<10; ++j, l+=32, r+=32)
		{
		rectangle(l,t,r,b);
		}
}

int x, y;

//COLUMN NOS
x=9;
y=3;
for(i=0; i<=9; ++i, x+=4)
{
	gotoxy(x, y);
	cout<<i;
}

//ROW NOS
x=5;
y=5;
for(i=0; i<=9; ++i, y+=2)
{
	gotoxy(x, y);
	cout<<i;
}

int cordc, cordr;
for(i=0; i<66; ++i)
{
	if(reg[i].returnflag()==1)
		{
		cordr=5+reg[i].returnr()*2;
		cordc=9+reg[i].returnc()*4;
		gotoxy(cordc,cordr);
		cout<<reg[i].returnbmb();
		}
}

}



//FUNCTION TO CHECK FOR BOMB
void check(bomb b[], regular reg[], int cr, int cc)
{

int i, cordr, cordc, j, crdr, crdc;

cordr=5+cr*2;
cordc=9+cc*4;

for(i=0; i<34; ++i)
{
	if(b[i].returnr()==cr&&b[i].returnc()==cc)
		{
		gotoxy(cordc,cordr);
		cout<<"B";
		gotoxy(52,13);
		cout<<"You hit a bomb! GAME OVER";
		gotoxy(52,14);
		cout<<"PRESS 'C' TO CONT";
		bombsfound=1;

		for(j=0; j<34; ++j)
		{
			crdr=5+b[j].returnr()*2;
			crdc=9+b[j].returnc()*4;
			gotoxy(crdc,crdr);
			cout<<"B";
		}
		break;
		}
}

for(i=0; i<66; ++i)
{
	if(reg[i].returnr()==cr&&reg[i].returnc()==cc)
		{
		gotoxy(cordc,cordr);
		cout<<reg[i].returnbmb();
		reg[i].trueflag();
		gotoxy(52,13);
		cout<<"Not a bomb!";
		gotoxy(52,14);
		cout<<"PRESS 'C'=CONT, 'E'=EXIT";
		break;
		}
}

}