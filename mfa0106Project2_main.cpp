#include "mfa0106Project2_header.h"



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