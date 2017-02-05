#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXSize 1024 
#define HISSize 10

void execute(char** args);
char** ParseCommandLine(char* InputCommand);


int main(){
	// run the command loop
	int i = 0; // loop count for history array
	int k;
	int current = 0;// 'current' mark the index of history array
	int count = 0;
	char** args;//the array for all the tokens in the command line
	char directory[100];//store the cd directories into the string
	char InputCommand[MAXSize]; 
	char* hist_arr[HISSize]; // the array to store history

	for(i = 0; i < HISSize; i++)// initialize the history array with NULL
			hist_arr[i] = NULL;

	for(;;){//ifinite loop
		//title for each command line
		printf("CMPT300@my_shell:~$ ");

		fgets(InputCommand, sizeof(InputCommand), stdin); // store the command line from user to the array
		
		free(hist_arr[current]); // free the history array

		hist_arr[current] = strdup(InputCommand);
		current = (current +1) % HISSize;

		//If the internal command line is "exit", the shell will exit
		if(strcmp(InputCommand, "exit\n") == 0){
			printf("Wow! my_shell exit!\n\n");
			exit(1);
		}

		//for internal "cd" command
		args = ParseCommandLine(InputCommand); //split the command line into each token

		char* cd_command;
		char* command; // 'command' store the command without \n 

		cd_command = strtok(InputCommand, " ");
		command = InputCommand;

		if(strcmp(cd_command, "cd") == 0){
			args[1] = strtok(args[1], "\n");
			if(chdir(args[1]) == -1){
				printf("***ERROR: can not find the file or directory.\n");
				break;
			}
		}
		else if(strcmp(command, "pwd\n") == 0){// inernal pwd command
			getcwd(directory, sizeof(directory));
			if(directory != NULL)
				printf("Directory:  %s\n", directory);
			else
				printf("***ERROR: you can not find the directory!\n");
		}
		else if(strcmp(command, "history\n") == 0){ // internal history command
			k = current;
			int his_count = 1;
			do{
				if(hist_arr[k])
					printf("%4d %s", his_count++, hist_arr[k]);
				k = (k+1) % HISSize;
			}while (k != current);

		}
		if(strcmp(command, "pwd\n") != 0 && strcmp(cd_command, "cd") != 0 &&
			strcmp(command, "history\n") != 0 && strcmp(command, "cat\n") != 0 &&
			strcmp(command, "ls\n") != 0)	
			printf("***ERROR: can not find the file or directory.\n");

		//external command
		pid_t pid;
		int status;
		pid = fork();

		if(pid < 0){
			printf("***ERROR: forking child process failed.\n");
			exit(1);
		}
		else if(pid == 0){//child process
			if (strcmp(command, "cat\n") == 0){// cat command
				//char* a = strtok(command, "cat");
				char* argv[] = {"cat", "textfile.txt", 0};
				execvp(argv[0], argv);
			}
			else if(strcmp(command, "ls\n") == 0){// ls command
				char* argm[] = {"ls", 0};
				execvp(argm[0], argm);
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
 	token = strtok(InputCommand, " ");
 	int index = 0; //index in arr_tokens array

 	while(token != NULL){
 		arr_tokens[index++] = token;//store each token in array
 		token = strtok(NULL, " ");
 	}
 	arr_tokens[index] = NULL;
 	return arr_tokens;
}