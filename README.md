# minishell

This project is a custom implementation of a shell, similar to `bash` or `zsh`. It is a 42 school project.

## Features

*   **Command Execution**: Executes simple commands with arguments.
*   **Built-in Commands**:
    *   `echo` with `-n` option
    *   `cd` with relative or absolute path
    *   `pwd`
    *   `export`
    *   `unset`
    *   `env`
    *   `exit`
*   **Redirections**:
    *   `<` (input redirection)
    *   `>` (output redirection)
    *   `<<` (here document)
    *   `>>` (append output redirection)
*   **Pipes**: `|` operator to chain commands.
*   **Environment Variables**: Handles `$` followed by characters for environment variable expansion.
*   **Signal Handling**:
    *   `Ctrl-C`: Interrupts the current process and displays a new prompt.
    *   `Ctrl-D`: Exits the shell.
    *   `Ctrl-\`: Does nothing.

## How to Use

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your_username/your_repository.git
    cd your_repository
    ```

2.  **Build the project:**
    ```bash
    make
    ```

3.  **Run the shell:**
    ```bash
    ./minishell
    ```

## Project Structure

The source code is organized into the following directories:

*   `SRCS/`: Main source files.
    *   `built_in/`: Implementation of the built-in commands.
    *   `exec/`: Command execution logic.
    *   `expander/`: Variable expansion logic.
    *   `lexer/`: Lexical analysis.
    *   `parser/`: Parsing logic.
    *   `utils/`: Utility functions.
*   `includes/`: Header files.
*   `OBJS/`: Object files.

## Example Usage

```bash
$ echo "Hello, world!"
Hello, world!
$ ls -l | grep ".c"
-rw-r--r--  1 user  group  1234 Jul  4 10:00 main.c
...
$ export MESSAGE="Hello from minishell"
$ echo $MESSAGE
Hello from minishell
$ unset MESSAGE
$ echo $MESSAGE

$ cat < Makefile > Makefile_copy
$ cat << EOF > temp.txt
> line 1
> line 2
> EOF
$ cat temp.txt
line 1
line 2
```
