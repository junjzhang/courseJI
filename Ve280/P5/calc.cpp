#include "dlist.h"
#include <iostream>
#include <string>

using namespace std;

const string operation = "+-*/ndrpcaq";
//Then the indexes of operations is the following: 0+ 1- 2* 3/ 4n 5d 6r 7p 8c 9a 10q  
int is_validInput(const string &input);
//EFFECTS: If the input is integer, then return -1. If the input is operation, then return the index of operation. Return -2 otherwise.
bool is_integer(const string &input);
//EFFECTS: If the input represent an interger, return true. Return false otherwise.

int main(){
    bool flag = true;
    int input_t;
    string input;
    Dlist<int> int_stack;
    int *temp1=nullptr, *temp2=nullptr, *temp3=nullptr;

    while(flag){
        cin>>input;
        cin.clear();
        input_t = is_validInput(input);
        if(input_t == -2){
            cout<<"Bad input"<<endl;
            continue;
        }
        //push integer to stack
        else if(input_t == -1){
            int* elt = new int(stoi(input));
            int_stack.insertFront(elt);
            continue;
        }
        //do operation
        else try{
                if(input_t<4||input_t == 6){
                    temp1 = int_stack.removeFront();
                    temp2 = int_stack.removeFront();
                    temp3 = new int;
                    switch (input_t){
                    case 0:
                        *temp3 = (*temp1)+(*temp2);
                        break;
                    case 1:
                        *temp3 = (*temp2)-(*temp1);
                        break;
                    case 2:
                        *temp3 = (*temp2)*(*temp1);
                        break;
                    case 3:
                        if(*temp1==0){
                            cout<<"Divide by zero"<<endl;
                            int_stack.insertFront(temp2);
                            int_stack.insertFront(temp1);
                            delete temp3;
                            continue;
                        }
                        *temp3 = (*temp2)/(*temp1);
                        break;
                    case 6:
                        int_stack.insertFront(temp1);
                        int_stack.insertFront(temp2);
                        delete temp3;
                    }
                    if(input_t<4){ 
                        int_stack.insertFront(temp3);
                        delete temp1;
                        delete temp2;
                    }
                    temp1 = temp2 = temp3 = nullptr;
                }
                else if(input_t==4||input_t==5||input_t==7){
                    temp1 = int_stack.removeFront();
                    switch (input_t){
                    case 4:
                        *temp1 = -*temp1;
                        break;
                    case 5:{
                        temp2 = new int(*temp1);
                        int_stack.insertFront(temp2);
                        break;
                    }
                    case 7:
                        cout<<*temp1<<endl;
                    }
                    int_stack.insertFront(temp1);
                    temp1 = temp2 = nullptr;
            }
        }
        catch(emptyList error){
            if (temp2!=nullptr) int_stack.insertFront(temp2);
            if (temp1!=nullptr) int_stack.insertFront(temp1);
            cout<<"Not enough operands"<<endl;
            temp1 = temp2 = nullptr;
            continue;
        }
        switch (input_t){
        case 8:
            while(!int_stack.isEmpty()){
                int* temp = int_stack.removeFront();
                delete temp;
            }
            break;
        case 9:{
            Dlist<int> temp_intStack(int_stack);
            while(!temp_intStack.isEmpty()){
                int* temp = temp_intStack.removeFront();
                cout<<*temp<<" "; 
                delete temp;
            }
            cout<<endl;
            break;
        }
        case 10:
            flag = false;
        }
    }
    return 0;
}

int is_validInput(const string& input){
    if(is_integer(input)) return -1;
    if (input.length()!=1) return -2;
    for(int ii=0; ii<int(operation.length()); ii++){
        if (input == operation.substr(ii,1)) {
            return ii;
        }
    }
    return -2;
}

bool is_integer(const string& input){
    int begin;
    begin = (input[0]=='-')?1:0;
    if (begin==1&&input.length()==1) return false;
    for(int ii = begin;ii<int(input.length());ii++){
        if (input[ii]-'0'>9||input[ii]-'0'<0) return false;
    }
    return true;
}
