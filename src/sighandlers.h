#pragma once
#include <signal.h>
#include <unistd.h>
#include <execinfo.h>

/* 
 * SIGHUP - Закрытие терминала
 * 
 * ---- SIGINT - Сигнал прерывания (Ctrl-C) с терминала ^^^^^
 * ---- SIGTERM - Сигнал завершения (сигнал по умолчанию для утилиты kill) ^^^^^
 * ---- SIGTSTP - Сигнал остановки с терминала (Ctrl-Z)
 * ---- SIGQUIT - Сигнал «Quit» с терминала (Ctrl-\)
 * 
 * SIGSEGV - Нарушение при обращении в память
 * 
 * SIGPIPE - Запись в разорванное соединение (пайп, сокет)
 *  
 */

__sighandler_t setHandlers();

void exitHandler(int sig);