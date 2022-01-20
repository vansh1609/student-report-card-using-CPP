//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>	 //for getting system time
#include <windows.h> //for setting cursor positions
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class student
{
	int rollno;
	char name[50];
	int p_marks, c_marks, m_marks, e_marks, cs_marks;
	double per;
	char grade;
	void calculate(); //function to calculate grade
public:
	void getdata();		   //function to accept data from user
	void showdata() const; //function to show data on screen
	void show_tabular() const;
	int retrollno() const;
}; //class ends here

void student::calculate()
{
	per = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0;
	if (per >= 60)
		grade = 'A';
	else if (per >= 50)
		grade = 'B';
	else if (per >= 33)
		grade = 'C';
	else
		grade = 'F';
}

void student::getdata()
{
	cout << "\nEnter The roll number of student ";
	cin >> rollno;
	cout << "\n\nEnter The Name of student ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter The marks in physics out of 100 : ";
	cin >> p_marks;
	cout << "\nEnter The marks in chemistry out of 100 : ";
	cin >> c_marks;
	cout << "\nEnter The marks in maths out of 100 : ";
	cin >> m_marks;
	cout << "\nEnter The marks in english out of 100 : ";
	cin >> e_marks;
	cout << "\nEnter The marks in computer science out of 100 : ";
	cin >> cs_marks;
	calculate();
}

void student::showdata() const
{
	cout << "\nRoll number of student : " << rollno;
	cout << "\nName of student : " << name;
	cout << "\nMarks in Physics : " << p_marks;
	cout << "\nMarks in Chemistry : " << c_marks;
	cout << "\nMarks in Maths : " << m_marks;
	cout << "\nMarks in English : " << e_marks;
	cout << "\nMarks in Computer Science :" << cs_marks;
	cout << "\nPercentage of student is  :" << per;
	cout << "\nGrade of student is :" << grade;
}

void student::show_tabular() const
{
	cout << rollno << setw(6) << " " << name << setw(10) << p_marks << setw(4) << c_marks << setw(4) << m_marks << setw(4) << e_marks << setw(4) << cs_marks << setw(8) << per << setw(6) << grade << endl;
}

int student::retrollno() const
{
	return rollno;
}

//***************************************************************
//    	function declaration
//****************************************************************

void write_student();	  //write the record in binary file
void display_all();		  //read all records from binary file
void display_sp(int);	  //accept rollno and read record from binary file
void modify_student(int); //accept rollno and update record of binary file
void delete_student(int); //accept rollno and delete selected records from binary file
void class_result();	  //display all records in tabular format from binary file
void gotoxy(int, int);	  //set cursor position on console
void intro();			  //display welcome screen
void entry_menu();		  //display entry menu on screen
void submenu();			  //display options on every page

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
	char ch;
	cout.setf(ios::fixed | ios::showpoint);
	cout << setprecision(2);
	intro();
	Sleep(2000);
	system("cls");
	entry_menu();
	return 0;
}
//***************************************************************
//    	function to change the cursor position in console
//****************************************************************
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************
void intro()
{
	system("cls");
	system("COLOR F4");
	gotoxy(90, 2);
	time_t my_time = time(NULL);
	cout << ctime(&my_time);
	gotoxy(45, 6);
	cout << "CPP PROJECT" << endl;
	gotoxy(40, 7);
	cout << "STUDENT REPORT CARD" << endl;
	gotoxy(0, 25);
	cout << "MADE BY- ";
	gotoxy(0, 26);
	cout << "VANSH KALRA";
	gotoxy(0, 27);
	cout << "GRAPHIC ERA DEEMED TO BE UNIVERSITY";
}
//***************************************************************
//    	MAIN MENU
//****************************************************************

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout << "\n\n\n\tENTRY MENU";
	cout << "\n\n\t1.CREATE STUDENT RECORD";
	cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout << "\n\n\t3.SEARCH STUDENT RECORD ";
	cout << "\n\n\t4.MODIFY STUDENT RECORD";
	cout << "\n\n\t5.DELETE STUDENT RECORD";
	cout << "\n\n\t6.DISPLAY CLASS RESULT";
	cout << "\n\n\t7.EXIT";
	cout << "\n\n\tPlease Enter Your Choice (1-7) ";
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case '1':
		write_student();
		break;
	case '2':
		display_all();
		break;
	case '3':
		cout << "\n\n\tPlease Enter The roll number ";
		cin >> num;
		display_sp(num);
		break;
	case '4':
		cout << "\n\n\tPlease Enter The roll number ";
		cin >> num;
		modify_student(num);
		break;
	case '5':
		cout << "\n\n\tPlease Enter The roll number ";
		cin >> num;
		delete_student(num);
		break;
	case '6':
		class_result();
		break;
	case '7':
		exit(0);
		break;

	default:
		cout << "\a";
		entry_menu();
	}
}
//***************************************************************
//    	SUBMENU
//****************************************************************
void submenu()
{
	int c;
	gotoxy(90, 25);
	cout << "0.Exit";
	gotoxy(90, 26);
	cout << "1.Go back to main menu";
	cin >> c;
	switch (c)
	{
	case 0:
		exit(0);
	case 1:
		entry_menu();
		break;
	}
}

//***************************************************************
//    	function to write in file
//****************************************************************

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat", ios::binary | ios::app);
	st.getdata();
	outFile.write((char *)&st, sizeof(student));
	outFile.close();
	cout << "\n\nStudent record Has Been Created ";
	submenu();
}

//***************************************************************
//    	function to read all records from file
//****************************************************************

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while (inFile.read((char *)&st, sizeof(student)))
	{
		st.showdata();
		cout << "\n\n====================================\n";
	}
	inFile.close();
	submenu();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag = false;
	while (inFile.read((char *)&st, sizeof(student)))
	{
		if (st.retrollno() == n)
		{
			st.showdata();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nrecord not exist";
	submenu();
}

//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_student(int n)
{
	bool found = false;
	student st;
	fstream File;
	File.open("student.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}

	while (!File.eof() && found == false)
	{
		File.read((char *)&st, sizeof(student));
		if (st.retrollno() == n)
		{
			st.showdata();
			cout << "\n\nPlease Enter The New Details of student" << endl;
			st.getdata();
			int pos = (-1) * static_cast<int>(sizeof(st));
			File.seekp(pos, ios::cur);
			File.write((char *)&st, sizeof(student));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
	submenu();
}

//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat", ios::out);
	inFile.seekg(0, ios::beg);
	while (inFile.read((char *)&st, sizeof(student)))
	{
		if (st.retrollno() != n)
		{
			outFile.write((char *)&st, sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat", "student.dat");
	cout << "\n\n\tRecord Deleted ..";
	submenu();
}

//***************************************************************
//    	function to display all students grade report
//****************************************************************

void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
	cout << "==========================================================\n";
	cout << "R.No       Name        P   C   M   E   CS   %age   Grade" << endl;
	cout << "==========================================================\n";
	while (inFile.read((char *)&st, sizeof(student)))
	{
		st.show_tabular();
	}
	inFile.close();
	submenu();
}

//***************************************************************
//    			THE END 
//***************************************************************