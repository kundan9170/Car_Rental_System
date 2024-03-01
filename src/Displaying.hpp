#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;
namespace display{
    
    void main_screen (){
    system("cls");
    cout << "###########################################" << endl;
    cout << "#       WELCOME TO CAR RENTAL SYSTEM      #" << endl;
    cout << "#          [1]. REGISTER NEW USER.        #" << endl;
    cout << "#          [2]. LOGIN AS CUSTOMER.        #" << endl;
    cout << "#          [3]. LOGIN AS EMPLOYEE.        #" << endl;
    cout << "#          [4]. LOGIN AS ADMIN.           #" << endl;
    cout << "#          [5]. EXIT THE PROGRAM.         #" << endl;
    cout << "##########################################" << endl;
    cout << "\n\n\n" << endl;}

    void user_screen( string name){
        system("cls");
        cout << "##########################################" << endl;
        cout << "----------WELCOME BACK"<< " " << name << "  " <<"----------" << endl;
        cout << "#   [1.] Show the List of available Cars.#" << endl;
        cout << "#   [2.] SELECT TO RETURN IT.            #" << endl;
        cout << "#   [3.] SELECT TO SHOW YOUR USER SCORE. #" << endl;
        cout << "#   [4.] SELECT TO CLEAR YOUR DUE.       #" <<endl;
        cout << "#   [0.] GO BACK TO LOGIN SCREEN.        #" << endl;
        cout << "##########################################" << endl;
     }
     void due_screen(){
        system("cls");
          cout << "##########################################" << endl;
          cout << "[1.] SELECT TO CLEAR DUE." << endl;
          cout << "[0.] GO BACK." << endl;
     }
    void list_of_car_rented(){
        system("cls");
        cout <<"##########################################"<<endl;
        cout << "LIST OF RENTED CAR."<<endl;
    }
    void car_renting_screen(int i , int j){
        //system("cls");
        cout << endl;
        cout << "##########################################" << endl;
        cout << "["<<i<<"."<<"]" <<"-"<<"["<<j<<"."<<"]" << "SELECT CAR TO GET FULL INFORMATION ABOUT IT AND RENT IT." << endl;
        cout << "[0.] SELECT TO GO BACK" << endl;
        cout << endl;
    }

    void renting_screen(int i , int j){
        //system("cls");
        cout << "##########################################" << endl;
        cout << "[1.]" << "SELECT TO RENT IT." << endl;
        cout << "[0.] GO BACK." << endl;
    }

    void Payment_screen(){
        //system("cls");
        cout << "##########################################" << endl;
        cout << "[1.] SELECT TO PAY NOW." << endl;
        cout << "[2.] SELECT TO PAY LATER." << endl;
        cout << "[0.] GO BACK." << endl;
    }

    void how_many_week_rent(){
        //system("cls");
        cout << endl;
        cout << "##########################################" << endl;
        cout<< "Do you want Continue with this?" << endl;
        cout << "[1.] SELECT to change Number of week." << endl;
        cout << "[2.] SELECT to continue." << endl;
    }
    //void 
    void exiting(){
        cout << "-------exiting-------" << endl;
    }
    void manager_screen(){
        system("cls");
        cout << "##########################################" << endl;
        cout << "------------WELCOME BACK ADMIN------------" << endl;
        cout << "[1.] ADD NEW CARS." << endl;
        cout << "[2.] REMOVE CAR." << endl;
        cout << "[3.] GO BACK TO LOGIN SCREEN." << endl;
    }

    void car_condition(){
        cout << "WHAT IS CAR CONDITION?" << endl;
        cout << "[1.] EXCELLENT" << endl;
        cout << "[2.] GOOD" << endl;
        cout << "[3.] BAD" << endl;
    }


    void is_employee_or_manager(){
        system("cls");
        cout << "##########################################" <<endl;
        cout << "[1.] SELECT FOR CUSTOMER." << endl;
        cout << "[2.] SELECT FOR EMPLOYEE." << endl;
        cout << "[0.] GO BACK TO MAIN MENU." << endl;
    }
}


