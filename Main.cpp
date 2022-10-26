#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


const int num_tests=5;
enum choice {Add=1,Remove,Display,Search,Results,Quit};
struct Student{
    string name; //full name
    string ID; //Id number
    int tests_taken;//number of tests taken
    int* test_ptr;
    double test_avg;
};


void add_student();
void remove_Student(string userID);
int getNumber();
void display();
void search(string userID);
void exportResults();
int findMinimum(int* array,int size);

int main()
{   
    bool correct_choice;// a boolean variable to check whether the user chose the correct choice from the menu
    string userID; //this is the ID the user will enter to pass to any of the functions that require it like search or delete

    cout << "Computer Science and Engineering\n" << "CSCE 1030 - Computer Science 1\n" << "Mahmoud Algharbawi mfa0106 mfa0106@my.unt.edu\n*****************************\n";
    do{
        int choice_num;
        cout << "Please choose from the following:\n1.Add\n2.Remove\n3.Display\n4.Search\n5.Results\n6.Quit\nEnter your choice: ";
        cin >> choice_num;
        choice_num=static_cast<choice>(choice_num);
        correct_choice=false;
        switch(choice_num)
        {
            case 1:
                correct_choice=false;
                add_student();
                break;

            case 2:
                cout << "Enter the ID # of the student you want to remove: "; cin >> userID;
                correct_choice=false;
                remove_Student(userID);
                break;

            case 3:
                correct_choice=false;
                display();
                break;

            case 4:
                cout << "Enter the ID # of the student you want to search for: ";cin>>userID;
                search(userID);
                break;

            case 5: 
                exportResults();
                break;

            case 6:
                cout <<"Bye!\n";
                correct_choice=true;
                break;

            default: 
                cout << "Wrong choice please enter again.\n";
            
        }
    }while (!correct_choice);

    return 0;
}



void add_student()
{
    Student addStudent;
    string fname, lname;
    int tests_taken;
    ofstream fout;

    cin.ignore();
    cout << "Enter student first name: "; getline(cin,fname);
    cout << "Enter student last name: "; getline(cin,lname);
    addStudent.name= lname+','+fname;
    cout << "Enter student id: "; cin>> addStudent.ID;

   //getting the number of tests
    cout << "How many tests did the student take? "; cin>> tests_taken;
    addStudent.test_ptr= new int[tests_taken];
    
    for (int i=0;i<tests_taken;++i)
    {
        cout << "Enter grade for test #" << i+1 << ": "; cin >> addStudent.test_ptr[i];
    }

    //opening file
    fout.open("student.dat", ios::app);
    
    if(fout.fail())
    {
        cout << "Error opening file.\n";
        exit(1);
    }
    
    fout << endl;
    fout << addStudent.name << ","<<addStudent.ID<<","<<tests_taken<<",";
    for (int j=0;j<tests_taken;++j)
    {
        fout << addStudent.test_ptr[j] << ",";
    }
    

    fout.close();
    delete [] addStudent.test_ptr;
}



void remove_Student(string userID)
{
    bool found;
    string fname, lname;
    ofstream fout;
    ifstream fin;
    istringstream sin;
    int number_students= getNumber();
    Student* students = new Student[number_students];//allocationg memory for the array of structs
    string tempString;
    

    fin.open("student.dat");
    if (fin.fail())
    {
        cout << "Error opening file.\n";
        exit(1);
    }

    for (int i=0; i<number_students; ++i)
    {
            
        getline(fin,tempString,'\n');//this gets the full line 
        sin.clear();
        sin.str(tempString);
        getline(sin,lname,',');
        getline(sin,fname,',');
        students[i].name=lname+','+fname;//reading the name from the string then adding it to make the full name

        
        getline(sin,students[i].ID,',');//getting the id
        
      

        string temp1;//temporary string to read integer calues and conversion 
        getline(sin,temp1,',');
        students[i].tests_taken=stoi(temp1);//number of tests taken for that student

        students[i].test_ptr=new int[students[i].tests_taken];//dynamic array for the grades of the tests

        //cout << students[i].name << "\t" << students[i].ID;

        for (int j=0;j<students[i].tests_taken;++j)//getting the grades for the student
        {
            getline(sin,temp1,',');
            students[i].test_ptr[j]=stoi(temp1);
            //cout << students[i].test_ptr[j] << ","; //this was for seeing if the program reads the numbers correctly
        }
        //cout << endl;

        if(stoi(students[i].ID)==stoi(userID))
        {
            found = true;
            cout<< "Match found.\n";
        }
    }

    if (found)//if the id was found overwriting the whole file without the id of the student we want to delete
    {
        fout.open("student.dat");
        if (fout.fail())
        {
            cout << "Failed to open file.\n";
            exit(1);
        }
        
        for (int h=0;h<number_students;++h)
        {
            if (stoi(students[h].ID)==stoi(userID))
            {
                continue;
            }
            else
            {
                fout << students[h].name << "," << students[h].ID << "," << students[h].tests_taken << ",";
                for (int j=0;j<students[h].tests_taken;++j)
                {
                    fout << students[h].test_ptr[j] << ",";
                }
                        
                if (h<(number_students-2))
                {
                    fout << endl;
                }
            }
        }
        fout.close(); 
    }    
       
    
  
    if (!found)
    {
        cout << "No match found.\n";
    }

    for (int i=0;i<number_students;++i)//deleting the memory I allocated to the dynamic arrays of grades
    {
        delete [] students[i].test_ptr;
    }

    delete [] students;
    fin.close();
    
}




void display()
{
    ifstream fin;
    istringstream sin;
    int number_students= getNumber();
    string tempString;
    string fname, lname;

    fin.open("student.dat");
    if (fin.fail())
    {
        cout << "Error opening file.\n";
        exit(1);
    }
    
    Student* students = new Student[number_students];

    for (int i=0; i<number_students; ++i)
    {
            
        getline(fin,tempString,'\n');//this gets the full line 
        sin.clear();
        sin.str(tempString);
        getline(sin,lname,',');
        getline(sin,fname,',');
        students[i].name=lname+','+fname;//reading the name from the string then adding it to make the full name

        
        getline(sin,students[i].ID,',');//getting the id

        string temp1;//temporary string to read integer calues and conversion 
        getline(sin,temp1,',');
        students[i].tests_taken=stoi(temp1);//number of tests taken for that student

        students[i].test_ptr=new int[students[i].tests_taken];//dynamic array for the grades of the tests

        for (int j=0;j<students[i].tests_taken;++j)//getting the grades for the student
        {
            getline(sin,temp1,',');
            students[i].test_ptr[j]=stoi(temp1);
        }

            
        cout << setw(50) << students[i].name << setw(15) << students[i].ID;//outputs using the set format
        for (int j=0;j<students[i].tests_taken;++j)
        {
            cout << setw(5) << students[i].test_ptr[j];
        }
        cout << endl;       
        

        delete [] students[i].test_ptr;
    }

    delete [] students;
    fin.close();
    
}



void search(string userID)
{
    ifstream fin;
    istringstream sin;
    int number_students= getNumber();
    string tempString;
    string fname, lname;
    Student* students=new Student;
    bool found;

    fin.open("student.dat");
    if (fin.fail())
    {
        cout << "Error opening file.\n";
        exit(1);
    }


    while(!fin.eof())
    {
        getline(fin,tempString,'\n');//this gets the full line 
        sin.clear();
        sin.str(tempString);
        getline(sin,lname,',');
        getline(sin,fname,',');
        students->name=lname+','+fname;//reading the name from the string then adding it to make the full name

        
        getline(sin,students->ID,',');//getting the id
        


        string temp1;//temporary string to read integer calues and conversion 
        getline(sin,temp1,',');
        students->tests_taken=stoi(temp1);//number of tests taken for that student

        students->test_ptr=new int[students->tests_taken];//dynamic array for the grades of the tests
        
        for (int j=0;j<students->tests_taken;++j)//getting the grades for the student
        {
            getline(sin,temp1,',');
            students->test_ptr[j]=stoi(temp1);
        }
        
        if(stoi(students->ID)==stoi(userID))//this is true if the user entered id matches the id for the student
        {
            found = true;
            cout<< "Match found.\n";
            cout << setw(50) << students->name << setw(15) << students->ID;
            for (int j=0;j<students->tests_taken;++j)
            {
                cout << setw(5) << students->test_ptr[j];
            }
            cout << endl; 
            break;
        }
        else
        {
            found=false;
        }
    }
        if (!found)
        {
            cout << "No match was found.\n";
        }

        delete students;
        delete [] students->test_ptr;
}


void exportResults()
{
    ifstream fin;
    string fname, lname;
    ofstream fout;
    istringstream sin;
    int number_students= getNumber();
    Student* students = new Student[number_students];//allocationg memory for the array of structs

    string tempString;

    fin.open("student.dat");
    if (fin.fail())
    {
        cout << "Error opening file.\n";
        exit(1);
    }

    fout.open("averages.dat");
    if (fout.fail())
    {
        cout << "File error.\n";
        exit(1);
    }

    for (int i=0; i<number_students; ++i)
    {
           
        getline(fin,tempString,'\n');//this gets the full line 
        sin.clear();
        sin.str(tempString);
        getline(sin,lname,',');
        getline(sin,fname,',');
        students[i].name=lname+','+fname;//reading the name from the string then adding it to make the full name
        
        getline(sin,students[i].ID,',');//getting the id

        string temp1;//temporary string to read integer calues and conversion 
        getline(sin,temp1,',');
        students[i].tests_taken=stoi(temp1);//number of tests taken for that student

        students[i].test_ptr=new int[students[i].tests_taken];//dynamic array for the grades of the tests

        double sum=0;

        for (int j=0;j<students[i].tests_taken;++j)//getting the grades for the student
        {
            getline(sin,temp1,',');
            students[i].test_ptr[j]=stoi(temp1);
            sum= sum+students[i].test_ptr[j];
        }
       

        int min=findMinimum(students[i].test_ptr,students[i].tests_taken);
        
        sum = sum-min;
        
        if(students[i].tests_taken==5)
        {
            students[i].test_avg=sum/(students[i].tests_taken-1);
        }
        else 
        {
            students[i].test_avg=sum/(students[i].tests_taken);
        }        

        fout << students[i].ID << "\t" << students[i].test_avg << endl;

        
        delete [] students[i].test_ptr;
    }


    fout.close();
    fin.close();
    delete [] students;
}

int findMinimum(int* array,int size)
{
    int min;

    if (size<5)
    {
        min=0;
    }
    else if(size==5)
    {
        min=array[0];
        for (int i=0; i<size;++i)
        {
            if (min>array[i])
            {
             min = array[i];
            }
        }
       
    }
    
    return min;
}

int getNumber()
{
	ifstream fin;
	fin.open("student.dat");
	if (fin.fail())
	{
		cout<<"File error."<<endl;
		exit(1);
	}
	int count=0;
	string line;
	while(!fin.eof())
	{
		getline(fin, line);
		++count;
	}
	
	fin.close();
	return(count);
}