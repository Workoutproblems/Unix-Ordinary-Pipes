//
//  main.cpp
//  Unix Ordinary Pipes
//
//  Created by Johnny Soto on 11/25/17.
//  Copyright © 2017 Johnny Soto. All rights reserved.
//

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(int argc, const char * argv[]) {
    
    char write_msg[BUFFER_SIZE] = "Hello, using pipes!";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;
    
    if (pipe(fd) == -1){
        fprintf(stderr, "Pipe failed");
        return 1;
    }
    pid = fork();
    printf("After fork.\n");
    if (pid < 0){
        fprintf(stderr, "Fork failed");
        return 1;
    }
    if (pid > 0) {
        close(fd[READ_END]);
        printf("In the parent process.\n");
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
        
        close(fd[WRITE_END]);
    }
    else {
        close(fd[WRITE_END]);
        printf("In the child process.\n");
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        
        printf("read: %s\n", read_msg);
        
        close(fd[READ_END]);
    }
    printf("Done\n");
    return 0;
}
