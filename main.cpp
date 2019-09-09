/* 
 * File:   main.cpp
 * Author: stephenlucas
 *
 * Created on August 26, 2019, 9:22 AM
 */

#include <cstdlib>
#include <iostream>;
#include <fstream>
#include <string>
#include<ctime>;

using namespace std;

//Global variable definitions 
int SEED;
int INIT_TIME;
int FIN_TIME;
int ARRIVE_MIN;
int ARRIVE_MAX;
double QUIT_PROB;
int CPU_MIN;
int CPU_MAX;
int DISK1_MIN;
int DISK1_MAX;
int DISK2_MIN;
int DISK2_MAX;

//Returns a random int for the process arrival between global ints ARRIVE_MIN and ARRIVE_MAX
int ArrivalRandomInterval(){
    cout<<"Performing Arrival Random Interval:\n";
    return rand() % ::ARRIVE_MAX + ::ARRIVE_MIN;
}

//The amount of time process will stay there for is a random integer between constants CPU_MIN and CPU_MAX. 
int RunRandomInterval(){
    cout<<"Performing Run Random Interval:\n";
    return rand() % ::CPU_MAX + ::CPU_MIN;
}

//Determine a random interval for how long a process executes in the respective disk for
int Disk1RandomInterval(){
    cout<<"Performing Disk1 Random Interval:\n";
    return rand() % ::DISK1_MAX + ::DISK1_MIN;
}

//Determine a random interval for how long a process executes in the respective disk for
int Disk2RandomInterval(){
    cout<<"Performing Disk2 Random Interval:\n";
    return rand() % ::DISK2_MAX + ::DISK2_MIN;
}

//Reads input file to initialize global variables and prints them to screen
void InitializeVariables(){
    double line;
    ifstream myFile ("Input.txt");
    if (myFile.is_open())
    {
        myFile >> line;
        cout << "SEED: " << line << '\n';
        ::SEED = line;
        
        myFile >> line;
        cout << "INIT_TIME: " << line << '\n';
        ::INIT_TIME = line;
        
        myFile >> line;
        cout << "FIN_TIME: " << line << '\n';
        ::FIN_TIME = line;
        
        myFile >> line;
        cout << "ARRIVE_MIN: " << line << '\n';
        ::ARRIVE_MIN = line;
        
        myFile >> line;
        cout << "ARRIVE_MAX: " << line << '\n';
        ::ARRIVE_MAX = line;
        
        myFile >> line;
        cout << "QUIT_PROB: " << line << '\n';
        ::QUIT_PROB = line;
        
        myFile >> line;
        cout << "CPU_MIN: " << line << '\n';
        ::CPU_MIN = line;
        
        myFile >> line;
        cout << "CPU_MAX: " << line << '\n';
        ::CPU_MAX = line;
        
        myFile >> line;
        cout << "DISK1_MIN: " << line << '\n';
        ::DISK1_MIN = line;
        
        myFile >> line;
        cout << "DISK1_MAX: " << line << '\n';
        ::DISK1_MAX = line;
        
        myFile >> line;
        cout << "DISK2_MIN: " << line << '\n';
        ::DISK2_MIN = line;
        
        myFile >> line;
        cout << "DISK2_MAX: " << line << '\n';
        ::DISK2_MAX = line;
        
        myFile.close();
    }

    else cout << "Unable to open file"; 
}

//Write the values of the global variables to the Log, Overwriting the Log.txt file
void LogVariables(){
    ofstream Log;
    Log.open("Log.txt");
    cout << "LOGGING VARIABLES..." << endl <<endl;
    Log << "***GLOBAL VARIABLES***" << endl;
    Log << "SEED: " << ::SEED << endl;
    Log << "INIT_TIME: " << ::INIT_TIME << endl;
    Log << "FIN_TIME: " << ::FIN_TIME << endl;
    Log << "ARRIVE_MIN: " << ::ARRIVE_MIN << endl;
    Log << "ARRIVE_MAX: " << ::ARRIVE_MAX << endl;
    Log << "QUIT_PROB: " << ::QUIT_PROB << endl;
    Log << "CPU_MIN: " << ::CPU_MIN << endl;
    Log << "CPU_MAX: " << ::CPU_MAX << endl;
    Log << "DISK1_MIN: " << ::DISK1_MIN << endl;
    Log << "DISK1_MAX: " << ::DISK1_MAX << endl;
    Log << "DISK2_MIN: " << ::DISK2_MIN << endl;
    Log << "DISK2_MAX: " << ::DISK2_MAX << endl;
    Log << "**********************" << endl <<endl;
    Log.close();
}

/*
 * 
 */
int main(int argc, char** argv) {
    char data[100];
    srand(::SEED);
    
    InitializeVariables();
    LogVariables();
    
    //Open log file to append events to
    ofstream Log;
    Log.open("Log.txt", std::ios_base::app);
    
    cout << "Writing to the log file..." << endl;
    // write inputted data into the file.
    Log << "The arrival of a new job to the system" << endl;
    Log << "A job entering the CPU, Disk 1, or Disk 2" << endl;
    Log << "A job leaving the CPU, Disk 1, or Disk 2" << endl;
    Log << "A job exiting the system" << endl;
    Log << "The “simulation finished” event at FIN_TIME" << endl;
    

     // close the opened file.
    Log.close();
   
    /*
    //random interval test
    for(int i=0; i<100; i++){
        cout<<ArrivalRandomInterval()<<"\n";
    }//*/
    
    
    
    
   //Code for writing to stats and logs files:
   /*
   ofstream Statistics;
   Statistics.open("Statistics.txt");
   
   cout << "Writing to the file" << endl;
   cout << "Type your stats to test: "; 
   cin.getline(data, 100);
   
   // write inputted data into the file.
   Statistics << data << endl;
    
   // close the opened file.
   Statistics.close();
   
   //Appends to file
   ofstream Log;
   Log.open("Log.txt", std::ios_base::app);
   
   cout << "Writing to the file" << endl;
   cout << "Type Log test: "; 
   cin.getline(data, 100);
   
   // write inputted data into the file.
   Log << data << endl;
    
    // close the opened file.
   Statistics.close();
   //*/ 
    
   
   
    return 0;
}

