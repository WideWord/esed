#include "sighandlers.h"

#include <signal.h>
#include <unistd.h>
#include <execinfo.h>

#include <stdlib.h>
#include <stdio.h>


#define SET_HANDLER(Signal, Handler) \
    if(signal(Signal, Handler) == SIG_ERR) \
        return SIG_ERR;


/*
 * Description: this function sets up signal handlers
 * Receives: nothing
 * Returnes: 0 if success, SIG_ERR if failure
 */
sig_t setHandlers(){
    
    // Set handler for SIGINT, SIGTERM, SIGTSTP, SIGQUIT, SIGHUP
    SET_HANDLER(SIGINT,  exitHandler);
    SET_HANDLER(SIGTERM, exitHandler);
    SET_HANDLER(SIGTSTP, exitHandler);
    SET_HANDLER(SIGQUIT, exitHandler);  
    SET_HANDLER(SIGHUP,  exitHandler);
    
    // Set handler for SIGSEGV
    SET_HANDLER(SIGSEGV, segfaultHandler);
    
    // Set handler for SIGPIPE
    SET_HANDLER(SIGPIPE, sigpipeHandler);
    
    // Return success code
    return 0;
}

/*
 * Description: handler for signals SIGINT, SIGTERM, SIGTSTP, SIGQUIT
 * Receives: sig - signal code
 * Returnes: nothing 
 */
void exitHandler(int sig){    
    fprintf(stderr, "Save files, exit... \n");     
    exit(EXIT_SUCCESS);
}

/*
 * Description: handler for signal SIGSEGV
 * Receives: sig - signal code
 * Returnes: nothing 
 */
void segfaultHandler(int sig) {
    fprintf(stderr, "SIGSEGV catched.\n");
    
    /* Printing stack trace */
    void * array[10];
    size_t size;

    size = backtrace(array, 10);

    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

/*
 * Description: handler for signal SIGPIPE
 * Receives: sig - signal code
 * Returnes: nothing 
 */
void sigpipeHandler(int sig){
//  ?????????
    fprintf(stderr, "SIGPIPE catched.\n");
    exit(EXIT_FAILURE);
}