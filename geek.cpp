// C program to demonstrate use of fork() and pipe()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
const char PRead[] = "pipe pipeParentReadChildMessage";
const char PWrite[] = "pipe pipeParentWriteChildMessage";

int isNumber(char s[]) {
    for (int i = 0; s[i]!= '\0'; i++) {
        if (isdigit(s[i]) == 0)
           return 0;
    }
    return 1;
}

int main (int argc, char **argv) 
{
    if ((argc != 2) || !(isNumber(argv[1]))) {
        perror("Usage:forkpipe <number>");
        return -1;
    }
    char* pp;
    long arg = strtol(argv[1], &pp, 10);
    int number = arg;
    // We use two pipes
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child
 
    int fd1[2]; // Used to store two ends of first pipe
    int fd2[2]; // Used to store two ends of second pipe
 
    char fixed_str[] = "forgeeks.org";
    char input_str[100];
    pid_t p;
 
    if (pipe(fd1) == -1) {
        perror("Pipe Failed");
        return 1;
    }
    if (pipe(fd2) == -1) {
        perror("Pipe Failed");
        return 1;
    }
 
    printf("Enter your message:");

    scanf("%99[^\n]", input_str);
    p = fork();
 
    if (p < 0) {
        perror("fork Failed");
        return 1;
    }
 
    // Parent process
    else if (p > 0) {
        char concat_str[100];
 
        for (int a = 1; a <= number; a++) {
            close(fd1[0]); // Close reading end of first pipe
            // Write input string and close writing end of first
            // pipe.
            write(fd1[1], input_str, strlen(input_str) + 1);
            close(fd1[1]);
            printf("In Parent: Write to pipe getQuoteMessage sent\n");
            printf("Message\n:%s\n", input_str);
     
            // Wait for child to send a string
            wait(NULL);
     
            close(fd2[1]); // Close writing end of second pipe
     
            // Read string from child, print it and close
            // reading end.
            printf("In Parent: Read from %s read\n", PRead);
            read(fd2[0], concat_str, 100);
            printf("Message:\n%s\n", concat_str);
            close(fd2[0]);
        }
        close(fd1[0]); // Close reading end of first pipe
        write(fd1[1], "Exit", 5);
        close(fd1[1]);

    }
 
    // child process
    else {
        int flag = 1;
        close(fd1[1]); // Close writing end of first pipe
 
        // Read a string using first pipe
        char code[100];
        char msg[1000] = "Fetch quote";

        while (flag) {
            read(fd1[0], code, 100);
            printf("In Child: Read from %s read\n", PRead);
            printf("Message:\n%s\n", code); 
            // Close both reading ends
            close(fd1[0]);
            close(fd2[0]);
        
            if (strcmp(code, "Exit") == 0) {
                printf("Child done Exit\n");
                flag = 0;
            }
            else if (strcmp(code, "Get Quote") == 0) {
                // Write concatenated string and close writing end
                write(fd2[1], msg, strlen(msg) + 1);
                close(fd2[1]);
                printf("In Child: Write to %s sent\n", PWrite);
                printf("Message:\n%s\n", msg);
                flag = 0;
            }
            else {
                printf("Illegal message\n");
                flag = 0;
            } 
        } 
 


        exit(0);
    }
}
