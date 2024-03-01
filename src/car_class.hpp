#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <windows.h>
#include <bits/stdc++.h>
#include "date_handler.hpp"
#define car_num 1000 // id of cars
using namespace std;

class car{
    private:
        int id;
        string name;
        string model;
        string condition;
        bool is_avail;
        string due_date;
        int price;
    public:
        car(int id , string name , string model , string condition , bool is_avail , string due_date , int price){
            this->id = id;
            this->name = name;
            this->model = model;
            this->condition = condition;
            this-> is_avail = is_avail;
            this->due_date = due_date;
            this->price = price;
        }
        void set_name(string name){
            this->name = name;
        }
        void set_model(string model){
            this->model = model;
        }
        void set_condition(string condition){
            this->condition = condition;
        }
        void set_price(int p){
            this->price = p;
        }
        bool car_avail(){
            return is_avail;
        }
        void set_avail(bool b){
            this->is_avail = b;
        }        
        void set_due_date(string date){
            due_date = date;
        }
        void set_id(int id){
            this->id = id;
        }

        string get_name(){return this->name;}
        string get_model(){return this->model;}
        string get_condition(){return this->condition;}
        int get_price(){return this->price;}
        string get_due_date(){return this->due_date;}
        bool get_is_avail(){return this->is_avail;}
        int get_id(){return id;}
};

// bool is_valid_input(int i , int j , int input){
//     if(input>=i && input<=j){
//         return true;
//     }
//     else{
//         retur 
//     }
// }

void display_invalid_input(){
    cout << "ERROR INVALID INPUT" << endl;
}


// bool isInteger(const std::string& str) {
//     try {
//         size_t pos;
//         std::stoi(str, &pos);
//         return pos == str.length();
//     } catch (std::invalid_argument&) {
//         return false;
//     } catch (std::out_of_range&) {
//         return false;
//     }
// }



class car_database{
    private:
        vector<car> cars;
        int no_of_cars = 0;
    public:
    int get_no_of_car(){
        no_of_cars = cars.size();
        return no_of_cars;
    }
    void add_car(){
        //car c;
        string name;
        cout << "Enter the company of the Car:" << endl;
        cin >> name;
        string model;
        cout << "Enter the model of the Car:" << endl;
        cin >> model;
        string condition;
        int idx = 0;
        system("cls");
        cout << "Select the condition of the Car:" << endl;
        cout << "[1] EXCELLENT"<<endl;
        cout << "[2] GOOD" << endl;
        cout << "[3] BAD" << endl;
        cin >> idx;
        while(idx!= 1 && idx != 2 && idx !=3){
            display_invalid_input();
            cin >> idx;
        }
        switch(idx){
            case 1 :
                condition = "Excellent";
                break;
            case 2 :
                condition = "Good";
                break;
            case 3 :
                condition = "Bad";
                break;
        }
        bool avail;
        system("cls");
        cout << "IS CAR AVAILABLE FOR RENTING?" << endl;
        cout << "[1] AVAILABLE" << endl;
        cout << "[2] NOT AVAILABLE" << endl;
        idx = 0;
        cin >> idx;
        while(idx<1 || idx>2){
            display_invalid_input();
            cin >> idx;
        }
        switch(idx){
            case(1):
                avail = true;
                break;
            case(2):
                avail = false;
                break;
        }
        string due_date = "AVAILABLE";
        if(avail == false){
                while(true){
                    cout << "When Car will be available?. Enter the date.(YYYY-MM-DD)" << endl;
                    cin >> due_date;
                    if(dates::isValidDate(due_date)){
                        break;
                    }
                    else{
                        cout << "~~~~Please Enter valid Date.~~~~" << endl;
                        continue;
                    }
                }
            }
        int price;
        while(true){
            try{
                cout << "Enter the price of renting per week." << endl;
                cin >> price;
                cout << "CAR ADDED SUCCESSFULLY." << endl;
                dates :: waitForSeconds(2);
                break;
            }
            catch(...){
                display_invalid_input();
            }  
        }
        no_of_cars = cars.size();
        car c(no_of_cars + car_num, name , model , condition , avail , due_date , price);
        this->cars.push_back(c);
    }
    void show_car(){
        //int cnt = 1;
        system("cls");
        cout << endl;
        cout << "##########################################" << endl;
        for(int i = 0 ; i<cars.size() ; ++i){
            cout <<"#    [" << i+1 << "." <<"]" << cars[i].get_name() << "_" << cars[i].get_model() << endl;
            //cnt++;
        }
    }
    void remove_car(int idx){
        cars.erase(cars.begin()+idx-1);
    }
    void write_to_database(){
        fstream myfile;
        myfile.open("car_database.txt" , ios :: out);
        for(auto temp_car : cars){
            string line;
            line = to_string(temp_car.get_id()) + "," + temp_car.get_name() + "," + temp_car.get_model() + "," + to_string(temp_car.get_price()) + "," + temp_car.get_condition() + "," + to_string(temp_car.get_is_avail()) + "," + temp_car.get_due_date() + "," + "\n";
            myfile << line;
        }
        myfile.close();
    } 

    void start_car_database(){
        this->cars.clear();
        fstream myfile;
        myfile.open("car_database.txt" , ios :: in);
        string t_line;
        while(getline(myfile , t_line , '\n')){
            stringstream ss(t_line);
            string word;
            car c (1  ,"" , "" , "" , 1 , "" , 0);
            int cnt = 1;
            while(getline(ss , word , ',')){
                switch(cnt){
                    case (1):
                        c.set_id(stoi(word));
                        cout << stoi(word) << endl;
                        cnt++;
                        break;
                    case (2):
                        c.set_name(word);
                        cnt++;
                        break;
                    case (3):
                        c.set_model(word);
                        cnt++;
                        break;
                    case (4):
                        c.set_price(stoi(word));
                        cnt++;
                        break;
                    case (5):
                        c.set_condition(word);
                        cnt++;
                        break;
                    case (6):
                        if(stoi(word) == 1)c.set_avail(true);
                        else c.set_avail(false);
                        cnt++;
                        break;
                    case (7):
                        c.set_due_date(word);
                        cnt++;
                        break;
                }
            }
            this->cars.push_back(c);
        }
        myfile.close();
    }

    void display_car_info(int index){
        system("cls");
        car c = cars[index-1];
        cout << "##########################################" << endl;
        cout << "#   CAR NAME             -    " << c.get_name() << endl;
        cout << "#   CAR MODEL            -    " << c.get_model() << endl;
        cout << "#   CAR RENT PER WEEK    -    " << c.get_price() << endl;
        cout << "#   CAR AVAILABILITY     -    " << c.get_due_date() << endl;
        cout << "#   CAR CONDITION        -    " << c.get_condition() << endl;
        //cout << endl;
    }

    car* get_car(int index){
        return &cars[index-1];
    }

    car* get_car_by_id(int id){
        for(int i = 0 ; i<cars.size() ; ++i){
            if (cars[i].get_id() == id){
                //cout << &cars[i] << endl;
                return &cars[i];
            }
        }
    }
    bool if_car_id_exits(int id){
        for(int i = 0 ; i<cars.size() ; ++i){
            if (cars[i].get_id() == id){
                //cout << &cars[i] << endl;
                return true;
            }
        }
        return false;
    }
};
