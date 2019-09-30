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

using namespace std;

std::string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}
 
//Function to clear the screen of shell
void clr(){
    cout << string( 100, '\n' );
}

//Function to change the current working directory and returns 0 if successful, -1 if not
int cd(string DirName){
    return chdir(DirName.c_str());
}



typedef std::vector<std::string> stringvec;

//Function to print the contents of the current directory,  or user specified directory
void dir(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    std::sort(v.begin(), v.end());
    closedir(dirp);
}



 


/*
 * 
 */
int main(int argc, char** argv) {

    string Input;
    
    stringvec v;
    //dir("/Users/stephenlucas", v);
    //std::copy(v.begin(), v.end(),
       //  std::ostream_iterator<std::string>(std::cout, "\n"));
    


    //std::cout << GetCurrentWorkingDir() << std::endl;
    
    while(Input!= "quit"){
        
        if(Input =="clr"){
            //Sets cursor to top of console
            printf("\033[1;1H");
            
            cout<< GetCurrentWorkingDir() << ": ";
        }
        else{
            cout<< GetCurrentWorkingDir() << ": ";
        }
        
        getline(cin, Input);

       
        
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
                cout<<Input.substr(2,1);
                if(cd(Input.substr(3,Input.length()-1)) != 0 && Input.substr(2,1) == " "){
                    cout<<"\n\n******************"
                        <<"\n* PATH NOT FOUND *"
                        <<"\n******************\n\n";
                }
            }
        }
        
         //If user enters cd, change directory
        if(Input.substr(0, 3) == "dir"){
            
            cout<<Input.substr(3,1);
                
            
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
                    cout<<"Hello";
                        dir(Input.substr(4, Input.length()-1), v);
                            std::copy(v.begin(), v.end(),
                            std::ostream_iterator<std::string>(std::cout, "\n"));
                }
            }
        }
        
        if(Input == "quit"){
            cout<<"\n\n********************"
                <<"\n* SHELL TERMINATED *"
                <<"\n********************";
        }
    }
    return 0;
}

