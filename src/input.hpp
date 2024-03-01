#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <windows.h>
#include <bits/stdc++.h>
#define id_username 2 // tells the column number in database
#define id_password 3 
#define not_found "#false" // keyword string

using namespace std;


namespace input{
    int take_input(int i , int j){
        while(true){
            int choice;
            cin >> choice;
            //help :: ignore_input();
            if(choice<i || choice>j){
                cout << "~~~~~ERROR! INVALID INPUT. TRY AGAIN.~~~~~~" << endl;
                continue;
            }
            else{
                return choice;
            }
        }
    }
}
