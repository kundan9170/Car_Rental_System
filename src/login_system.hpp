#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <windows.h>
#include <bits/stdc++.h>
#include "customer_database.hpp"
#define id_username 2 // tells the column number in database
#define id_password 3 
#define not_found "#false" // keyword string

using namespace std;

namespace auth {

    customer login(customer_database database){
        string username;
        string password;
        while(true){

            cout << "[Enter your username]" << endl;
            cout << endl;
            cin >> username;
            //ignore_input();
            if(database.is_username_avail(username) == false){
                cout << "---------username found-----------" << endl;
                cout<<endl;
                while(true){
                    cout << "[Please Enter Your secret Password]" << endl;
                    cout << endl;
                    cin >> password;
                    //ignore_input();
                    if(password == database.user_password(username)){
                        cout << endl;
                        cout << "---------Login Sucessfull----------" << endl;
                        cout << endl;
                        return database.give_customer_obj(username, password);
                    }
                    else{
                        cout << endl;
                        cout << "~~~~ERROR! Password Mismatch. Please Try again~~~~" << endl;
                        cout << endl;
                        continue;
                    }
                }
            }
            else{
                cout << endl;
                cout << "~~~~~ERROR! username not found.~~~~~" <<endl;
                cout << "~~~~~Please try again.~~~~"<<endl;
                cout << endl;
                continue;
            }
        }
    }

    employee employee_login(employee_database database){
        string username;
        string password;
        while(true){
            cout << "Enter your username." << endl;
            cin >> username;
            //ignore_input();
            if(database.is_username_avail(username) == false){
                cout << "------username found------" << endl;
                while(true){
                    cout << "Please Enter Your secret Password" << endl;
                    cin >> password;
                    //ignore_input();
                    if(password == database.user_password(username)){
                        cout << "------Login Sucessfull-------" << endl;
                        return database.give_customer_obj(username, password);
                    }
                    else{
                        cout << "ERROR! Password Mismatch. Please Try again" << endl;
                        continue;
                    }
                }
            }
            else{
                cout << "ERROR! username not found." <<endl;
                cout << "Please try again."<<endl;
                continue;
            }
        }
    }



    manager login_admin(){
        manager m;
        fstream myfile;
        myfile.open("manager_info.txt" , ios :: in);
        string line;
        getline(myfile , line , '\n');
        stringstream ss(line);
        string name , password;
        getline(ss , name , ',');
        getline(ss , password , ',');
        string verify_password;
        while(true){
            cout << "ENTER THE ADMIN PASSWORD." << endl;
            cin >> verify_password;
            if(password!= verify_password){
                cout << "ERROR! WRONG PASSWORD." << endl;
                continue;
            }
            else{
                cout << "LOGIN SUCCESSFULL." << endl; 
               
                m.set_name(name);
                m.set_password(password);
                return m;
            }
        }
        
    }
}