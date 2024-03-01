#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <bits/stdc++.h>
#define user_predefined_score 500
#define discount_given_to_employee 0.85
//include "car_class.cpp"
using namespace std;

class user{
    protected:
        string password;
        int id;
        string name;
};


struct rent_detail{
    string car_name;
    string car_model;
    string rent_price;
    string rented_date;
    string due_date;
    string is_late;
    string return_date = "NOT_RETURNED";
    string status;
    int car_idx  = -1;
};

class customer : public user{
    private : 
        int fine_due;
        vector<rent_detail> rented_car;
        vector<rent_detail> curr_rented_car;
        int car_good = 0;
        int car_bad = 0;
        int car_excellent = 0;
        int no_of_car;
        int user_score = user_predefined_score;
    public :

    customer( int id , string name, string pass , int fine_due){
        this->name = name;
        this->id = id;
        this->password = pass;
        this->fine_due = fine_due;
        //car_stats();
        //current_rented_car();
    }

    void set_name(string name){
        this->name = name;
    }


    int get_user_score(){
        return user_score;
    }

    void set_user_score(int value){
        this->user_score = value;
    }

    void change_user_score(int val){
        this->user_score+=val;
    }

    void set_id(int id){
        this->id = id;
    }

    int get_fine_due(){
        return fine_due;
    }

    void set_fine_due(int val){
        fine_due+= val;
    }

    void add_car(rent_detail r){
        //cout << "hi";
        rented_car.push_back(r);
        //cout<<rented_car.size()<<endl;
    }

    string get_name(){
        return name;
    }

    string get_password(){
        return password;
    }

    string set_password(string pass){
        password = pass;
    }

    int get_id(){
        return id;
    }

    int whats_fine_due(){
        return fine_due;
     }
    int total_car_rented(){
        no_of_car =  rented_car.size();
        return no_of_car;
     }
     
    void car_stats(){
        for(auto car : rented_car){
            if(car.status == "good") car_good++;
            else if(car.status == "bad") car_bad++;
            else if(car.status == "excellent") car_excellent++;
        }
    }

    void current_rented_car(){
        curr_rented_car.clear();
        for(auto car : rented_car){
            if(car.return_date == "NOT_RETURNED"){
                this->curr_rented_car.push_back(car);
            }
        }
    }
    void rented_car_name(){
        for(auto car : rented_car){
            cout << car.car_name << endl;
        }
    }

    vector<rent_detail> get_rented_car(){
        //current_rented_car();
        vector<rent_detail> v = this->rented_car;
        return v;
        //return 
    }

     vector<rent_detail> get_curr_rented_car(){
        current_rented_car();
        vector<rent_detail> v = this->curr_rented_car;
        cout << v.size();
        return v;
        //return 
    }



    rent_detail* get_rent_detail_by_idx(int index){
        for(int i = 0 ; i<rented_car.size() ; ++i){
            if(rented_car[i].car_idx == index) return &rented_car[i];
        }
        //return &rented_car[idx];
    }

    int no_of_rented_car(){
        return rented_car.size();
    }

};

class manager : public user{
    public:
        void set_name(string name){
            this->name = name;
        }
        void set_password(string password){
            this->password = password;
        }
        string get_password(){
            return password;
        }

    manager (){
        fstream myfile;
        myfile.open("manager_info.txt" , ios :: in);
        string line;
        getline(myfile , line , '\n');
        stringstream ss(line);
        string n;
        string password;
        getline(ss , n , ',');
        getline(ss , password , ',');
        this->name = n;
        this->password = password;
    }
};


struct employee_rent_detail{
    string car_name;
    string car_model;
    string rent_price;
    string rented_date;
    string due_date;
    string is_late;
    string return_date = "NOT_RETURNED";
    string status;
    int car_idx  = -1;
};


class employee : public user{
    private: 
        int fine_due;
        vector<employee_rent_detail> rented_car;
        vector<employee_rent_detail> curr_rented_car;
        int car_good = 0;
        int car_bad = 0;
        int car_excellent = 0;
        int no_of_car;
        int user_score = user_predefined_score;
        float discount = discount_given_to_employee;
    public:
    employee(int id , string name, string pass , int fine_due){
        this->name = name;
        this->id = id;
        this->password = pass;
        this->fine_due = fine_due;
        rented_car.clear();
        curr_rented_car.clear();
        //car_stats();
        //current_rented_car();
    }
    float get_discount(){
        return discount;
    }
    void set_name(string name){
        this->name = name;
    }


    int get_user_score(){
        return user_score;
    }

    void set_user_score(int value){
        this->user_score = value;
    }

    void change_user_score(int val){
        this->user_score+=val;
    }

    void set_id(int id){
        this->id = id;
    }

    int get_fine_due(){
        return fine_due;
    }

    void set_fine_due(int val){
        fine_due+= val;
    }

    void add_car(employee_rent_detail r){
        //cout << "hi";
        rented_car.push_back(r);
        //cout<<rented_car.size()<<endl;
    }

    string get_name(){
        return name;
    }

    string get_password(){
        return password;
    }

    string set_password(string pass){
        password = pass;
    }

    int get_id(){
        return id;
    }

    int whats_fine_due(){
        return fine_due;
     }
    int total_car_rented(){
        no_of_car =  rented_car.size();
        return no_of_car;
     }
     
    void car_stats(){
        for(auto car : rented_car){
            if(car.status == "good") car_good++;
            else if(car.status == "bad") car_bad++;
            else if(car.status == "excellent") car_excellent++;
        }
    }

    void current_rented_car(){
        curr_rented_car.clear();
        for(auto car : rented_car){
            if(car.return_date == "NOT_RETURNED"){
                curr_rented_car.push_back(car);
            }
        }
    }
    void rented_car_name(){
        for(auto car : rented_car){
            cout << car.car_name << endl;
        }
    }

    vector<employee_rent_detail> get_rented_car(){
        current_rented_car();
        vector<employee_rent_detail> v = this->rented_car;
        return v;
    }

    vector<employee_rent_detail> get_curr_rented_car(){
        current_rented_car();
        vector<employee_rent_detail> v = this->curr_rented_car;
        return v;
    }

    employee_rent_detail* get_rent_detail_by_idx(int index){
        for(int i = 0 ; i<rented_car.size() ; ++i){
            if(rented_car[i].car_idx == index) return &rented_car[i];
        }
        //return &rented_car[idx];
    }
};