#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXSize 1024 

void execute(char** args);
char** ParseCommandLine(char* InputCommand);


int main(){
	// run the command loop
	int i = 0; //the count in the for loop for "pwd" command
	int j = 0;
	int count = 0;
	char** commands = malloc(MAXSize * sizeof(char*));; // the array for the 
	char** args;//the array for all the tokens in the command line
	char directory[100];//store the cd directories into the string
	char InputCommand[MAXSize]; 

	for(;;){//ifinite loop
		//title for each command line
		printf("CMPT300@my_shell:~$ ");

		fgets(InputCommand, sizeof(InputCommand), stdin); // store the command line from user to the array
		
		//If the internal command line is "exit", the shell will exit
		if(strcmp(InputCommand, "exit\n") == 0){
			printf("Wow! my_shell exit!\n\n");
			exit(1);
		}
		

		//for internal "cd" command

		args = ParseCommandLine(InputCommand); //split the command line into each token
		pid_t pid;
		int status;
		pid = fork();
		if(pid < 0){
			printf("ERROR: forking child process failed.\n");
			exit(1);
		}
		else if(pid == 0){//child process
			char* cd_command;
			char* pwd_command;
			char* his_command;

			//cd_command = malloc(strlen(InputCommand)); 
			strcpy(cd_command, InputCommand);
			cd_command = strtok(InputCommand, " ");
			pwd_command = InputCommand;
			his_command = InputCommand;

			//if the command is "cd", it will enter the directory
			if(strcmp(cd_command, "cd") == 0){
				args[1] = strtok(args[1], "\n");
				//directory = realloc(args[1], MAXSize * sizeof(char*));
				if(chdir(args[1]) == -1){
					printf("Error: can not find the file or directory.\n");
					break;
				}
			}
			else if(strcmp(pwd_command, "pwd\n") == 0){
				getcwd(directory, sizeof(directory));
				if(directory != NULL)
					printf("Directory:  %s\n", directory);
				else
					printf("Error: you can not find the directory!\n");
			}
			else if(strcmp(his_command, "history\n") == 0){
				



				

			}
		}
		else{//parent process
			while(wait(&status) != pid);
		}
	}
	return 0;
}

char** ParseCommandLine(char* InputCommand){
 	char** arr_tokens = malloc(MAXSize * sizeof(char*)); // allocate the space for each tokens in the array
 	char* token; //each token in each command line
 	char* space = " \t"; //space is the separater in command line
 	token = strtok(InputCommand, space);
 	int index = 0; //index in arr_tokens array

 	while(token != NULL){
 		arr_tokens[index++] = token;//store each token in array
 		token = strtok(NULL, " \t");
 	}
 	arr_tokens[index] = NULL;
 	return arr_tokens;
}