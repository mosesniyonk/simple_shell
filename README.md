
# Simple Shell Team Project

## Project Details

- **Language Used**: C
- **Shell**: Yes
- **Linter**: Betty

## General Project Requirements

- All files are compiled on Ubuntu 20.04 LTS using `gcc`, with the options `-Wall -Werror -Wextra -pedantic -std=gnu89`.
- All files end with a new line.
- A `README.md` file at the root of the project folder is mandatory.
- The Betty style is used and checked using `betty-style.pl` and `betty-doc.pl`.
- The shell should not have any memory leaks.
- No more than 5 functions per file.
- All header files should be include guarded.

## Project Description

**hsh** is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

## How hsh Works

1. Prints a prompt and waits for a command from the user.
2. Creates a child process in which the command is checked.
3. Checks for built-ins, aliases in the PATH, and local executable programs.
4. The child process is replaced by the command, which accepts arguments.
5. When the command is done, the program returns to the parent process and prints the prompt.
6. The program is ready to receive a new command.
7. To exit: press Ctrl-D or enter "exit" (with or without a status).
8. Works also in non-interactive mode.

## Compilation

Compile the project using the following command:


gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage

After compiling, run the shell using the `./hsh` command.

## Author

This project was created by the **Moise** team.

## License

This project is open-source and available under the **License Name** license. See the LICENSE file for more details.

## Contact Information

For questions or feedback, please contact **moses.niyonk@gmail.com**.

You can copy and paste this Markdown code into your `README.md` file.
