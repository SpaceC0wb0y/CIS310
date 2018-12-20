#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>
using namespace std;

string dectohex(int x);

vector <string> instructions = {"MOVE","ADD","SUB","TRAP","ORG","END"};
vector <string> operands = {"DO","#","$"};
int address;
string saddress;
string MC;
int operand1;
int main(){
    int length;
    string loop;
    cout << "Address" << " " << "MC" << " "<<"Operand" << " " << "Instructions" << endl;
    string sub;
    int i;
    ifstream myfile;
    string word;
    myfile.open("prog5.txt"); 
    while(getline(myfile, word)){
        
        if(word.find("ORG") != -1){
           i = word.find("$");
           sub = word.substr(i+1);
           address = stoul(sub, nullptr, 16); // Convert address to int
           
            
            
        }

        else if(word.find("MOVE") != -1){
            cout << dectohex(address) << " ";
            string operand;
            length = 2;
            if(word.find("#") != -1){
                length+=2;
                int x = word.find("#");
                operand = word.substr(x+1, 3) + " ";
                operand1 =  stoul(operand, nullptr, 10);
                operand=dectohex(operand1) + " ";
                    
                
                if(word.find("DO") != -1){
                    MC = "303C";
                    operand+=word.substr(word.find("DO"), 3);
                    
                    
                }
                else if(word.find("$") != -1){
                    length+= 4;
                    MC = "33FC";
                    operand+=word.substr(word.find("$"), (word.find("$")+2));
                    
                }
            }
            else if(word.find("$") != -1){
                length+=4;
                operand = word.substr(word.find("$"), 9);
                MC= "3039";
                if((word.find("DO") != -1)  && (word.find("$") > word.find("DO"))){
                    MC = "33CO";
                }
            }
            
            else if(word.find("DO") != -1){
                if( (word.find("$") != -1) && (word.find("DO") < word.find("$"))){
                    length+=4;
                    MC = "33C0";
                }
            }
           

            //address+=length;
            string instructions = word.substr(word.find("MOVE")); 
            
            cout << MC << " " <<operand << " " << instructions << endl;

        }

        else if(word.find("TRAP") != -1){
            cout << dectohex(address) << " ";
            length = 2;
            if(word.find("#0") != -1){
                MC = "4E40";
            }
            else if(word.find("#1") != -1){
                MC = "4E41";
            }
            else if(word.find("#2") != -1){
                MC = "4E42";
            }
            //address+=length;
            
            cout << MC << endl;
        }

        else if(word.find("ADDI") != -1){
            string operand;
            cout << dectohex(address) << " ";
            length = 2;
            if(word.find("#") != -1){
                length+=2;
                int x = word.find("#");
                operand = word.substr(x+1, 3) + " ";
                operand1 =  stoul(operand, nullptr, 10);
                operand=dectohex(operand1) + " ";
                if(word.find("DO") != -1){
                    MC = "0640";
                }
                else if(word.find("$") != -1){
                    operand+=word.substr(word.find("$"), (word.find("$")+2));
                    length+=4;
                    MC = "0679";
                }
            }
            //address+=length;
            string instructions = word.substr(word.find("ADDI")); 
            
            cout << MC << " " <<operand << " " << instructions << endl;
            
            
        }
        else if(word.find("ADD") != -1){
            string operand;
            cout << dectohex(address) << " ";
            length = 2;
            
            if(word.find("$")){
                int x = word.find("$");
                 operand = word.substr(word.find("$"), 9);
                length+=4;
                if(word.find("DO") != -1){
                    MC = "D079";
                }
                /*if((word.find("DO") != -1)  && (word.find("$") > word.find("DO"))){
                    MC = "D079";
                }*/

            }
            else if(word.find("DO") != -1){
                
                if(word.find("$") != -1){
                int x = word.find("$");
                 operand = word.substr(word.find("$"), (word.find("$")+2));
                
                    length+= 4;
                    MC = "D179";
                }
            }
            
            //address+=length;
            
             string instructions = word.substr(word.find("ADD")); 
            
            cout << MC << " " <<operand << " " << instructions << endl;
        }
        else if(word.find("SUBI") != -1){
            cout << dectohex(address) << " ";
            length = 2;
            if(word.find("#") != -1){
                length+=2;
                if(word.find("DO") != -1){
                    MC = "0440";
                }
                else if(word.find("$") != -1){
                    length+=4;
                    MC = "0479";
                }
            }
            //address+=length;
           
            cout << MC << endl;
        }
        else if(word.find("SUB") != -1){
            cout << dectohex(address) << " ";
            int length = 2;
            if(word.find("$")){
                length+=4;
                if(word.find("DO") != -1){
                    MC = "9079";
                }

            }
            else if(word.find("DO") != -1){
                if(word.find("$") != -1){
                    length+= 4;
                    MC = "9179";
                }
            }
            //address+=length;
            
            cout << MC << endl;
        }
        if(word.find("LOOP") != -1){
            
            loop += word.substr(word.find("LOOP"), 5) + " " + dectohex(address) + "\n";
        }
        address+=length;
    };
    
    cout << endl << loop << endl;
}

string dectohex(int p_intValue)
{
    std::stringstream stream;
    stream << hex << p_intValue; 
    string saddress( stream.str() ); // reconvert back to hex
    return saddress;
}