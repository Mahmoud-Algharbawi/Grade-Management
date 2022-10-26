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