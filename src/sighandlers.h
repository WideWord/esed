#ifndef __clang__

#pragma once
#include <signal.h>
#include <unistd.h>
#include <execinfo.h>

/* 
 * ---- SIGHUP - Закрытие терминала
 * 
 * ---- SIGINT - Сигнал прерывания (Ctrl-C) с терминала
 * ---- SIGTERM - Сигнал завершения (сигнал по умолчанию для утилиты kill)
 * ---- SIGTSTP - Сигнал остановки с терминала (Ctrl-Z)
 * ---- SIGQUIT - Сигнал «Quit» с терминала (Ctrl-\)
 * 
 * ---- SIGSEGV - Нарушение при обращении в память
 * 
 * SIGPIPE - Запись в разорванное соединение (пайп, сокет)
 * 
 * SIGXCPU - Процесс превысил лимит процессорного времени
 * SIGXFSZ - Процесс превысил допустимый размер файла
 *  
 */

/*
 * Description: this function sets up signal handlers
 * Receives: nothing
 * Returnes: 1 if success, 0 if failure
 */
int setHandlers(char * tmpFileName);


/*
 * Description: handler for signals SIGINT, SIGTERM, SIGTSTP, SIGQUIT
 * Receives: sig - signal code
 * Returnes: nothing 
 */
void exitHandler(int sig);


/*
 * Description: handler for signal SIGPIPE
 * Receives: sig - signal code
 * Returnes: nothing 
 */
void sigpipeHandler(int sig);


/*
 * Description: handler for signal SIGSEGV
 * Receives: sig - signal code
 * Returnes: nothing 
 */
void segfaultHandler(int sig);

#endif