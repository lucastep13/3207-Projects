/* 
 * File:   main.cpp
 * Author: stephenlucas
 *
 * Created on September 22, 2019, 8:20 PM
 */

#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include <sys/stat.h>
#include <fcntl.h>
pid_t fork( void );

using namespace std;

bool isLaunch=0;

//Function to return current working directory
std::string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

//Global variable to hold shell path
string ShellPath = GetCurrentWorkingDir();
 
//Function to clear the screen of shell
void clr(){
    printf("\033[H\033[2J");
}

//Function to change the current working directory and returns 0 if successful, -1 if not
int cd(string DirName){
    return chdir(DirName.c_str());
}

//Function to print help.txt file
void help(int launchType, string fileName){
    string line;                                    //Variable to store the line read
    string savePath=GetCurrentWorkingDir();         //Variable to hold the current directory
    
    cd(::ShellPath);                                //Change directory to shell path to get help.txt file
    
    fstream file;                                   //Variable to redirect output to
    ifstream myFile ("help.txt");
    
    //Set redirection to append and create file if it doesnt exist
    if(launchType == 2){
        file.open(fileName, ios::out | std::fstream::app |fstream::out); 
    }
    //Set redirection to truncate and create file if it doesnt exist
    if(launchType == 1){
        file.open(fileName, ios::out |fstream::out); 
    }
    
    
    // Backup streambuffers of  cout 
    streambuf* stream_buffer_cout = cout.rdbuf(); 
    streambuf* stream_buffer_cin = cin.rdbuf(); 
    
    // Get the streambuffer of the file 
    streambuf* stream_buffer_file = file.rdbuf(); 
    
    //If launch type is 1 or 2, redirect cout to file 
    if(launchType != 0){
        cout.rdbuf(stream_buffer_file); }
    
    //While file is open, print contents of help.txt
    if (myFile.is_open())
        cout << myFile.rdbuf();
   
    
    myFile.close();
    cout<<endl;
    
    // Redirect cout back to screen 
    cout.rdbuf(stream_buffer_cout); 
    
    myFile.close();
   
    cd(savePath);
}

//String vector to hold directory contents for dir()
typedef std::vector<std::string> stringvec;

//Function to print the contents of the current directory,  or user specified directory
void dir(const std::string& name, stringvec& v, int launchType, string userFile)
{
    string fileName = userFile;                     //Variable to hold name of file to open
    fstream file;                                   //Variable to hold file to redirect output to
    
    //Set redirection to append and create file if it doesnt exist
    if(launchType == 2){
        file.open(fileName, ios::out | std::fstream::app |fstream::out); 
    }
    //Set redirection to truncate and create file if it doesnt exist
    if(launchType == 1){
        file.open(fileName, ios::out |fstream::out); 
    }
    
    
    // Backup streambuffers of  cout 
    streambuf* stream_buffer_cout = cout.rdbuf(); 
    streambuf* stream_buffer_cin = cin.rdbuf(); 
    
    // Get the streambuffer of the file 
    streambuf* stream_buffer_file = file.rdbuf(); 
    
    //If launch type is not 1 or 2, redirect cout to file 
    if(launchType != 0){
        cout.rdbuf(stream_buffer_file); 
    }
    
    //Clear the vector, then fill it with dir contents and sort it
    v.clear();
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) { 
        v.push_back(dp->d_name);
    }
    std::sort(v.begin(), v.end());
    closedir(dirp);
    
    //If launch type was not redirecting output, print contents to screen
    if(launchType!=0){
        for(int i; i< v.capacity(); i++){
            cout<<v[i];
            cout<<endl;
        }
    }
    
    // Redirect cout back to screen 
    cout.rdbuf(stream_buffer_cout); 
    
    file.close();
}

//Function to print user input
void echo(string myInput, int launchType, string userFile){
 
    string fileName = userFile;                 //Variable to hold file to open
    fstream file;                               //Variable to file to redirect to
    
    //Set redirection to append and create file if it doesnt exist
    if(launchType == 2){
        file.open(fileName, ios::out | std::fstream::app |fstream::out); 
    }
    //Set redirection to truncate and create file if it doesnt exist
    if(launchType == 1){
        file.open(fileName, ios::out |fstream::out); 
    }
    
    
    // Backup streambuffers of  cout 
    streambuf* stream_buffer_cout = cout.rdbuf(); 
    streambuf* stream_buffer_cin = cin.rdbuf(); 
    
    // Get the streambuffer of the file 
    streambuf* stream_buffer_file = file.rdbuf(); 
    
    //Redirect cout to file if launch type is 1 or 2
    if(launchType != 0){
        cout.rdbuf(stream_buffer_file); }
        cout<<myInput<<endl;
    
    // Redirect cout back to screen 
    cout.rdbuf(stream_buffer_cout); 
    
        file.close();
}

//Pauses shell until user presses enter
void pauseShell(){
    int c;                      //Variable to hold user input
    cout<<"****************"
        <<"\n* SHELL PAUSED *"
        <<"\n****************\n";

    //Loop until user presses return key
    do {
        c=getchar();
    } while (c != '\n');
}

//Function to print environment variables
void environ(int launchType, string userFile){
    char* pPath;                    //Variable to hold pointer to environ variable
    
    string fileName = userFile;     //Variable to hold user file to open
    fstream file;                   //Variable to hold file to direct output to
    
    //Set redirection to append and create file if it doesnt exist
    if(launchType == 2){
        file.open(fileName, ios::out | std::fstream::app |fstream::out); 
    }
    //Set redirection to truncate and create file if it doesnt exist
    if(launchType == 1){
        file.open(fileName, ios::out |fstream::out); 
    }
    
    // Backup streambuffers of  cout 
    streambuf* stream_buffer_cout = cout.rdbuf(); 
    streambuf* stream_buffer_cin = cin.rdbuf(); 
    
    // Get the streambuffer of the file 
    streambuf* stream_buffer_file = file.rdbuf(); 
    
    //Redirect cout to file if launch type is 1 or 2
    if(launchType != 0){
        cout.rdbuf(stream_buffer_file);}
   
    
    //Go through all the environment variables
    //If it is found, print to screen or file
    pPath = getenv ("TERM_PROGRAM");
    if (pPath!=NULL)
        cout<< "TERM_PROGRAM: "<<pPath;
    else
        cout<<"TERM_PROGRAM: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("SHELL");
    if (pPath!=NULL)
        cout<<"SHELL: "<<pPath;
    cout<<endl;
    
    pPath = getenv("TERM");
    if (pPath!=NULL)
        cout<<"TERM: "<< pPath;
    cout<<endl;
    
    pPath = getenv("TMPDIR");
    if (pPath!=NULL)
        cout<<"TMPDIR: "<<pPath;
    cout<<endl;
    
    pPath = getenv("Apple_PubSub_Socket_Render");
    if (pPath!=NULL)
        cout<<"Apple_PubSub_Socket_Render: "<<pPath;
    cout<<endl;
    
    pPath = getenv ("TERM_PROGRAM_VERSION");
    if (pPath!=NULL)
        cout<<"TERM_PROGRAM_VERSION: "<<pPath;
    else
        cout<<"TERM_PROGRAM_VERSION: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("TERM_SESSION_ID");
    if (pPath!=NULL)
        cout<<"TERM_SESSION_ID: "<<pPath;
    else
        cout<<"TERM_SESSION_ID: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("USER");
    if (pPath!=NULL)
        cout<<"USER: "<<pPath;
    else
        cout<<"USER: NOT FOUND!";
    cout<<endl;
    
     pPath = getenv ("SSH_AUTH_SOCK");
    if (pPath!=NULL)
        cout<<"SSH_AUTH_SOCK: "<<pPath;
    else
        cout<<"SSH_AUTH_SOCK: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("PATH");
    if (pPath!=NULL)
        cout<<"PATH: "<<pPath;
    else
        cout<<"PATH: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("CSSCRIPT_DIR");
    if (pPath!=NULL)
        cout<<"CSSCRIPT_DIR: "<<pPath;
    else
        cout<<"CSSCRIPT_DIR: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv("PWD");
    if (pPath!=NULL)
        cout<<"PWD = " <<pPath;
    cout<<endl;
    
    pPath = getenv ("LANG");
    if (pPath!=NULL)
        cout<<"LANG: "<<pPath;
    else
        cout<<"LANG: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("XPC_FLAGS");
    if (pPath!=NULL)
        cout<<"XPC_FLAGS: "<<pPath;
    else
        cout<<"XPC_FLAGS: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("XPC_SERVICE_NAME");
    if (pPath!=NULL)
        cout<<"XPC_SERVICE_NAME: "<<pPath;
    else
        cout<<"XPC_SERVICE_NAME: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("SHLVL");
    if (pPath!=NULL)
        cout<<"SHLVL: "<<pPath;
    else
        cout<<"SHLVL: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("HOME");
    if (pPath!=NULL)
        cout<<"HOME: "<<pPath;
    else
        cout<<"HOME: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("LOGNAME");
    if (pPath!=NULL)
        cout<<"LOGNAME: "<<pPath;
    else
        cout<<"LOGNAME: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("DISPLAY");
    if (pPath!=NULL)
        cout<<"DISPLAY: "<<pPath;
    else
        cout<<"DISPLAY: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("SECURITYSESSIONID");
    if (pPath!=NULL)
        cout<<"SECURITYSESSIONID: "<<pPath;
    else
        cout<<"SECURITYSESSIONID: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("_");
    if (pPath!=NULL)
        cout<<"_: "<<pPath;
    else
        cout<<"_: NOT FOUND!";
    cout<<endl;
    
    pPath = getenv ("OLDPWD");
    if (pPath!=NULL)
        cout<<"OLDPWD: "<<pPath;
    else
        cout<<"OLDPWD: NOT FOUND!";
    cout<<endl;
    
    // Redirect cout back to screen 
    cout.rdbuf(stream_buffer_cout); 
    
    file.close();
}

//Function to launch external command in foreground of shell
void launch(char *Command){
  
    cout<<"\nLAUNCHING FOREGROUND: \n";
    
    char *argv[512];                        //Char array to hold command to execute
    char *str = Command;                    //Char pointer to tokenize command
    int init_size = strlen(str);            //Int to hold initial size of command
    char delim[] = " ";                     //Char used to tokenize the command
    
    int index =0;                           //Int to keep track of index of argv[] array
    
    char *ptr = strtok(str, delim);         //Char pointer used to hold the tokenized words
    
    argv[0] = ptr;                          
    index++;
    
    //While pointer is not null, store it in the argv[] array
    while(ptr != NULL)
    {   
        ptr = strtok(NULL, delim);
        if(ptr == NULL){
            break;
        }
        argv[index] = ptr;
        index++; 
    }
    argv[index] = NULL;
  
    int pid = fork();                   //Int variable to hold return value of fork()
    //If there was no error in fork
    if(pid >= 0){
        cout<<"argv: ";
        cout<<argv[0];
        //If in child process
        if(pid == 0){
            cout<<"\n\nargv: ";
            cout<<argv[0];
            //Overlay process to given command
            if(execvp(argv[0], argv) < 0){
                puts("ERROR EXECUTING COMMAND!");
            }
        }
        //If in parent process, wait for child to finish 
        else
        {
            int status = 0;
            wait(&status);
        }
    }
    else{
        puts("Forking error!");
    }
    
    ::isLaunch = 0;
}

//Function to launch given command in background
void launchBackground(char *Command){
  
    cout<<"\nLAUNCHING BACKGROUND: \n";              
    char *argv[512];                                 //Char array to hold command to execute
    char *str = Command;                             //Char pointer to tokenize command
    int init_size = strlen(str);                     //Int to hold initial size of command
    char delim[] = " ";                              //Char to tokenize command
    
    int index =0;                                    //Int to hold index of char array
    
    char *ptr = strtok(str, delim);                  //Char pointer used to hold the tokenized words
        
    argv[0] = ptr;
    index++;
    
    //While pointer is not null, store it in argv[] 
    while(ptr != NULL)
    {   
        ptr = strtok(NULL, delim);
        if(ptr == NULL){
            break;
        }
        argv[index] = ptr;
        index++;
            
    }
    argv[index] = NULL;
    
    int pid = fork();                   //Variable to hold return value of fork()
    //If no fork error
    if(pid >= 0){
        cout<<"argv: ";
        cout<<argv[0];
        //If in child process
        if(pid == 0){
            cout<<"\n\nargv: ";
            cout<<argv[0];
            //Overlay process with given command
            if(execvp(argv[0], argv) < 0){
                puts("ERROR EXECUTING COMMAND!");
            }
        }
    }
        
    else{
        puts("Forking error!");
    }
    
    ::isLaunch = 0;
}

//Function to redirect output and truncate the file
void Truncate(char *Command, char *outFile){
  
    cout<<"\nTruncating: \n";
    char *argv[512];
    char *str = Command;
    char *strCopy = Command;                //Holds copy of comand
    
    int init_size = strlen(str);
    char delim[] = " ";
    char *textFile =outFile;                //Holds file to direct output to
    int fileIndex;                          //Holds index the file name starts
    
    int index =0;
    
    char *ptr = strtok(str, delim);
    argv[0] = ptr;
    index++;
    
    //While pointer is not null, add to argv[] array
    while(ptr != NULL)
    {   
        ptr = strtok(NULL, delim);
        if(ptr == NULL){
            break;
        }
        argv[index] = ptr;

        index++;    
    }
    argv[index] = NULL;
    
    int pid = fork();
    if(pid >= 0){
        cout<<"\n\nargv: ";
            cout<<argv[0];
        if(pid == 0){
            //Open textfile to redirect output and truncate
            int outFile = open(textFile, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU| S_IRWXU
                               |S_IRWXG|S_IRWXO);

            //Close stdout, redirect output to file
            close(1);
            dup2(outFile, 1);
            close(outFile);

            if(execvp(argv[0], argv) < 0){
                puts("ERROR EXECUTING COMMAND!");
            }
            
        }
        else
        {
                int status = 0;
                wait(&status);
        }
    }
        
    else{
        puts("Forking error!");
    }
    
    ::isLaunch = 0;
}

//Function to launch command and append to given file
void Append(char *Command, char *outFile){
  
    cout<<"\nAppending: \n";
    
    //Variable to hold command information
    char *argv[512];                    
    char *str = Command;
    char *strCopy = Command;
    
    int init_size = strlen(str);
    char delim[] = " ";
    char *textFile =outFile;
    int fileIndex;
    
    int index =0;
    
    char *ptr = strtok(str, delim);
    argv[0] = ptr;
    index++;
    
    //While pointer is not null, 
    while(ptr != NULL)
    {   
        ptr = strtok(NULL, delim);
        if(ptr == NULL){
            break;
        }
        argv[index] = ptr;

        index++;

            
    }
    argv[index] = NULL;
    
    int pid = fork();
    if(pid >= 0){
        cout<<"\n\nargv: ";
        cout<<argv[0];
        if(pid == 0){
            //Open file, append to it or create if it does not exist
            int outFile = open(textFile, O_WRONLY|O_CREAT|O_APPEND, S_IRWXU| S_IRWXU
                               |S_IRWXG|S_IRWXO);

            //Close stdout, redirect it to out file
            close(1);
            dup2(outFile, 1);
            close(outFile);
            
            cout<<"\n\nargv: ";
            cout<<argv[0];
            //Overlay process with command
            if(execvp(argv[0], argv) < 0){
                puts("ERROR EXECUTING COMMAND!");
            }
            
        }
        else
        {
            int status = 0;
            wait(&status);
        }
    }
    else{
        puts("Forking error!");
    }
    
    ::isLaunch = 0;
}

//Function that returns an int that corresponds to command type to launch, 
int LaunchType(char *Command){
    
    int launchType =0;                 //Int that holds launch type
    
    //Parse the command
    for(int i=0; i<strlen(Command); i++){
        if(Command[i] == '&'){
            
            return 1;           //Launch in background
        }
        else if(Command[i] == '>'){
            if(Command[i+1] == '>'){
                return 4;       //Append
            }
            else
                return 3;           //Truncate
        }
        else if(Command[i] == '<'){
            return 5;               //Input redirect
        }
        
    }
    launchType = 2; 
    return launchType;
    
    
}

//Main function, runs shell 
int main(int argc, char** argv) {
    string Input;                   //String to hold user input
    string textFile;                //String to hold text file name
    
    char cFile[256];                //Char array to hold file name
    char cstr[Input.size()+1];      //Char array to input 
    char myCopy[Input.size()+1];    //Char array to hold copy of input
    
    int launchFunction =0;
 
    stringvec v;                    //Stringvec to hold dir contents
        
    //While user does not enter 'quit'
    while(Input!= "quit"){
        //If user enters 'clr'
        if(Input =="clr"){
                cout<< GetCurrentWorkingDir() << ": ";
            }
            else{
                if(!::isLaunch)
                cout<< GetCurrentWorkingDir() << ": ";
            }
        //Get user input
        getline(cin, Input);
        //If the input is a built-in command
        if(Input.substr(0, 3) == "clr" || Input.substr(0, 2) == "cd" || Input.substr(0, 3) == "dir" 
            || Input.substr(0, 4) == "echo" || Input.substr(0, 4) == "help" || Input.substr(0, 5) == "pause" 
            || Input.substr(0, 7) == "environ" || Input.substr(0, 4) == "quit"){
            
            //If user enters clr command, clear the screen
            if(Input == "clr"){
                clr();
            }
            //If user enters cd, change directory
            if(Input.substr(0, 2) == "cd"){
                //Handles the user just entering cd
                if(Input == "cd"){
                    cout<<"\nNo Path Specified!\n\n";
                }
                //Handles the input after the cd command
                else{
                    //If cd returns -1, the path doesn't exist
                    //Otherwise, change the directory to what follows the cd command

                    if(cd(Input.substr(3,Input.length()-1)) != 0 && Input.substr(2,1) == " "){
                        cout<<"\n\n******************"
                            <<"\n* PATH NOT FOUND *"
                            <<"\n******************\n\n";
                    }
                }
            }
            //If user enters dir, determine which command to run
            if(Input.substr(0, 3) == "dir"){
                //Handles the user just entering dir
                if(Input == "dir"){

                    dir(GetCurrentWorkingDir(), v,1,"cne.txt");
                    std::copy(v.begin(), v.end(),
                        std::ostream_iterator<std::string>(std::cout, "\n"));

                }
                //Handles user printing a specific directory
                else{
                    
                    if(Input.substr(3,1) == " "){
                        for(int i = 0; i< Input.length(); i++){
                      
                        if(Input.substr(i,1) == ">"){
                            //Append
                            if(Input.substr(i,2) == ">>"){
                                
                                textFile = Input.substr(i+3, Input.length()-1);
                                Input = Input.substr(4, (Input.length()-5)-textFile.length()-3);

                                strcpy(cstr, Input.c_str()); 
                                strcpy(cFile, textFile.c_str()); 

                                cout<<endl<<"Parsed Command: "<<Input<<Input.length();
                                cout<<endl<<"Parsed Text File: "<<textFile<<endl;
                                dir("/users/stephenlucas", v,2,textFile);

                                break;
                            }
                        }
                        //Print dir to screen
                        else{
                                dir(Input.substr(4, Input.length()-1), v,0," ");
                                std::copy(v.begin(), v.end(),
                                std::ostream_iterator<std::string>(std::cout, "\n"));
                                break;
                        }
                        }
                        
                    }
                }
            }
            //If user enters 'echo' 
            if(Input.substr(0, 4) == "echo"){
                //Handles the user just entering echo
                if(Input == "echo"){
                    cout<<"\nNothing to echo.";
                }
                //Handles the input after the echo command
                else{
                    for(int i = 0; i< Input.length(); i++){
                        if(Input.substr(i,1) == ">"){
                            //Append
                            if(Input.substr(i,2) == ">>"){
                                
                                textFile = Input.substr(i+3, Input.length()-1);
                                Input = Input.substr(5, (Input.length()-5)-textFile.length()-4);

                                strcpy(cstr, Input.c_str()); 
                                strcpy(cFile, textFile.c_str()); 

                                cout<<endl<<"Parsed Command: "<<Input;
                                cout<<endl<<"Parsed Text File: "<<textFile<<endl;
                                echo(Input, 2, textFile);

                                break;
                            }
                            //Truncate
                            else{
                                textFile = Input.substr(i+2, Input.length()-1);
                                Input = Input.substr(5, (Input.length()-5)-textFile.length()-3);

                                strcpy(cstr, Input.c_str()); 
                                strcpy(cFile, textFile.c_str()); 

                                cout<<endl<<"Parsed Command: "<<Input;
                                cout<<endl<<"Parsed Text File: "<<textFile<<endl;
                                echo(Input, 1, textFile);
                                break;
                            }
                        }
                        //Print to screen
                        else{
                            echo(Input, 0, " ");
                            break;
                        }
                    }            
                }
            }
            
            //If user enters 'help'
            if(Input.substr(0,4) == "help"){
                
                for(int i =0; i<Input.length(); i++){
                    
                    if(Input.substr(i,1) == ">"){
                        //Append
                        if(Input.substr(i,2) == ">>"){
                            cout<<"\nGOTCHTA at: "<<i;
                            textFile = Input.substr(i+3, Input.length());
                            Input = Input.substr(0,i-1);

                            strcpy(cstr, Input.c_str()); 
                            strcpy(cFile, textFile.c_str()); 

                            cout<<endl<<"Parsed Command: "<<Input;
                            cout<<endl<<"Parsed Text File: "<<textFile<<endl;

                            help(2, textFile);
                            break;
                        }
                        //Truncate
                        else{
                            textFile = Input.substr(i+2, Input.length());
                            Input = Input.substr(0,i-1);

                            strcpy(cstr, Input.c_str()); 
                            strcpy(cFile, textFile.c_str()); 

                            cout<<endl<<"Parsed Command: "<<Input;
                            cout<<endl<<"Parsed Text File: "<<textFile<<endl;

                            help(1, textFile);
                            break;
                            
                        }
                    }
                    //Print help.txt to screen
                    else{
                        if(Input.length() == 4){
                            help(0, "test2.txt");
                            break;
                        }
                    }
                }       
            }
            //If user enters 'pause'
            if(Input == "pause"){
                pauseShell();
            }
            //If user enters 'environ'
            if(Input.substr(0,7) == "environ"){
                for(int i =0; i<Input.length(); i++){
                    cout<<Input.substr(i,1);
                    if(Input.substr(i,1) == ">"){
                        //Append
                        if(Input.substr(i,2) == ">>"){
                            cout<<"\nGOTCHTA at: "<<i;
                            textFile = Input.substr(i+3, Input.length());
                            Input = Input.substr(0,i-1);

                            strcpy(cstr, Input.c_str()); 
                            strcpy(cFile, textFile.c_str()); 

                            cout<<endl<<"Parsed Command: "<<Input;
                            cout<<endl<<"Parsed Text File: "<<textFile<<endl;

                            environ(2, textFile);
                            break;
                        }
                        //Truncate
                        else{
                            textFile = Input.substr(i+2, Input.length());
                            Input = Input.substr(0,i-1);

                            strcpy(cstr, Input.c_str()); 
                            strcpy(cFile, textFile.c_str()); 

                            cout<<endl<<"Parsed Command: "<<Input;
                            cout<<endl<<"Parsed Text File: "<<textFile<<endl;

                            environ(1, textFile);
                            break;
                            
                        }
                    }
                    //Print to screen
                    else{
                        if(Input.length() == 7){
                             environ(0, " ");
                            break;
                        }
                    }
                }
               
            }
            //If user enters 'quit'
            if(Input == "quit"){
                cout<<"\n\n********************"
                    <<"\n* SHELL TERMINATED *"
                    <<"\n********************";
            }
        }
        //Run external commands
        else{
            cout<<"Attempting to load: "<< Input <<endl;
            ::isLaunch = 1;
            
            //Handle background command launch
            if(Input.substr(Input.length()-1,Input.length()-1) == "&"){
               Input = Input.substr(0, Input.length()-1);
               strcpy(cstr, Input.c_str());
               strcpy(myCopy, Input.c_str());    
               launchBackground(myCopy);
            }
           else{
               strcpy(cstr, Input.c_str());          //Copy char array because initial will be tokenized
                strcpy(myCopy, Input.c_str()); 
                //If launch type is 2, run in foreground
                if(LaunchType(myCopy) == 2){
                    launch(cstr);
                    
                }
                //Truncate 
                else if(LaunchType(myCopy) == 3){
                    cout<<"Truncating: ";
                    for(int i =0; i<Input.length(); i++){
                        //Parse for command and text file
                        if(Input.substr(i,1) == ">"){
                            
                            textFile = Input.substr(i+2, Input.length());
                            Input = Input.substr(0,i-1);
                            
                            strcpy(cstr, Input.c_str()); 
                            strcpy(cFile, textFile.c_str()); 
                            
                            cout<<endl<<"Parsed Command: "<<Input;
                            cout<<endl<<"Parsed Text File: "<<textFile;
                        }
                    }
                    //Launch truncate command
                    Truncate(cstr, cFile);
                }
                //Append
                else if(LaunchType(myCopy) == 4){
                    cout<<"Appending: ";
                    for(int i =0; i<Input.length(); i++){
                        
                        //Parse for command and text file
                        if(Input.substr(i,2) == ">>"){
                            
                            textFile = Input.substr(i+3, Input.length());
                            Input = Input.substr(0,i-1);
                            
                            strcpy(cstr, Input.c_str()); 
                            strcpy(cFile, textFile.c_str()); 
                            
                            cout<<endl<<"Parsed Command: "<<Input;
                            cout<<endl<<"Parsed Text File: "<<textFile;
                        }
                    }
                    //Launch append function
                    Append(cstr, cFile);
                }
                //Input redirection
                else if(LaunchType(myCopy) == 5){
                    cout<<"Input redirection: ";
                    for(int i =0; i<Input.length(); i++){
                        //Parse file for command and text file
                        if(Input.substr(i,1) == "<"){
                            int indexFound = i;
                            textFile = Input.substr(i+3, Input.length());
                            Input = Input.erase(i,2);
                            
                            strcpy(cstr, Input.c_str()); 
                            strcpy(cFile, textFile.c_str()); 
                            
                            cout<<endl<<"Parsed Command: "<<Input;
                            cout<<endl<<"Parsed Text File: "<<textFile;
                        }
                    }
                    //Launch command
                    launch(cstr);
               }
           }  
        }          
    }
    return 0;
}