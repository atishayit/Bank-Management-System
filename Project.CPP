#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>

class account
{
	int acno;
	char name[50];
	int deposit;
	long int mobile;
	char resi[100];
	int age;
	char type;
	public:
		void create_account();
		void show_account();
		void modify();
		void dep(int);
		void draw(int);
		void report();
		int retacno();
		int retdeposit();
		char rettype();
};

void account::create_account()
{
	cout<<"\nEnter the Account Number: ";
	cin>>acno;
	cout<<"\nEnter the Name of The Account Holder : ";
	gets(name);
	cout<<"\nEnter age: ";
	cin>>age;
	cout<<"\nEnter your mobile number: ";
	cin>>mobile;
	cout<<"\nEnter your residential address: ";
	cin>>resi;
	cout<<"\nEnter type of The account (C for Current/S for Savings) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount( >=500 for Savings and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\nAccount Created !!!";
}

void account::show_account()
{
	cout<<"\n\tAccount No. : "<<acno;
	cout<<"\n\tAccount Holder Name : "<<name;
	cout<<"\n\tAge : "<<age;
	cout<<"\n\tMobile Number : "<<mobile;
	cout<<"\n\tResidential Address : "<<resi;
	cout<<"\n\tType of Account : "<<type;
	cout<<"\n\tBalance amount : "<<deposit;
}

void account::modify()
{
	cout<<"\n\tEnter The Name of The account Holder : ";
	gets(name);
	cout<<"\n\tEnter age: ";
	cin>>age;
	cout<<"\n\tEnter mobile number: ";
	cin>>mobile;
	cout<<"\nEnter your residential address: ";
	cin>>resi;
	cout<<"\n\tEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\tEnter The amount : ";
	cin>>deposit;
}

void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report()
{
	cout<<acno<<setw(12)<<" "<<name<<setw(11)<<" "<<age<<setw(9)<<" "<<type<<setw(14)<<deposit<<endl;
}

int account::retacno()
{
	return acno;
}

int account::retdeposit()
{
	return deposit;
}

char account::rettype()
{
	return type;
}


void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();


int isstaff()
{
	clrscr();
	char code[7] = { "ATIBANK" };
	int access = 1;
	char input[7];
	cout<<"Enter the access code: ";
	for(int i=0; i<7; i++)
	{
		input[i] = getch();
		cout<<"*";
	}
	getch();
	cout<<endl;
	for(i=0; i<7; i++)
		if( input[i] != code[i] )
		{
			access = 0;
			break;
		}
	if( access == 1 )
		return(1);
	else
		return(0);
}

void main()
{
	char ch;
	int num;
	clrscr();
	intro();
	if( isstaff() )
	{
	do
	{
		clrscr();
		cout<<"\n\n\n\t\t\t\t\tMAIN MENU";
		cout<<"\n\t\t\t\t\t---------";
		cout<<"\n\n\tPress 1:TO CREATE A NEW ACCOUNT";
		cout<<"\n\n\tPress 2:TO DEPOSIT AMOUNT";
		cout<<"\n\n\tPress 3:TO WITHDRAW AMOUNT";
		cout<<"\n\n\tPress 4:FOR BALANCE ENQUIRY";
		cout<<"\n\n\tPress 5:SHOW ALL ACCOUNTS HOLDERS LIST";
		cout<<"\n\n\tPress 6:TO CLOSE AN ACCOUNT";
		cout<<"\n\n\tPress 7:TO MODIFY AN ACCOUNT";
		cout<<"\n\n\tPress 8:TO EXIT";
		cout<<"\n\n\tSelect Your Option: ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter the account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter the account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tEnter the account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter the account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter the account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using Bank Managemnt System !!";
			break;
		 default :cout<<"\a";
		}
		getch();
	}while(ch!='8');
	}
}

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write((char *) &ac, sizeof(account));
	outFile.close();
}

void display_sp(int n)
{
	account ac;
	int flag=0;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\t\t\tBALANCE DETAILS\n";
	cout<<"\t\t\t\t---------------";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
}

void modify_account(int n)
{
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\n\n\n\tEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*sizeof(account);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\tRecord Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\t Record Not Found ";
}

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write((char *) &ac, sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\tRecord Deleted !!";
}

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"======================================================\n";
	cout<<"A/c no.      NAME          Age 	    Type      Balance\n";
	cout<<"======================================================\n";
	while(inFile.read((char *) &ac, sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	int found=0;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &ac, sizeof(account)) && found==0)
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\n\n\t\t\tTO DEPOSIT AMOUNT";
				cout<<"\n\t\t\t-----------------";
				cout<<"\n\n\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\t\t\t------------------";
				cout<<"\n\n\tEnter The amount to be withdrawn: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"\n\tInsufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)* sizeof(ac);
			File.seekp(pos,ios::cur);
			File.write((char *) &ac, sizeof(account));
			cout<<"\n\tRecord Updated";
			found=1;
	       }
	}
	File.close();
	if(found==0)
		cout<<"\n\t Record Not Found ";
}

void intro()
{
	cout<<"\n\n\n\t\t	BANK MANAGEMENT SYSTEM";
	cout<<"\n\t\t        ----------------------";
	cout<<"\n\n\n\n	MADE BY : Atishay Jain";
	getch();
}