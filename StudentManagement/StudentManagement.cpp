#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <random>
#include <cstring>
#define SIZE 20

using namespace std;

//ios::app provides that when you want to add a line end of your text, it provide writing a new line after the old/already exitsting data.

fstream studentFile;

bool run = true;

class Person
{
public:
	int id;
	string name, surname;

	virtual string ShowPerson() = 0;
	virtual string getName() = 0;
	
};

class Student : public Person{

public:

	bool isActive;

	Student() 
	{
	}
	
	Student(string _name, string _surname, int _id)
	{
		this->isActive = true;
		this->id = _id;
		this->name = _name;
		this->surname = _surname;
	}

	string ShowPerson()
	{
		string strID = to_string(this->id);
		return  "Name: " + this->name + " Surname: " + this->surname + " ID: " + strID;
	}

	string getName()
	{
		return this->name;
	}
	void WriteFile();
};

void isRun(int selected)
{

	while (selected != 0 && selected != 1)
	{
		system("cls");
		cout << "You have selected wrong operation. Please choose 1 or 0!!!" << endl;
		cout << "-->";
		cin >> selected;
	}

	if (selected == 1)
	{
		run = true;
	}
	else
	{
		run = false;
	}

	system("cls");

}

void ShowArray(string temp[], int size)
{

	for(int i = 0; i < size; i++)
	{
		if(temp[i] != "")
		{
			cout << i << ". Student ---> " << temp[i] << endl;
		}
	}
}

void ShowMenu()
{
	cout << setw(50) << "======== STUDENT MANAGEMENT SYSTEM ========\n\n\n";
	cout << setw(23) << "1. Add " << endl;
	cout << setw(24) << "2. List " << endl;
	cout << setw(26) << "3. Modify " << endl;
	cout << setw(26) << "4. Delete " << endl;
	cout << setw(24) << "5. Exit " << endl;
}

void ReadFile()
{
	ifstream readFile;
	string line;
	int index = 1;
	int choice;
	system("cls");
	
	readFile.open("students.txt", ios::in);
	
	if(readFile.is_open())
	{
		
		while(getline(readFile, line))
		{
			cout << index << ". STUDENT --->" << line << endl;
			index++;
		}
	}
	readFile.close();

	cout << "Would you like to see list <1,0> --> ";
	cin >> choice;

	isRun(choice);
	
}

void Modify(string studentArr[]);

void RemoveElement(string studentArr[]);

void WriteArray(string studentArray[])
{
	ifstream inFile("students.txt", ios::in);
	string line;
	int index = 0;

	if(inFile.is_open())
	{
		while(getline(inFile, line))
		{
			if(line != "")
			{
				studentArray[index] = line;
				index++;
			}
		}
		inFile.close();
	}
	index = 0;

}

void WriteFile(string studentArr[])
{
	ofstream outFile("students.txt", ios::out);
	int index = 0;

	if(outFile.is_open())
	{
		while(studentArr[index] != "")
		{
			outFile << studentArr[index] << endl;
			index++;
		}
	}
	outFile.close();
	index = 0;
}

void SortArray(string tempArr[])
{
	string temp; 

	//This for loop makes it sorted.
	for(int i = 0; i < SIZE - 1; i++ )
	{
		//When the value is empty in index, it will be changed its place with not empty element until the finding empty element. 
		if(tempArr[i+1] != "")
		{
			temp = tempArr[i];
			tempArr[i] = tempArr[i + 1];
			tempArr[i + 1] = temp;
		}
	}

	WriteFile(tempArr);

}

Student* CreateStudent();

int EmptyIndex(string tempAr[], int size);

int main()
{
	srand(time(0));
	
	int choice;
	int temp = 0;

	//To assign to array.
	Student* student;

	Student students[SIZE];	

	//Bufer variable.
	string studentArr[SIZE];
	   
	//That function will copy element from the text which is existent and then when you want to make any change, 
	//it can be used. After all the changes, it will be written it down in the text.
	WriteArray(studentArr);
	while(run)
	{
		studentFile.open("students.txt");
		ShowMenu();
		cout << setw(10) << "\nSelect Operation-> ";
		cin >> choice;
		switch (choice)
		{
		//Adding a student.
		case 1:
			system("cls");
			student = CreateStudent();
			student->WriteFile();
			WriteArray(studentArr);
			break;
		case 2:
			ReadFile();
			break;
		//Modify.
		case 3:
			Modify(studentArr);
			break;
		//Delete an Element from the text.
		case 4:
			RemoveElement(studentArr);
			break;
		//stop running the program.
		case 5:
			run = false;
			break;
		//When the choice is out of the list, it will give an error. 
		default:
			system("cls");
			cout << "There is no operation you have selected !! Please select operation which is in the list" << endl;	
			break;
		}

	}

	studentFile.close();
	
	return 0;
}

void Student::WriteFile()
{
	string strID = to_string(this->id);
	ofstream writeFile;

	writeFile.open("students.txt", ios::out | ios::app);
	
	if (writeFile.is_open())
	{
		writeFile << "Name: " << this->name << " Surname: " << this->surname << " ID: " << this->id << " Status: " << this->isActive << endl;
	}
	else
		cout << "Unable to open file"<< endl;

	writeFile.close();
}

//This function creates a student.
Student* CreateStudent()
{
	int ID = rand() % 1000 + 1000; 
	string name, surname;
	Student* temp;

	cout << "Name: ";
	cin >> name;
	cout << "\nSurname: ";
	cin >> surname;

	temp = new Student(name, surname, ID);

	cout << "A student named " << name << " has been created!!." << endl;

	return temp;

}

//This function finds empty index of the array.
int EmptyIndex(string tempAr[], int size)
{
	int tempIndex = 0;

	for(int i = 0 ; i < size; i++)
	{
		if(tempAr[i] == "")
		{
			tempIndex = i;
			break;
		}
	}

	return tempIndex;
}

//This function using for setting student active or not.
void Modify(string studentArr[])
{
	system("cls");
	int choice;
	int emptyIndex = EmptyIndex(studentArr, SIZE);
	int statusIndex;

	int selection;

	ShowArray(studentArr, SIZE);
	cout << "Which student would you like to change its status." << endl;
	cout << "-----> ";
	cin >> choice;
	if (choice == emptyIndex)
	{
		while (choice != emptyIndex)
		{
			system("cls");
			WriteArray(studentArr);
			cout << "Please enter a number which is in the list!!!" << endl;
			cout << "---> ";
			cin >> choice;
		}
	}
	else
	{
		
		int lastElement = studentArr[choice].size() - 1;//Last element is status of the element.
		string tempWord = studentArr[choice]; // Temporary variable to b.

		system("cls");
		
		if(tempWord[lastElement] == '1')
		{
			cout << studentArr[choice] << endl;
			cout << "That student's status is being changed from 1 to 0";
			tempWord.replace(lastElement, 1, "0");
		}
		else
		{
			cout << studentArr[choice] << endl;
			cout << "That student's status is being changed from 0 to 1" << endl;
			tempWord.replace(lastElement, 1, "1");
		}
		studentArr[choice] = tempWord;

		cout << "\nWould you like to continue? <1,0> ";
		cin >> selection;

		isRun(selection);



		WriteFile(studentArr);
	}
}

//This function using for removing element from the text and update it.
void RemoveElement(string studentArr[])
{
	system("cls");
	int choice;
	int emptyIndex = EmptyIndex(studentArr, SIZE);
	string tempStudent;
	
	int selection;

	ShowArray(studentArr, SIZE);
	cout << "Which student would you like to remove : ";
	cin >> choice;
	if(choice == emptyIndex)
	{
		while(choice != emptyIndex)
		{
			cout << "Please enter a number which is in the list!!!" << endl;
			cout << "---> ";
			cin >> choice;
		}
	}
	else
	{
		cout << "That student has been deleted in the system... ---> " << studentArr[choice]<< endl;
		studentArr[choice] = "";
		
	}

	SortArray(studentArr);

	cout << "Would you like to continue <1,0> " << endl;
	cout << "---> ";
	cin >> selection;

	isRun(selection);

	system("cls");

}
