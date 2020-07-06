#include "dlist.h"
#include <iostream>
#include <sstream>

using namespace std;

struct event{
    int timestamp;
    string name;
    int status;//0 for regular, 1 for silver, 2 for gold, 3 for platinum
    int duration;
};

const static string member[]={"regular","silver","gold","platinum"};

int main(){
    istringstream temp;
    string input;
    int num_event,time_cost=0, time_needed=0, tick=0, iter=0;
    event* cand_event=nullptr;
    const event* present_event=nullptr;
    Dlist<event> event_array,waiting_plat,waiting_gold,waiting_sil,waiting_reg;
    Dlist<event>* waiting_events[] = {&waiting_reg,&waiting_sil,&waiting_gold,&waiting_plat};
    //input num of event
    cin>>num_event;
    cin.ignore(1024,'\n');
    //input events
    while(iter<num_event){
        string s_status;
        getline(cin,input);
        temp.str(input);
        event* ne = new event;
        temp>>ne->timestamp;
        temp>>(ne->name);
        temp>>s_status;
        for(int ii=0; ii<4; ii++){
            if(member[ii]==s_status){
                ne->status = ii;
                break;
            }
        }
        temp>>(ne->duration);
        temp.str("");
        temp.clear();
        event_array.insertBack(ne);
        iter++;
    }
    
    if(!event_array.isEmpty()) cand_event = event_array.removeFront();
    else cout<<"Starting tick #0"<<endl;
    while(!event_array.isEmpty()||!waiting_events[0]->isEmpty()||present_event!=nullptr||cand_event!=nullptr){
        cout<<"Starting tick #"<<tick<<endl;
        if(cand_event!=nullptr){
            while(cand_event->timestamp == tick){
                waiting_events[cand_event->status]->insertBack(cand_event);
                cout<<"Call from "<<cand_event->name<<" "<<"a "<<member[cand_event->status]<<" member"<<endl;
                if(!event_array.isEmpty()) cand_event = event_array.removeFront();
                else{
                    cand_event = nullptr;
                    break;
                }
            }
        }
        if(time_cost==time_needed){
            if(present_event!=nullptr){ 
                delete present_event;
                present_event = nullptr;
            }
            for(int ii=0;ii<4;ii++){
                if(!waiting_events[3-ii]->isEmpty()){
                    present_event = waiting_events[3-ii]->removeFront();
                    time_cost = 0;
                    time_needed =present_event->duration;
                    break;
                }
            }
        }
        if(time_cost<time_needed){
            if(time_cost == 0) cout<<"Answering call from "<<present_event->name<<endl;
            time_cost++;
        }
       tick++;
    }
    return 0; 
}

