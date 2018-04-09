#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <stdlib.h>

const char* DB_FILE_NAME = "info.dat";

struct Date
{
	int dd, mm, yy;
};

class Cricket                       
{
	int id;
	char player_name[30];
	Date dob;
	int age;
	char country[20];
	char category[20];
	int no_odi;
	int no_tests;
	long tot_runs;
	int tot_wickets;

	public :
	void output1();
	void input();
	void output();
	void output2(int r);
	void modify_file();
	void create_file();
	void read_file1();
	void search_yob();
	void search_category();
	void search_playername();
	void search_country();
	void delete_file();
};

void Cricket::input()
{
	 clrscr();
	 cout<<"enter the name :"<<endl;
	 gets(player_name);
	 cout<<"enter the date os birth :"<<endl;
	 cin>>dob.dd>>dob.mm>>dob.yy;
	 cout<<"enter the age :"<<endl;
	 cin>>age;
	 cout<<"enter the country :"<<endl;
	 gets(country);
	 cout<<"enter the category :"<<endl;
	 gets(category);
	 cout<<"enter the ODI's played :"<<endl;
	 cin>>no_odi;
	 cout<<"enter the tests played :"<<endl;
	 cin>>no_tests;
	 cout<<"enter the total runs :"<<endl;
	 cin>>tot_runs;
	 cout<<"enter the number wickets taken :"<<endl;
	 cin>>tot_wickets;
}

void Cricket::create_file()
{
	clrscr();
	fstream f;
	int n;
	f.open(DB_FILE_NAME, ios::app|ios::binary);
	Cricket d;
	cout<<"enter the number of records to be accepted"<<endl;
	cin>>n;
	for(int i=0;i<n;i++)
	{
			d.input();
			f.write((char*)&d,sizeof(d));
	}
	f.close();
}

void Cricket::output1()
{
	gotoxy(1,1);
	cout<<"Player Name";
	gotoxy(18,1);
	cout<<"Country";
	gotoxy(32,1);
	cout<<"Category";
	gotoxy(50,1);
	cout<<"ODI";
	gotoxy(58,1);
	cout<<"TEST";
	gotoxy(64,1);
	cout<<"Runs";
	gotoxy(72,1);
	cout<<"Wickets";
}

void Cricket::output()
{
	 clrscr();
	 gotoxy(1,1);    cout<<"Name          :";
	 gotoxy(20,1);	  cout<<player_name;
	 gotoxy(1,2);	  cout<<"country       :";
	 gotoxy(20,2);	  cout<<country;
	 gotoxy(1,3);	  cout<<"Category      :";
	 gotoxy(20,3);	  cout<<category;
	 gotoxy(1,4);	  cout<<"ODI's played  :";
	 gotoxy(20,4);	  cout<<no_odi;
	 gotoxy(1,5);	  cout<<"tests played  :";
	 gotoxy(20,5);	  cout<<no_tests;
	 gotoxy(1,6);	  cout<<"total runs    :";
	 gotoxy(20,6);	  cout<<tot_runs;
	 gotoxy(1,7);	  cout<<"wickets taken :";
	 gotoxy(20,7);	  cout<<tot_wickets;
}

void Cricket::output2(int r)
{
	gotoxy(1,r);
	cout<<player_name;
	gotoxy(18,r);
	cout<<country;
	gotoxy(32,r);
	cout<<category;
	gotoxy(50,r);
	cout<<no_odi;
	gotoxy(58,r);
	cout<<no_tests;
	gotoxy(64,r);
	cout<<tot_runs;
	gotoxy(72,r);
	cout<<tot_wickets;
}

void Cricket::read_file1()
{
	clrscr();
	fstream f;
	f.open(DB_FILE_NAME, ios::in|ios::binary);
	Cricket d;
	output1();
	int i,j,x=3;
	while(f.read((char*)&d,sizeof(d)))
	{
		d.output2(x);
		x++;
	}
	f.close();
}

void Cricket::delete_file()
{
	clrscr();
	fstream f,f1;
	Cricket d;
	f.open(DB_FILE_NAME,ios::in|ios::binary);
	f1.open("temp.dat",ios::out|ios::binary);
	int pos=-1;
	char ch[30];
	d.read_file1();
cout<<endl;
	cout<<"enter the player name to be deleted"<<endl;
	gets(ch);
	while(f.read((char*)&d,sizeof(d)))
	{
		if(strcmpi(d.player_name,ch)==0)
			pos++;
		else
			f1.write((char*)&d,sizeof(d));
	}
  	f.close();
  	f1.close();
  	remove(DB_FILE_NAME);
  	rename("temp.dat",DB_FILE_NAME);
}


void Cricket::modify_file()
{
	clrscr();
	fstream f;
	Cricket d;
	f.open(DB_FILE_NAME, ios::in|ios::out|ios::binary);
	int pos;
	int id1;
	int ch2,ch3;
	char name[30];
	cout<<"enter the modification mode //as 1.name):"<<endl;
	cin>>ch2;
	if(ch2==1)
	{
		d.read_file1();
		cout<<endl;
		cout<<"enter name of the player to be modified :"<<endl;
		gets(name);
		pos=(-1*sizeof(d));
		while(f.read((char*)&d,sizeof(d)))
		{
			if(strcmpi(d.player_name,name)==0)
			{
				clrscr();
				gotoxy(23,8);
				cout<<"MODIFY MENU"<<endl;
				gotoxy(18,9);
				cout<<"1.BASED ON TOTAL RUNS"<<endl;
				gotoxy(18,10);
				cout<<"2.BASED ON TOTAL WICKETS"<<endl;
				gotoxy(18,11);
				cout<<"3.BASED ON. NUMBER OF ODI"<<endl;
				gotoxy(18,12);
				cout<<"4.BASED ON NO. OF TESTS"<<endl;
				gotoxy(18,14);
				cout<<"ENTER THE CHOICE :"<<endl;
				gotoxy(18,15);
cin>>ch3;
				switch(ch3)
				{
					case 1:cout<<"enter total runs :"<<endl;
						   cin>>d.tot_runs;
						   break;
					case 2:cout<<"enter total wicket:"<<endl;
					  	   cin>>d.tot_wickets;
						   break;
					case 3:cout<<"enter no. odi :"<<endl;
						   cin>>d.no_odi;
						   break;
					case 4:cout<<"enter no. of test:";
   cout<<endl;
						   cin>>d.no_tests;
						   break;
				}
				f.seekp(pos,ios::cur);
				f.write((char*)&d,sizeof(d));
			} //end of if
		} //end of while
	 } //end of ch2 if
} //end of function

void Cricket::search_yob()
{
	clrscr();
	fstream f;
	f.open(DB_FILE_NAME, ios::in|ios::binary);
	int year, x=3,flag=-1;
	Cricket d;
	cout<<"enter the YOB to be searched :"<<endl;
	cin>>year;
	clrscr();
	d.output1();
	while(f.read((char*)&d,sizeof(d)))
	{
		if(d.dob.yy==year)
		{
			flag=1;
			d.output2(x);
			x++;
		}
	}
	if(flag==-1)
	{
		cout<<"year of birth entered incorrect !!:"<<endl;
	}
	f.close();
}

void Cricket::search_category()
{
	clrscr();
	fstream f;
	f.open(DB_FILE_NAME, ios::in|ios::binary);
	char cat[20];
	int x=3,flag=-1;
	Cricket d;
	cout<<"enter the category to be searched"<<endl;
	gets(cat);
	clrscr();
	d.output1();
	while(f.read((char*)&d,sizeof(d)))
	{
		if(strcmpi(d.category,cat)==0)
		{
			flag=1;
			d.output2(x);
			x++;
		}
	}
	if(flag==-1)
	{
		cout<<"category entered incorrect !!:"<<endl;
	}
	f.close();
}

void Cricket::search_playername()
{
	clrscr();
	fstream f;
	f.open(DB_FILE_NAME, ios::in|ios::binary);
	char pla_name[30];
	int flag=-1;
	Cricket d;
	cout<<"enter the player name to be searched"<<endl;
	gets(pla_name);
	clrscr();
	while(f.read((char*)&d,sizeof(d)))
	{
		if(strcmpi(d.player_name,pla_name)==0)
		{
			flag=1;
			d.output();
		}
	}
   if(flag==-1)
	{
		cout<<"player name entered incorrect !!:"<<endl;
	}
	f.close();
}

void Cricket::search_country()
{
	clrscr();
	fstream f;
	f.open(DB_FILE_NAME, ios::in|ios::binary);
	char ctry[30];
	int x=3,flag=-1;
	Cricket d;
	cout<<"enter the country to be searched"<<endl;
	gets(ctry);
	clrscr();
	d.output1();
	while(f.read((char*)&d,sizeof(d)))
	{
		if(strcmpi(d.country,ctry)==0)
		{
			flag=1;
			d.output2(x);
			x++;
		}
	}
   	if(flag==-1)
	{
		cout<<"country entered incorrect !!:"<<endl;
	}
	f.close();
}



void main_menu();

int Admin()
{
	 char login[20];
	 cout<<"enter the password"<<endl;
	 gets(login);
	 clrscr();
	char password[20]="AQUAragia";
	if(strcmpi(login,password)==0)
	{
		int ch1;
		Cricket dummy;
		do
		{
			clrscr();
			gotoxy(23,8);
			cout<<"ADMIN MENU"<<endl;
			gotoxy(18,9);
			cout<<"1.CREATE DATABASE"<<endl;
			gotoxy(18,10);
			cout<<"2.DISPLAY"<<endl;
			gotoxy(18,11);
			cout<<"3.REMOVE"<<endl;
			gotoxy(18,12);
			cout<<"4.MODIFY"<<endl;
			gotoxy(18,13);
			cout<<"5.BACK TO MAIN MENU"<<endl;
			gotoxy(18,15);
			cout<<"ENTER YOUR CHOICE"<<endl;
			gotoxy(18,16);
cin>>ch1;
			switch(ch1)
			{
					case 1: dummy.create_file();
								break;
					case 2: dummy.read_file1();
								break;
					case 3: dummy.delete_file();
								break;
					case 4: dummy.modify_file();
								break;
					case 5: main_menu();
			}
			getchar();
		}while(ch1<=5);
		return 0;
	}
	return 1; // Something failed!
}

int user_menu()
{
	clrscr();
	Cricket dummy;
	int ch4;
	gotoxy(23,8);
	cout<<"USER MENU"<<endl;
	gotoxy(18,9);
	cout<<"1.SEARCH ON DOB"<<endl;
	gotoxy(18,10);
	cout<<"2.SEARCH ON CATEGORY"<<endl;
	gotoxy(18,11);
	cout<<"3.SEARCH ON PLAYER NAME"<<endl;
	gotoxy(18,12);
	cout<<"4.SEARCH ON COUNTRY"<<endl;
	gotoxy(18,13);
	cout<<"5.BACK TO MAIN MENU";
	gotoxy(18,15);
	cout<<"ENTER YOUR CHOICE"<<endl;
	gotoxy(18,16);
cin>>ch4;
	switch(ch4)
	{
		case 1: dummy.search_yob();
					break;
		case 2: dummy.search_category();
					break;
		case 3: dummy.search_playername();
					break;
		case 4: dummy.search_country();
					break;
		case 5: main_menu();
					break;
	}
	return 0;
}



void main_menu()
{
	int ch;
	int ret = 0;
	do
	{
		clrscr();
		gotoxy(23,8);
		cout<<"CRICKET PLAYER DATABASE"<<endl;
		gotoxy(18,9);
		cout<<"MENU"<<endl;
		gotoxy(18,10);
		cout<<"1.ADMIN LOGIN"<<endl;
		gotoxy(18,11);
		cout<<"2.USER"<<endl;
		gotoxy(18,12);
		cout<<"3.EXIT"<<endl;
		gotoxy(18,14);
		cout<<"ENTER YOUR CHOICE"<<endl;
		gotoxy(18,15);
		cin>>ch;
		switch(ch)
		{
			case 1: ret = Admin();
						break;
			case 2: ret = user_menu();
						break;
			case 3: exit(0);
						break;
		}
		//if(ret) return;
		getchar();
	}while(ch<=3);
}

void main()
{
	main_menu();
}
