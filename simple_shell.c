/* Rachel Cohen
 * CMSC 421 Homework 2
 * Simple Shell Program
*/


#include <stdio.h>

#include <string.h>

#include <stdlib.h>

//for wait()
#include <sys/wait.h>

//for execv
#include <unistd.h>


//initialize initial max input string size
const int INITMAXSIZE = 10000;
//declare cmd pointer
char* cmd;


//run the user's command

void execute() {


  int numArgs = 0;

  //parse the user's input string

  char** params = NULL;

  //delimiters to account for as arguments in order to parse command line args

  char* delim = " \t\n";                

  //extract the tokens from the command string

  char* token = strtok_r(cmd, delim, &cmd);


  //while there is a valid token

  while(token){

    //increase argument count 

    numArgs = numArgs + 1;


    //numArgs (argument count) is the start size for the mem allocation

    //attempt to resize memory block allocated in main

    params = realloc(params, sizeof(char* ) * numArgs);


    //if realloc was not successful

    if(params == NULL)    

      {
	//exit with error

	exit(1);

      }

    params[numArgs - 1] = token;

    
    //get remaining tokens with null pointer as first parameter

    token = strtok_r(NULL, delim, &cmd);

  }

  //realloc for remaining part

  params = realloc(params, sizeof(char* ) * (numArgs + 1));

  params[numArgs] = 0;     

  //execute, current process image replaced by new process image

  execv(params[0], params);



  //throw error, execv return not expected

  printf("execv error, path does not exist\n");



  //deallocate the previously allocated space

  free(params);

}


//prompt the user for a command

void cmdLinePrompt(){

  //prompt user with '$' shell prompt

  printf("$ ");

  //read in user input, store in string pointed to by arg

  fgets(cmd, INITMAXSIZE, stdin);

}

/*
int exitShell(char* args){
        //don't start arg count at 0
        int i = 1;
        //while there are available arguments, total them up
        while(args[i]!= NULL){
                i++;
        }
        i--;
        if (i > 1){
                printf("Too many arguments.");
                return 1;
        }
        if (args[1] == NULL || (args[1]) == 0){
                exit(0);
        }

        else if (args[1]) == 1){
                exit(1);       
        }
        else{
   
printf("Error exiting");
                return 1;
        }

}
*/



/*
int cdFunction(char* args[]){
    if(args[1] == NULL){
        chdir(getenv("HOME"));
        return 1;
    }
    else{
        if(chdir(args[1] == -1){
            printf("Error.");
        }
        return -1;
        }
return 0;

}
*/



int main() {



  //allocate argument with the initial max size 

  cmd = (char* )malloc(INITMAXSIZE);



  //prompt user

  cmdLinePrompt();





  //while true

  while(1){



    //fork process

    pid_t pid;

    pid = fork();



    //if fork returns a negative value, child process was unsuccessful

    if (pid < 0){

      printf("fork error, process failed");

      //exit with error

      exit(1);

    }

    //if fork returns zero, the child process was created successfully

    else if(pid == 0){

      //all good, execute command

      execute();

      //exit successfully

      exit(0);

    }

    //otherwise it's the parent, wait 

    else{

      wait(NULL);

      //reprompt

      cmdLinePrompt();

    }

  }

  return 0;

}
