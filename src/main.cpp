#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <windows.h>
#include <chrono>
#include<ctime>
#include <bits/stdc++.h>
#include "Displaying.hpp"
#include "car_class.hpp"
#include "login_system.hpp"
#include "input.hpp"
//#include "date_handler.hpp"
#define id_username 2 // tells the column number in database
#define id_password 3
#define not_found "#false" // keyword string
#define first_index_of_option_screen 1
#define last_index_of_option_screen 5
#define maximum_rent_week 4
#define bonus_good_to_excellent 200
#define bonus_bad_to_excellent 500
#define bonus_bad_to_good 200
#define penalty_excellent_to_good -100
#define penalty_excellent_to_bad -500
#define penalty_good_to_bad -300
#define penalty_for_late_submission -350
#define bonus_for_on_time_submission 200
#define minimum_score_to_rent 300
#define maximum_due_allowed 10000
#define wait_sec 2

using namespace std;

int how_many_week_screen(int price){
    while(true){
        int week;
        cout << endl;
        cout << "###########################################" << endl;
        cout << "How Many Weeks you want to rent?" << endl;
        cout << "Maximum rent week is" << " " << maximum_rent_week << "." << endl;
        week = input::take_input(1, maximum_rent_week);
        cout << endl;
        cout << "Total Price will be - " << price*week << endl;
        display::how_many_week_rent();
        int choice4;
        choice4 = input :: take_input(1, 2);
        if(choice4 == 1){
            continue;
        }
        else{
            display :: exiting();
            return week;
            break;
        }
                                        }
}

// bool admin_aut(manager m){
//     cout << "ASK ADMIN TO VERIFY." << endl;
//     dates :: waitForSeconds(wait_sec);
//     cout << "ENter" 
// }

void selecting_car_menu(customer c , car_database &car_db , manager &m , customer_database &customer_db , int *choice1){
        int choice2;
        int choice3;
        while(true){
            if(car_db.get_no_of_car() == 0){
                cout << "NO CAR IS AVAILABLE TO RENT." << endl;
                cout << endl;
                dates :: waitForSeconds(2);
                return;
            }
            car_db.show_car();
            display :: car_renting_screen(1 , car_db.get_no_of_car());
            *choice1 = input :: take_input(0,car_db.get_no_of_car());
            if(*choice1==0) return;
            car *car_ = car_db.get_car(*choice1);
            car_db.display_car_info(*choice1);
            cout << endl;
            // Selecting the car to rent it
            display ::renting_screen(1, car_db.get_no_of_car());
            int flag4 = true;
            while(true){
                choice2 = input :: take_input(0,1);
                if(choice2 == 0) break;
                if(choice2 == 1 && car_->get_is_avail()){
                    break;
                }
                else{
                    //system("cls");
                    cout << endl;
                    cout << "~~~~~~~~SORRY THIS CAR IS NOT AVAILABLE TO RENT!!~~~~~~~~~~" << endl;
                    cout << "~~~~~~~~PLEASE CHECK AVAILABILITY DATE~~~~~~~~~~~~~~~~~~~~~" << endl;
                    cout << endl;
                    dates :: waitForSeconds(2);
                    flag4 = false;
                    break;
                }
            }
            if(c.get_user_score()<minimum_score_to_rent || c.get_fine_due()>maximum_due_allowed) {
                cout << "~~~~SORRY YOU ARE NOT ELIGIBLE TO RENT A CAR!~~~~" << endl;
                if(c.get_user_score()<minimum_score_to_rent){
                    cout << "~~~~YOUR SCORE IS TOO LOW~~~~"<<endl;
                    cout << "SCORE :" << " " << c.get_user_score() << endl;
                    cout<< endl;
                }
                else{
                    cout << "~~~~PLEASE CLEAR YOUR DUES FIRST~~~~" << endl;
                    cout << "DUE : " << " " << c.get_fine_due() << endl;
                    cout << endl;
                }
                dates :: waitForSeconds(2);
                break; 
            }
            if(!flag4) continue;
            
            if(choice2 == 0){
                display :: exiting();
                break;
            }
            else{
                int flag3 = true;
                while(flag3){
                    display :: Payment_screen();
                    choice3 =  input :: take_input(0,2);
                    rent_detail r;
                    r.car_name = car_->get_name();
                    r.car_model = car_->get_model();
                    r.rented_date = dates :: getCurrentDateAsString();
                    int week;
                    week = how_many_week_screen(car_->get_price());
                    r.due_date = dates :: addWeeksToDate(r.rented_date, week);
                    r.rent_price = to_string((car_->get_price())*week);
                    r.is_late = "RENTED";
                    r.status = car_->get_condition();
                    r.car_idx = car_->get_id();
                    cout << "[To Confirm The Renting.Please ask Admin to Authenticate.]" << endl;
                    while(true){
                        cout <<"[Enter the Admin Password.]"<<endl;
                        string pass;
                        cin>>pass;
                        if(pass == m.get_password()){
                            cout << endl;
                            cout << "[ATHENTICATION SUCCESSFULL]" << endl;
                            cout << "[CAR RENTED SUCCESSFULLY!!]" << endl;
                            car_->set_avail(false);
                            car_->set_due_date(r.due_date);
                            customer *c_temp = customer_db.give_customer(c.get_name(), c.get_password()) ;
                            c_temp->add_car(r);
                            //c_temp->set_name("hero");
                            //cout << c_temp->no_of_rented_car() << endl;
                            //customer_db.write_to_database();
                            flag3 = false;
                            break;
                        }
                        else{
                            continue;
                        }
                    }
                    if(choice3 == 1){ //selected to pay now
                        continue;
                    }
                    else if(choice3 == 2){
                        c.set_fine_due(week*car_->get_price());
                    }
                    else{
                        display :: exiting();
                        break;
                    }
                }
            }
        }

}

void car_returning_menu(customer c , car_database &car_db , manager &m , customer_database &customer_db , int *choice5){
    vector<rent_detail> v = c.get_curr_rented_car();
    if(v.size() == 0) {
        cout << endl;
        cout << "NO CAR RENTED CURRENTLY." << endl;
        dates :: waitForSeconds(wait_sec);
        return;
    }
    display :: list_of_car_rented();
    customer *c_temp = customer_db.give_customer(c.get_name(), c.get_password()) ;
    int cnt = 1;
    for(auto rent : v){
        cout << "[" << cnt << "." << "]" << rent.car_name << " " <<rent.car_model << "." << endl;;
        cnt++;
    }
    *choice5 = input :: take_input(0, v.size());
    if(*choice5 == 0) return;
    else{
        if(!car_db.if_car_id_exits(v[(*choice5)-1].car_idx)){
            cout << "The Car doesn't exists in Database anymore. Please Contact Admin." << endl;
            dates :: waitForSeconds(wait_sec);
            return;
        }
        car* car_ = car_db.get_car_by_id(v[(*choice5)-1].car_idx);
        car_->set_avail(true);
        car_->set_due_date("AVAILABLE");
        display :: car_condition();
        int choice1 = input :: take_input(1, 3);

        string condition = v[(*choice5)-1].status;
        rent_detail *r = c_temp->get_rent_detail_by_idx(v[(*choice5)-1].car_idx);
        r->return_date = dates :: getCurrentDateAsString();
        bool late;
        late = dates :: isLaterDate(r->due_date, r->return_date);
        if(late == 1){
            c_temp->set_user_score(penalty_for_late_submission);
            r->is_late = "LATE";
            cout<< endl;
            cout << "Penalty for late Return : " << penalty_for_late_submission << endl;
            cout << "Updated user Score : " << c_temp->get_user_score() << endl;
            dates ::waitForSeconds(wait_sec);
        }
        else{
            r->is_late = "ON_TIME";
            c_temp->change_user_score(bonus_for_on_time_submission);
            cout << endl;
            cout << "Bonus for On Time Return : " << bonus_for_on_time_submission << endl;
            cout << "Updated user Score : " << c_temp->get_user_score() << endl;
            dates :: waitForSeconds(wait_sec);
        }
        
        switch(choice1){
            case(1):
                car_->set_condition("Excellent");
                if(condition == "Good"){
                    c_temp->set_user_score(bonus_good_to_excellent);
                    cout << "Bonus for improving Car Condition : " << bonus_good_to_excellent << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                    dates :: waitForSeconds(wait_sec);
                }
                else if(condition == "Bad"){
                    c_temp->set_user_score(bonus_bad_to_excellent);
                     cout << "Bonus for improving Car Condition : " << bonus_bad_to_excellent << endl;
                     cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                     dates :: waitForSeconds(wait_sec);
                }
                break;
            case(2):
                car_->set_condition("Good");
                if(condition == "Excellent"){
                    c_temp->set_user_score(penalty_excellent_to_good);
                    cout << "Penalty for making Car Condition worse : " << penalty_excellent_to_good << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                     dates :: waitForSeconds(wait_sec);
                }
                else if(condition == "Bad"){
                    c_temp->set_fine_due(bonus_bad_to_good);
                    cout << "Penalty for making Car Condition worse : " << bonus_bad_to_good << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                    dates :: waitForSeconds(wait_sec);
                }
                break;
            case(3):
                car_->set_condition("Bad");
                if(condition == "Good"){
                    c_temp->set_user_score(penalty_good_to_bad);
                    cout << "Penalty for making Car Condition worse : " << penalty_good_to_bad << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                    dates :: waitForSeconds(wait_sec);
                }
                else if(condition == "Excellent"){
                    c_temp->set_user_score(penalty_excellent_to_bad);
                    cout << "Penalty for making Car Condition worse : " << penalty_excellent_to_bad << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                    dates :: waitForSeconds(wait_sec);
                }
                break;
        }
        cout << "CAR IS SUCCESSFULLY RETURNED!" << endl;
        dates :: waitForSeconds(wait_sec);
        customer_db.write_to_database();
        customer_db.start_customer_database();
    }

}

void user_menu(customer c , car_database &car_db , manager &m , customer_database &customer_db){
    //car_db.start_car_database();
    int flag = true;
    while(flag){
        //cout << "entered" << endl;
        int choice;
        // int choice1;
        // int choice2;
        int choice3;
        int choice1 = -1;
        int *choice1_ptr = &choice1;
        int flag2 = true;
        display :: user_screen(c.get_name());
        choice = input :: take_input(0, 4);
        switch(choice){
            case(1):
                //car_db.show_car();
               
                while(flag2){
                    //car renting screen
                    if(choice1 !=0){
                        selecting_car_menu(c, car_db,m, customer_db, choice1_ptr);
                        continue;
                    }
                    else{
                        flag2 = false;
                        display :: exiting();
                        break;
                    }
                }
                break;

            case(2):
                    // To RETURN THE CAR
                    car_returning_menu(c, car_db, m, customer_db, choice1_ptr);
                    break;

            case(3):
                cout << endl;
                cout << "YOUR USER SCORE : " << c.get_user_score() << endl;
                cout << endl;
                dates :: waitForSeconds(2);
                break;
            case(4):
                display :: due_screen();
                cout << "YOUR DUE : " << c.get_fine_due() << endl;
                if(c.get_fine_due() == 0) {
                    cout << "YOU DONT HAVE ANY DUE." << endl;
                    dates :: waitForSeconds(2);
                    break;
                }
                choice3 = input ::take_input(0, 1);
                if(choice3 == 0){
                    break;
                }
                else{
                    int due;
                    cout << "[How Much Due you want to clear.]" << endl;
                    due = input :: take_input(1, c.get_fine_due());
                    customer *c_temp = customer_db.give_customer(c.get_name(), c.get_password());
                    c_temp->set_fine_due(c.get_fine_due()-due);
                    cout << "DUE CLEARED!!" << endl;
                    break;

                }
            case(0):
                flag = false;
                break;

        }
    }
}



void employee_selecting_car_menu(employee c , car_database &car_db , manager &m , employee_database &customer_db , int *choice1){
        int choice2;
        int choice3;
        while(true){
            car_db.show_car();
            display :: car_renting_screen(1 , car_db.get_no_of_car());
            *choice1 = input :: take_input(0,car_db.get_no_of_car());
            if(*choice1==0) return;
            car *car_ = car_db.get_car(*choice1);
            car_db.display_car_info(*choice1);
            cout << endl;
            // Selecting the car to rent it
            display ::renting_screen(1, car_db.get_no_of_car());
            int flag4 = true;
            while(true){
                choice2 = input :: take_input(0,1);
                if(choice2 == 0) break;
                if(choice2 == 1 && car_->get_is_avail()){
                    break;
                }
                else{
                    cout << "--------SORRY THIS CAR IS NOT AVAILABLE TO RENT!!----------" << endl;
                    cout << "--------PLEASE CHECK AVAILABILITY DATE---------------------" << endl;
                    cout <<"\n\n" << endl;
                    flag4 = false;
                    break;
                }
            }
            if(c.get_user_score()<minimum_score_to_rent || c.get_fine_due()>maximum_due_allowed) {
                    cout << "~~~~SORRY YOU ARE NOT ELIGIBLE TO RENT A CAR!~~~~" << endl;
                    if(c.get_user_score()<minimum_score_to_rent){
                        cout << "~~~~YOUR SCORE IS TOO LOW~~~~"<<endl;
                        cout << "SCORE :" << " " << c.get_user_score() << endl;
                        cout<< endl;
                    }
                    else{
                        cout << "~~~~PLEASE CLEAR YOUR DUES FIRST~~~~" << endl;
                        cout << "DUE : " << " " << c.get_fine_due() << endl;
                        cout << endl;
                    }   
                dates :: waitForSeconds(2);
                break; 
            }
            if(!flag4) continue;
            
            if(choice2 == 0){
                display :: exiting();
                break;
            }
            else{
                int flag3 = true;
                while(flag3){
                    display :: Payment_screen();
                    choice3 =  input :: take_input(0,2);
                    employee_rent_detail r;
                    r.car_name = car_->get_name();
                    r.car_model = car_->get_model();
                    r.rented_date = dates :: getCurrentDateAsString();
                    int week;
                    week = how_many_week_screen(car_->get_price());
                    r.due_date = dates :: addWeeksToDate(r.rented_date, week);
                    r.rent_price = to_string(int((car_->get_price())*week*c.get_discount()));
                    r.is_late = "RENTED";
                    r.status = car_->get_condition();
                    r.car_idx = car_->get_id();
                    cout << "To Confirm The Renting.Please ask Admin to Authenticate.?" << endl;
                    while(true){
                        cout <<"Enter the Admin Password."<<endl;
                        string pass;
                        cin>>pass;
                        if(pass == m.get_password()){
                            cout << "ATHENTICATION SUCCESSFULL" << endl;
                            cout << "CAR RENTED SUCCESSFULLY!!" << endl;
                            car_->set_avail(false);
                            car_->set_due_date(r.due_date);
                            employee *c_temp = customer_db.give_customer(c.get_name(), c.get_password()) ;
                            c_temp->add_car(r);
                            //c_temp->set_name("pulkit");
                            flag3 = false;
                            break;
                        }
                        else{
                            continue;
                        }
                    }
                    if(choice3 == 1){ //selected to pay now
                        continue;
                    }
                    else if(choice2 == 2){
                        c.set_fine_due(week*car_->get_price());
                    }
                    else{
                        display :: exiting();
                        break;
                    }
                }
            }
        }

}

void employee_car_returning_menu(employee c , car_database &car_db , manager &m , employee_database &customer_db , int *choice5){
    vector<employee_rent_detail>v = c.get_curr_rented_car();
    //cout << v.size() ;
    if(v.size() == 0) {
        cout << "NO CAR RENTED CURRENTLY." << endl;
        return;
    }
    display :: list_of_car_rented();
    employee *c_temp = customer_db.give_customer(c.get_name(), c.get_password()) ;
    int cnt = 1;
    for(auto rent : v){
        cout << "[" << cnt << "." << "]" << rent.car_name << " " <<rent.car_model << "." << endl;;
        cnt++;
    }
    *choice5 = input :: take_input(0, v.size());
    if(*choice5 == 0) return;
    else{
        if(!car_db.if_car_id_exits(v[(*choice5)-1].car_idx)){
            cout << "The Car doesn't exists in Database anymore. Please Contact Admin." << endl;
            dates :: waitForSeconds(wait_sec);
            return;
        }
        car* car_ = car_db.get_car_by_id(v[(*choice5)-1].car_idx);
        car_->set_avail(true);
        car_->set_due_date("AVAILABLE");
        display :: car_condition();
        int choice1 = input :: take_input(1, 3);
        string condition = v[(*choice5)-1].status;
        employee_rent_detail *r = c_temp->get_rent_detail_by_idx(v[(*choice5)-1].car_idx);
        r->return_date = dates :: getCurrentDateAsString();
        bool late;
        late = dates :: isLaterDate(r->due_date, r->return_date);
        if(late == 1){
            c_temp->set_user_score(penalty_for_late_submission);
            r->is_late = "LATE";
            cout<< endl;
            cout << "Penalty for late Return : " << penalty_for_late_submission << endl;
            cout << "Updated user Score : " << c_temp->get_user_score() << endl;
            dates ::waitForSeconds(wait_sec);
        }
        else{
            r->is_late = "ON_TIME";
            c_temp->change_user_score(bonus_for_on_time_submission);
            cout << endl;
            cout << "Bonus for On Time Return : " << bonus_for_on_time_submission << endl;
            cout << "Updated user Score : " << c_temp->get_user_score() << endl;
            dates :: waitForSeconds(wait_sec);
        }
        
        switch(choice1){
            case(1):
                car_->set_condition("Excellent");
                if(condition == "Good"){
                    c_temp->set_user_score(bonus_good_to_excellent);
                     cout << "Bonus for improving Car Condition : " << bonus_good_to_excellent << endl;
                     cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                     dates :: waitForSeconds(wait_sec);
                }
                else if(condition == "Bad"){
                    c_temp->set_user_score(bonus_bad_to_excellent);
                    cout << "Bonus for improving Car Condition : " << bonus_bad_to_excellent << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                    dates :: waitForSeconds(wait_sec);
                }
                break;
            case(2):
                car_->set_condition("Good");
                if(condition == "Excellent"){
                    c_temp->set_user_score(penalty_excellent_to_good);
                    cout << "Penalty for making Car Condition worse : " << penalty_excellent_to_good << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                    dates :: waitForSeconds(wait_sec);
                }
                else if(condition == "Bad"){
                    c_temp->set_fine_due(bonus_bad_to_good);
                    cout << "Penalty for making Car Condition worse : " << bonus_bad_to_good << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                    dates :: waitForSeconds(wait_sec);
                }
                break;
            case(3):
                car_->set_condition("Bad");
                if(condition == "Good"){
                    c_temp->set_user_score(penalty_good_to_bad);
                    cout << "Penalty for making Car Condition worse : " << penalty_good_to_bad << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                    dates :: waitForSeconds(wait_sec);
                }
                else if(condition == "Excellent"){
                    c_temp->set_user_score(penalty_excellent_to_bad);
                    cout << "Penalty for making Car Condition worse : " << penalty_excellent_to_bad << endl;
                    cout << "Updated user Score : " << c_temp->get_user_score() << endl;
                    dates :: waitForSeconds(wait_sec);
                }
                break;
        }
        cout << "CAR IS SUCCESSFULLY RETURNED!" << endl;
        dates :: waitForSeconds(wait_sec);

    }

}

void employee_user_menu(employee c , car_database &car_db , manager &m , employee_database &customer_db){
    //car_db.start_car_database();
    int flag = true;
    while(flag){
        //cout << "entered" << endl;
        int choice;
        // int choice1;
        // int choice2;
        // int choice3;
        int choice1 = -1;
        int *choice1_ptr = &choice1;
        int flag2 = true;
        display :: user_screen(c.get_name());
        choice = input :: take_input(0, 3);
        switch(choice){
            case(1):
                //car_db.show_car();
               
                while(flag2){
                    //car renting screen
                    if(choice1 !=0){
                        employee_selecting_car_menu(c, car_db,m, customer_db, choice1_ptr);
                        continue;
                    }
                    else{
                        flag2 = false;
                        display :: exiting();
                        break;
                    }
                }
                break;

            case(2):
                    // To RETURN THE CAR
                    employee_car_returning_menu(c, car_db, m, customer_db, choice1_ptr);
                    break;
            case(3):
                cout << endl;
                cout << "YOUR USER SCORE : " << c.get_user_score() << endl;
                cout << endl;
                dates :: waitForSeconds(2);
                break;
            case(0):
                flag = false;
                break;
        }
    }
}

void admin_menu(car_database &car_db , manager m){
    int flag = true;
     while(flag){
        display :: manager_screen();
        int choice;
        choice = input::take_input(1 , 3);
        switch(choice)
        {
            case(1):
                car_db.add_car();
                car_db.write_to_database();
                break;
            case(2):
                if(car_db.get_no_of_car() == 0){
                    cout << "~~~~~~GARAGE IS EMPTY.~~~~~~~" << endl;
                    dates :: waitForSeconds(2);
                }
                cout << "WHICH CAR YOU WANT TO REMOVE?" << endl;
                car_db.show_car();
                cout << "#     [0.]GO BACK    " << endl;
                int idx;
                idx = input ::take_input(0, car_db.get_no_of_car());
                if(idx == 0){
                    break;
                }
                car_db.remove_car(idx);
                car_db.write_to_database();
                cout << "-----Car Removed Successfully----" << endl;
                dates :: waitForSeconds(2);
                break;
            case(3):
                car_db.write_to_database();
                flag = false;
                break;
        }
     }
     
     
}



int main() {
    customer_database customer_db;
    customer_db.start_customer_database();
    car_database car_db;
    car_db.start_car_database();
    employee_database employee_db;
    employee_db.start_employee_database();
    manager m;
    customer c_temp(1,"","",1);
    bool flag = true;
    while(flag){
        customer user(1,"","",0);
        employee empl(1,"","",0);
        manager m;
        display :: main_screen();
        int choice;
        choice = input :: take_input(first_index_of_option_screen,last_index_of_option_screen);
        switch(choice){
            case (1):
                display :: is_employee_or_manager();
                while(true){
                    int choose;
                    choose = input :: take_input(0, 2);
                    if(choose == 0){
                        break;
                    }
                    else if(choose == 1){
                        customer_db.add_customer();
                        customer_db.write_to_database();
                        break;
                    }
                    else if(choose == 2){
                        employee_db.add_customer();
                        employee_db.write_to_database();
                        break;
                    }
                }
                break;
            case (2):
                user = auth :: login(customer_db);
                //cout << user.get_name() <<endl;
                user_menu(user, car_db , m , customer_db);
                break; 
            case (3):
                empl = auth :: employee_login(employee_db);
                employee_user_menu(empl, car_db, m, employee_db);
                //cout << "hello" << endl;
                break;
            case(4):
                m = auth :: login_admin();
                admin_menu(car_db , m);
                car_db.start_car_database();
                break;
            case(5):
                car_db.write_to_database();
                customer_db.write_to_database();
                employee_db.write_to_database();
                flag = false;
                break;
        }   
    }
}
