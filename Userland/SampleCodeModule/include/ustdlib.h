#ifndef USTDLIB_H
#define USTDLIB_H

#include <stdint.h>
#include <stdarg.h>

enum {
  STDIN = 0, STDOUT, 
};

#define IS_DIGIT(x) (((x) >= '0' && (x) <= '9'))
#define IS_HEXDIGIT(x) (IS_DIGIT(x) || (x >= 'A' && x <= 'F') || (x >= 'a' && x <= 'f'))
#define EOF -1

#define MAX_SPACES 6

void clearScreen();
void _fprint(const char *str);
char getChar();
void _putc(char c);
void _fprintf(char *,...);              
int toLower(int chr);
int strToHex(const char *str);
char* _itoa(uint64_t, int);      
long _atoi(const char* s);
void _print(const char *str);
int _strcasecmp(const char *str1, const char* str2);
int _strlen(const char* str);
int isNumber(const char *str);
void _hlt();
char * strcpy(char *strDest, const char *strSrc);

#endif