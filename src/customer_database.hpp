#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <bits/stdc++.h>
#include "users_class.hpp"
#define user_id_num 1000 // id of the customer
#define min_pass_len 10 // setting the minimum pass len

using namespace std;

class customer_database{
    protected:
      int no_of_customer;
      vector<customer> list_of_customer;
    public:
        //customer c;
    void start_customer_database(){
        list_of_customer.clear();
        fstream myfile;
        myfile.open("customer_database.txt" , ios:: in);
        string line;
        while(getline(myfile , line , '\n')){
            customer c(1,"","",0);
            stringstream ss(line);
            string user_info;
            int cnt = 1;
            while(getline(ss , user_info, ',')){
                if(cnt == 1){
                    c.set_id(stoi(user_info));
                    cnt++;
                }
                else if(cnt == 2){
                    c.set_name(user_info);
                    cnt++;
                }
                else if(cnt == 3){
                    c.set_password(user_info);
                    cnt++;
                }
                else if(cnt == 4){
                    c.set_fine_due(stoi(user_info));
                    cnt++;
                }
                else if(cnt == 5){
                    c.set_user_score(stoi(user_info));
                    cnt++;
                }
                else{
                    // from here user_info give car details
                    stringstream ss_temp(user_info);
                    string car_info;
                    // counter to retrieve car rented detail
                    int car_idx = 1;
                    rent_detail t;
                    while(getline(ss_temp , car_info , '.')){
                        if(car_idx == 1) {
                            t.car_name = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 2){
                            t.car_model = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 3){
                            t.rent_price = car_info;
                            car_idx++; 
                        }
                        else if(car_idx == 4){
                            t.rented_date = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 5){
                            t.due_date = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 6){
                            t.return_date = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 7){
                            t.is_late = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 8){
                            t.status = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 9){
                            t.car_idx = stoi(car_info);
                            car_idx++;
                        }
                    }
                    c.add_car(t);
                }
            }
            this->list_of_customer.push_back(c);
        }
        myfile.close();
    }

    bool is_username_avail(string username){
        for(auto u : list_of_customer){
            if(u.get_name() == username) return false;
        }
        return true;
    }

    void add_customer(){
        no_of_customer = list_of_customer.size();
        int user_id = no_of_customer + user_id_num;
        string name;
        while(true){
            cout << "Enter your Username without space :" << endl;
            cin >> name;
           // help :: ignore_input();
            if(is_username_avail(name) == true){
                cout << "------username is available------" << endl;
                break;
            }
            else{
                cout << "ERROR! USERNAME IS ALREADY TAKEN.TRY AGAIN." << endl;
                continue;
            }
        }
        string password;
        string pass_final;
        int pass_len = 0;
        while(true){
            cout << "Set Your Password." << endl;
            cin >> password;
           // help :: ignore_input();
            pass_len = password.size();
            if(pass_len<10){
                cout << "ERROR! PASSWORD MUST BE 10 CHAR LONG." << endl;
                continue; 
            }
            else{
                cout << "Enter Your Password Again." <<endl;
                cin >> pass_final;
               // help :: ignore_input();
                if(pass_final == password){
                    cout << "------REGISTARTION SUCCESSFULL------" << endl;
                    break;
                }
                else{
                    cout << "ERROR! PASSWORD MISMATCH.TRY AGAIN." << endl;
                    continue;
                }
            }
        }
        customer c(user_id , name , password , 0);
        c.set_user_score(500);
        this->list_of_customer.push_back(c);
    }

    void write_to_database(){
        fstream myfile;
        myfile.open("customer_database.txt" , ios :: out);
        for(auto c : this->list_of_customer){
            string line;
            line = to_string(c.get_id()) + "," + c.get_name() + "," + c.get_password() + "," + to_string(c.get_fine_due()) + ","+to_string(c.get_user_score())+",";
            vector<rent_detail> all_rented_car = c.get_rented_car();
            //cout << all_rented_car.size();
            if(all_rented_car.size()!=0){
                for(auto car_detail : all_rented_car){
                    line = line + car_detail.car_name + "." + car_detail.car_model + "." + car_detail.rent_price + "." + car_detail.rented_date + "." + car_detail.due_date + "." + car_detail.return_date + "." + car_detail.is_late + "." + car_detail.status + "." + to_string(car_detail.car_idx) + ",";
                }
            }
            //line+="kundan";
            //cout << "hello" << endl;
            line+= "\n";
            myfile << line;
        }
        myfile.close();
    } 
    string user_password(string name){
        for(auto c : list_of_customer){
            if(c.get_name() == name){
                return c.get_password();
            }
        }
    }
    customer* give_customer(string name , string password){
        for(int i = 0 ; i<list_of_customer.size() ; ++i){
            if(list_of_customer[i].get_name() == name && list_of_customer[i].get_password() == password){
                //cout << &(list_of_customer[i]) << endl;
                return &list_of_customer[i];
            }
        }
    }

    customer give_customer_obj(string name , string password){
        for(int i = 0 ; i<list_of_customer.size() ; ++i){
            if(list_of_customer[i].get_name() == name && list_of_customer[i].get_password() == password){
                //cout << &(list_of_customer[i]) << endl;
                return list_of_customer[i];
            }
        }
    }

    int is_empty_database(){
        if(list_of_customer.size() == 0){
            return 1;
        }
        else{
            return 0;
        }
    }

    

};


class employee_database {   
    protected:
      int no_of_customer;
      vector<employee> list_of_customer;
    public:
        //customer c;
    void start_employee_database(){
        list_of_customer.clear();
        fstream myfile;
        myfile.open("employee_database.txt" , ios:: in);
        string line;
        while(getline(myfile , line , '\n')){
            employee c(1,"","",0);
            stringstream ss(line);
            string user_info;
            int cnt = 1;
            while(getline(ss , user_info, ',')){
                if(cnt == 1){
                    c.set_id(stoi(user_info));
                    cnt++;
                }
                else if(cnt == 2){
                    c.set_name(user_info);
                    cnt++;
                }
                else if(cnt == 3){
                    c.set_password(user_info);
                    cnt++;
                }
                else if(cnt == 4){
                    c.set_fine_due(stoi(user_info));
                    cnt++;
                }
                else if(cnt == 5){
                    c.set_user_score(stoi(user_info));
                    cnt++;
                }
                else{
                    // from here user_info give car details
                    stringstream ss_temp(user_info);
                    string car_info;
                    // counter to retrieve car rented detail
                    int car_idx = 1;
                    employee_rent_detail t;
                    while(getline(ss_temp , car_info , '.')){
                        if(car_idx == 1) {
                            t.car_name = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 2){
                            t.car_model = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 3){
                            t.rent_price = car_info;
                            car_idx++; 
                        }
                        else if(car_idx == 4){
                            t.rented_date = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 5){
                            t.due_date = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 6){
                            t.return_date = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 7){
                            t.is_late = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 8){
                            t.status = car_info;
                            car_idx++;
                        }
                        else if(car_idx == 9){
                            t.car_idx = stoi(car_info);
                            car_idx++;
                        }
                    }
                    c.add_car(t);
                }
            }
            this->list_of_customer.push_back(c);
        }
        myfile.close();
    }

    bool is_username_avail(string username){
        for(auto u : list_of_customer){
            if(u.get_name() == username) return false;
        }
        return true;
    }

    void add_customer(){
        no_of_customer = list_of_customer.size();
        int user_id = no_of_customer + user_id_num;
        string name;
        while(true){
            cout << "Enter your Username without space :" << endl;
            cin >> name;
           // help :: ignore_input();
            if(is_username_avail(name) == true){
                cout << "------username is available------" << endl;
                break;
            }
            else{
                cout << "ERROR! USERNAME IS ALREADY TAKEN.TRY AGAIN." << endl;
                continue;
            }
        }
        string password;
        string pass_final;
        int pass_len = 0;
        while(true){
            cout << "Set Your Password." << endl;
            cin >> password;
           // help :: ignore_input();
            pass_len = password.size();
            if(pass_len<10){
                cout << "ERROR! PASSWORD MUST BE 10 CHAR LONG." << endl;
                continue; 
            }
            else{
                cout << "Enter Your Password Again." <<endl;
                cin >> pass_final;
               // help :: ignore_input();
                if(pass_final == password){
                    cout << "------REGISTARTION SUCCESSFULL------" << endl;
                    break;
                }
                else{
                    cout << "ERROR! PASSWORD MISMATCH.TRY AGAIN." << endl;
                    continue;
                }
            }
        }
        employee c(user_id , name , password , 0);
        c.set_user_score(500);
        this->list_of_customer.push_back(c);
    }

    void write_to_database(){
        fstream myfile;
        myfile.open("employee_database.txt" , ios :: out);
        for(auto c : this->list_of_customer){
            string line;
            line = to_string(c.get_id()) + "," + c.get_name() + "," + c.get_password() + "," + to_string(c.get_fine_due()) + ","+to_string(c.get_user_score())+",";
            vector<employee_rent_detail> all_rented_car = c.get_rented_car();
            //cout << all_rented_car.size();
            if(all_rented_car.size()!=0){
                for(auto car_detail : all_rented_car){
                    line = line + car_detail.car_name + "." + car_detail.car_model + "." + car_detail.rent_price + "." + car_detail.rented_date + "." + car_detail.due_date + "." + car_detail.return_date + "." + car_detail.is_late + "." + car_detail.status + "." + to_string(car_detail.car_idx) + ",";
                }
            }
            //line+="kundan";
            line+= "\n";
            myfile << line;
        }
        myfile.close();
    } 
    string user_password(string name){
        for(auto c : list_of_customer){
            if(c.get_name() == name){
                return c.get_password();
            }
        }
    }
    employee* give_customer(string name , string password){
        for(int i = 0 ; i<list_of_customer.size() ; ++i){
            if(list_of_customer[i].get_name() == name && list_of_customer[i].get_password() == password){
                //cout << &(list_of_customer[i]) << endl;
                return &list_of_customer[i];
            }
        }
    }

    employee give_customer_obj(string name , string password){
        for(int i = 0 ; i<list_of_customer.size() ; ++i){
            if(list_of_customer[i].get_name() == name && list_of_customer[i].get_password() == password){
                //cout << &(list_of_customer[i]) << endl;
                return list_of_customer[i];
            }
        }
    }

};


// int main(){
//     return 0;
// }