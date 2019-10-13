/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
void help(){
    string line;
    string savePath=GetCurrentWorkingDir();
    
    cd(::ShellPath);
    
    ifstream myFile ("help.txt");
    
    
    if (myFile.is_open())
        std::cout << myFile.rdbuf();
    
    
    myFile.close();
    cout<<endl;
    
    cd(savePath);
}

//String vector to hold directory contents for dir()
typedef std::vector<std::string> stringvec;

//Function to print the contents of the current directory,  or user specified directory
void dir(const std::string& name, stringvec& v)
{
    v.clear();
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) { 
        v.push_back(dp->d_name);
    }
    std::sort(v.begin(), v.end());
    closedir(dirp);
}


//Function to print user input
void echo(string myInput){
	cout<<myInput<<endl;
}

//Pauses shell until user presses enter
void pauseShell(){
    int c;
    cout<<"****************"
        <<"\n* SHELL PAUSED *"
        <<"\n****************\n";

    do {
        c=getchar();
        
  } while (c != '\n');
}

//Function to print environment variables
void environ(){
    char* pPath;
    
    pPath = getenv ("TERM_PROGRAM");
    if (pPath!=NULL)
        printf ("TERM_PROGRAM: %s",pPath);
    else
        printf("TERM_PROGRAM: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("SHELL");
    if (pPath!=NULL)
        printf ("SHELL: %s",pPath);
    cout<<endl;
    
    pPath = getenv("TERM");
    if (pPath!=NULL)
        printf ("TERM: %s",pPath);
    cout<<endl;
    
    pPath = getenv("TMPDIR");
    if (pPath!=NULL)
        printf ("TMPDIR: %s",pPath);
    cout<<endl;
    
    pPath = getenv("Apple_PubSub_Socket_Render");
    if (pPath!=NULL)
        printf ("Apple_PubSub_Socket_Render: %s",pPath);
    cout<<endl;
    
    pPath = getenv ("TERM_PROGRAM_VERSION");
    if (pPath!=NULL)
        printf ("TERM_PROGRAM_VERSION: %s",pPath);
    else
        printf("TERM_PROGRAM_VERSION: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("TERM_SESSION_ID");
    if (pPath!=NULL)
        printf ("TERM_SESSION_ID: %s",pPath);
    else
        printf("TERM_SESSION_ID: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("USER");
    if (pPath!=NULL)
        printf ("USER: %s",pPath);
    else
        printf("USER: NOT FOUND!");
    cout<<endl;
    
     pPath = getenv ("SSH_AUTH_SOCK");
    if (pPath!=NULL)
        printf ("SSH_AUTH_SOCK: %s",pPath);
    else
        printf("SSH_AUTH_SOCK: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("PATH");
    if (pPath!=NULL)
        printf ("PATH: %s",pPath);
    else
        printf("PATH: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("CSSCRIPT_DIR");
    if (pPath!=NULL)
        printf ("CSSCRIPT_DIR: %s",pPath);
    else
        printf("CSSCRIPT_DIR: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv("PWD");
    if (pPath!=NULL)
        printf ("PWD = %s",pPath);
    cout<<endl;
    
    pPath = getenv ("LANG");
    if (pPath!=NULL)
        printf ("LANG: %s",pPath);
    else
        printf("LANG: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("XPC_FLAGS");
    if (pPath!=NULL)
        printf ("XPC_FLAGS: %s",pPath);
    else
        printf("XPC_FLAGS: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("XPC_SERVICE_NAME");
    if (pPath!=NULL)
        printf ("XPC_SERVICE_NAME: %s",pPath);
    else
        printf("XPC_SERVICE_NAME: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("SHLVL");
    if (pPath!=NULL)
        printf ("SHLVL: %s",pPath);
    else
        printf("SHLVL: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("HOME");
    if (pPath!=NULL)
        printf ("HOME: %s",pPath);
    else
        printf("HOME: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("LOGNAME");
    if (pPath!=NULL)
        printf ("LOGNAME: %s",pPath);
    else
        printf("LOGNAME: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("DISPLAY");
    if (pPath!=NULL)
        printf ("DISPLAY: %s",pPath);
    else
        printf("DISPLAY: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("SECURITYSESSIONID");
    if (pPath!=NULL)
        printf ("SECURITYSESSIONID: %s",pPath);
    else
        printf("SECURITYSESSIONID: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("_");
    if (pPath!=NULL)
        printf ("_: %s",pPath);
    else
        printf("_: NOT FOUND!");
    cout<<endl;
    
    pPath = getenv ("OLDPWD");
    if (pPath!=NULL)
        printf ("OLDPWD: %s",pPath);
    else
        printf("OLDPWD: NOT FOUND!");
    cout<<endl;
}

void launch(char *Command){
  
    cout<<"\nLAUNCHING FOREGROUND: \n";
    char *argv[512];
    char *str = Command;
    int init_size = strlen(str);
    char delim[] = " ";
    
    int index =0;
    
    char *ptr = strtok(str, delim);
    argv[0] = ptr;
    index++;
    
    while(ptr != NULL)
    {   
            printf("'%s'\n", ptr);
            ptr = strtok(NULL, delim);
            if(ptr == NULL){
                break;
            }
            argv[index] = ptr;
            index++;
            
    }
    argv[index] = NULL;
    
   
    cout<<"\nCommand Size: "<<strlen(Command);
    
    //char *argv[3] = {"wc", "help.txt"};
    //argv[2] = NULL; 
    
    
    cout<<"\n\n\n";

    
    int pid = fork();
    if(pid >= 0){
        cout<<"\n\nargv: ";
            cout<<argv[0];
        if(pid == 0){
            //int outFile = open("output.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU| S_IRWXU
                              // |S_IRWXG|S_IRWXO);

            //close(1);
            //dup2(outFile, 1);
            //close(outFile);

            //if(execvp(cmdString, argv) < 0){
           //     puts("ERROR EXECUTING COMMAND!");
           // }
            
            cout<<"\n\nargv: ";
            cout<<argv[0];
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

void launchBackground(char *Command){
  
    cout<<"\nLAUNCHING BACKGROUND: \n";
    char *argv[512];
    char *str = Command;
    int init_size = strlen(str);
    char delim[] = " ";
    
    int index =0;
    
    char *ptr = strtok(str, delim);
    argv[0] = ptr;
    index++;
    
    while(ptr != NULL)
    {   
            printf("'%s'\n", ptr);
            ptr = strtok(NULL, delim);
            if(ptr == NULL){
                break;
            }
            argv[index] = ptr;
            index++;
            
    }
    argv[index] = NULL;
    
   
    cout<<"\nCommand Size: "<<strlen(Command);
    
    //char *argv[3] = {"wc", "help.txt"};
    //argv[2] = NULL; 
    
    
    cout<<"\n\n\n";

    
    int pid = fork();cout<<"test";
    if(pid >= 0){
        cout<<"\n\nargv: ";
            cout<<argv[0];
        if(pid == 0){
            //int outFile = open("output.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU| S_IRWXU
                              // |S_IRWXG|S_IRWXO);

            //close(1);
            //dup2(outFile, 1);
            //close(outFile);

            //if(execvp(cmdString, argv) < 0){
           //     puts("ERROR EXECUTING COMMAND!");
           // }
            
            cout<<"\n\nargv: ";
            cout<<argv[0];
            if(execvp(argv[0], argv) < 0){
                puts("ERROR EXECUTING COMMAND!");
            }
            else{
                
            }
            
            
        }
    }
        
    else{
        puts("Forking error!");
    }
    
    ::isLaunch = 0;
}

int LaunchType(char *Command){
    
    int launchType =0;
    
    for(int i=0; i<strlen(Command); i++){
        cout<<Command[i];
        if(Command[i] == '&'){
            
            return 1;           //Launch in background
        }
        
    }
    launchType = 2; 
    return launchType;
    
    
}

/*
 * 
 */
int main(int argc, char** argv) {

    string Input;
    char cstr[Input.size()+1];
    char myCopy[Input.size()+1];
    
 
    
    stringvec v;
    //dir("/Users/stephenlucas", v);
    //std::copy(v.begin(), v.end(),
       //  std::ostream_iterator<std::string>(std::cout, "\n"));
    


    //std::cout << GetCurrentWorkingDir() << std::endl;
    //cd("/Users/stephenlucas/NetBeansProjects/ShellFork");
    
  /*
    FILE *handle = popen("./main", "r");

        if (handle == NULL) {
                return 1;
        }

        char buf[64];
        size_t readn;
        while ((readn = fread(buf, 1, sizeof(buf), handle)) > 0) {
                fwrite(buf, 1, readn, stdout);
        }

        pclose(handle);//*/
        
    while(Input!= "quit"){
        if(Input =="clr"){
                //Sets cursor to top of console
                //printf("\033[1;1H");

                cout<< GetCurrentWorkingDir() << ": ";
            }
            else{
                if(!::isLaunch)
                cout<< GetCurrentWorkingDir() << ": ";
            }
        getline(cin, Input);
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

             //If user enters cd, change directory
            if(Input.substr(0, 3) == "dir"){



                //Handles the user just entering cd
                if(Input == "dir"){

                    dir(GetCurrentWorkingDir(), v);
                    std::copy(v.begin(), v.end(),
                        std::ostream_iterator<std::string>(std::cout, "\n"));

                }
                //Handles the input after the cd command
                else{
                    //If cd returns -1, the path doesn't exist
                    //Otherwise, change the directory to what follows the cd command

                    if(Input.substr(3,1) == " "){

                            dir(Input.substr(4, Input.length()-1), v);
                                std::copy(v.begin(), v.end(),
                                std::ostream_iterator<std::string>(std::cout, "\n"));
                    }
                }
            }

            if(Input.substr(0, 4) == "echo"){
                 //Handles the user just entering echo
                if(Input == "echo"){

                    cout<<"\nNothing to echo.";

                }
                //Handles the input after the echo command
                else{

                    //Call echo command
                    if(Input.substr(4,1) == " "){

                        echo(Input.substr(5, Input.length()-1));
                    }
                }
            }

            if(Input == "help"){
                help();
            }

            if(Input == "pause"){
                pauseShell();
            }

            if(Input == "environ"){
                environ();
            }

            if(Input == "quit"){
                cout<<"\n\n********************"
                    <<"\n* SHELL TERMINATED *"
                    <<"\n********************";
            }
        }
        else{
            cout<<"Attempting to load: "<< Input <<endl;
            ::isLaunch = 1;
            
           cout<< "\nTest: " << Input.substr(Input.length()-1,Input.length()-1)<<endl;
                
           if(Input.substr(Input.length()-1,Input.length()-1) == "&"){
               Input = Input.substr(0, Input.length()-1);
               strcpy(cstr, Input.c_str());
               strcpy(myCopy, Input.c_str());    
               launchBackground(myCopy);
           }
           else{
               strcpy(cstr, Input.c_str());          //Copy char array because initial will be tokenized
                strcpy(myCopy, Input.c_str());        
               if(LaunchType(myCopy) == 2){
                    launch(cstr);
               }
           }
           
                     
            
            
    
            
            
            
           
            
            
            //MAKE INT REPRESENTING ALL EXTERNAL COMMAND CASES, MAKE FUNCTION THAT DETERMINES EXTERNAL COMAND TYPE
            
            
        }
            
    }
    return 0;
}

