#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100



int MyShell (char **arr, int et)
{
        pid_t pid;

        pid=fork();
        if(pid<0){ /* if the forking dose not work. */
            printf("Error. the fork does not work. \n");
            exit (1);
        }
        else if (pid==0){ /*if its the son process*/
            execvp(*arr,arr); /*then the process will do the command that is given*/
            exit(0);
        }

        else /*if its the father process*/
            if (et==0) /*if there are not & in the end of the line so the process will be execute on the front- wich mean the father will wait to his son. */
                while(wait(NULL)!=-1);

        return 0;

}




int  main(void)
{
    close(2);
    dup(1);

    char *take[BUFFER_SIZE];
    int et, i;
    char command[BUFFER_SIZE];

    while (1)
    {
        fprintf(stdout, "my-shell> ");
        memset(command, 0, BUFFER_SIZE);
        fgets(command, BUFFER_SIZE, stdin);
        if(strncmp(command, "exit", 4) == 0) /*if the user write exit- we will go out.*/
            break;

        take[0] =strtok(command," \n\a\t\r"); /* we will separate the command that we get to one word at the tine*/
        for(i=0 ;take[i]!=NULL;i++){
            take[i+1]=strtok(NULL," \n\a\t\r");
        }
        if (take[i-1][0]=='&') /*if the last word was the char & - we will do the command in the back.*/
        {
            et=1;
            take[i-1]=NULL;
        }
        else
            et=0; /*if not, we will do it in the front. */
        MyShell(take, et);
    }
    return 0;
}
