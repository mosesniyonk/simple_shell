// shell.h
#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environment */
extern char **environ;
/* Global program name */
extern char *programName;
/* Global history counter */
extern int historyCounter;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_str
{
    char *directory;
    struct list_s *next;
} List;

/**
 * struct builtin_str - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_str
{
    char *name;
    int (*function)(char **arguments, char **front);
} Builtin;

/**
 * struct alias_str - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_str
{
    char *name;
    char *value;
    struct alias_str *next;
} Alias;

/* Global aliases linked list */
extern Alias *aliases;

/* Main Helpers */
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);
void *reallocate(void *pointer, unsigned int oldSize, unsigned int newSize);
char **tokenizeString(char *line, char *delimiter);
char *getLocation(char *command);
List *getPathDirectory(char *path);
int executeCommand(char **arguments, char **front);
void freeList(List *head);
char *integerToString(int number);

/* Input Helpers */
void handleLine(char **line, ssize_t read);
void replaceVariables(char **arguments, int *executionResult);
char *getArguments(char *line, int *executionResult);
int callArguments(char **arguments, char **front, int *executionResult);
int runArguments(char **arguments, char **front, int *executionResult);
int handleArguments(int *executionResult);
int checkArguments(char **arguments);
void freeArguments(char **arguments, char **front);
char **replaceAliases(char **arguments);

/* String functions */
int stringLength(const char *string);
char *concatenateStrings(char *destination, const char *source);
char *concatenateNStrings(char *destination, const char *source, size_t n);
char *copyString(char *destination, const char *source);
char *findCharacter(char *string, char character);
int stringSpan(char *string, char *accept);
int compareStrings(char *string1, char *string2);
int compareNStrings(const char *string1, const char *string2, size_t n);

/* Builtins */
int (*getBuiltin(char *command))(char **arguments, char **front);
int exitShellby(char **arguments, char **front);
int envShellby(char **arguments, char __attribute__((__unused__)) **front);
int setenvShellby(char **arguments, char __attribute__((__unused__)) **front);
int unsetenvShellby(char **arguments, char __attribute__((__unused__)) **front);
int cdShellby(char **arguments, char __attribute__((__unused__)) **front);
int aliasShellby(char **arguments, char __attribute__((__unused__)) **front);
int helpShellby(char **arguments, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **copyEnvironment(void);
void freeEnvironment(void);
char **getEnvironmentVariable(const char *variable);

/* Error Handling */
int createError(char **arguments, int errorNumber);
char *errorEnvironment(char **arguments);
char *error1(char **arguments);
char *error2Exit(char **arguments);
char *error2Cd(char **arguments);
char *error2Syntax(char **arguments);
char *error126(char **arguments);
char *error127(char **arguments);

/* Linkedlist Helpers */
Alias *addAliasEnd(Alias **head, char *name, char *value);
void freeAliasList(Alias *head);
List *addNodeEnd(List **head, char *directory);
void freeList(List *head);

void helpAll(void);
void helpAlias(void);
void helpCd(void);
void helpExit(void);
void helpHelp(void);
void helpEnv(void);
void helpSetenv(void);
void helpUnsetenv(void);
void helpHistory(void);

int processFileCommands(char *filePath, int *executionResult);
#endif /* _SHELL_H_ */
