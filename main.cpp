#include <iostream>
#include <time.h>
#include <vector>
#include <string>

using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;
using std::to_string;

class Person{
private:
    int index;
    int days_sick = 0;
    int days_vaccine_to_immune = 0;
    string current_status = "well";
    bool is_inoc = false;
    bool is_infected = false;
public:
    Person(){}
    Person(int num){
        index = num;
    }
    Person(bool infect, int days){
        current_status = "infected";
        is_infected = true;
        days_sick = days;
    }
    void update_status(){
        if(is_infected){
            if(days_sick--<=0){
                is_infected = false;
                is_inoc = true;
                current_status = "inoculated";
            }

        }
    }
    void infect_person(int days){
        if(!is_inoc && !is_infected){
            current_status = "infected";
            is_infected = true;
            days_sick = days;
        }
    }
void inoculate_person(){
        is_infected = false;
        is_inoc = true;
        current_status = "inoculated";
    }
int days_remaining(){
        return days_sick;
    }
string get_status(){
        return current_status;
    }
};

class Population{
private:
    vector<Person> people;
    int pop_size;
public:
    Population(){
        srand(time(NULL));
    }
    Population(int size, int days_sick){
        srand(time(NULL));
        pop_size = size;

        Person p(true, days_sick);
        people.push_back(p);
        for(int i = 1; i < size; i++){
            Person p(i);
            people.push_back(p);
        }
    }
    vector<Person> get_people(){
        return people;
    }

    void update_status(int number_of_interactions){
        int r;
        int index = 0;
        int chance;
        vector<Person> sick;

        for(Person &p:people){
            p.update_status();
            for(int i = 0; i < number_of_interactions; i++){
                r = rand() %pop_size;

                Person xp = people[r];
                sick.push_back(xp);
            }
            index++;
        }
        for(Person &p: sick){
            p.infect_person(5);
        }


    }
  void infect_pop(){
        int r;
        for(Person &p: people){
            r = rand() % 100;
            if(r < 25){
                p.infect_person(5);
            }
        }
    }
bool is_sick(int probability){
        int luck = rand() % 101;
        if(luck < probability){
            return true;
        }else{
            return false;
        }
    }
int get_num_sick(){
        int sick_ctr = 0;
        for(Person &p:people){
            if(p.get_status() == "infected"){
                sick_ctr++;
            }
        }
        return sick_ctr;
    }
int get_num_inoc(){
        int inoc_ctr = 0;
        for(Person &p:people){
            if(p.get_status() == "inoculated"){
                inoc_ctr++;
            }
        }
        return inoc_ctr;
    }

    int get_num_healthy(){
        int healthy_ctr = 0;
        for(Person &p: people){
            if(p.get_status() == "well"){healthy_ctr++;}
        }
        return healthy_ctr;
    }
    int get_num_vaccinated(){
        int vacc_ct = 0;
        for(Person &p: people){
            if(p.get_status() == "vaxxed"){
                vacc_ct++;
            }
        }
        return vacc_ct;
    }

};

int main(){

    Population pop(1000,5);
    cout << "Day: " << 1 << endl;
    cout << "Number sick is: " << pop.get_num_sick() << endl;
    cout << "Number inoc is: " << pop.get_num_inoc() << endl;
    cout << "Number uninfected is: " << pop.get_num_healthy() << endl;
    cout << endl;

    for(int day = 2; day < 30; day++) {
        pop.update_status(10);
        pop.infect_pop();

        cout << "Day: " << day << endl;
        cout << "Number sick is: " << pop.get_num_sick() << endl;
        cout << "Number inoculated is: " << pop.get_num_inoc() << endl;
        cout << "Number uninfected is: " << pop.get_num_healthy() << endl;
        cout << endl;
    }
    return 0;
}