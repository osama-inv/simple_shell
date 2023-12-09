The project, titled "Simple Shell Team Project," was successfully developed using the C programming language and adhered to the Betty coding style standards. This project was meticulously compiled on Ubuntu 20.04 LTS using the gcc compiler with specific flags (-Wall -Werror -Wextra -pedantic -std=gnu89) to ensure code quality. Each file in the project concludes with a newline character.

A crucial aspect of the project is the inclusion of a README.md file located in the project's root directory. This file is essential for providing an overview of the project. The code's adherence to the Betty style was verified using the betty-style.pl and betty-doc.pl scripts.

The shell developed in this project is designed to be leak-free in terms of memory usage. The project's structure is organized such that each file contains no more than five functions, and all header files are appropriately include guarded. The README file elaborates on the project's specifics.

The shell, named 'hsh,' functions as a basic UNIX command language interpreter. It operates by reading commands from a file or standard input and executing them. The shell's operational flow includes:

Displaying a prompt and waiting for user input.
Creating a child process to assess the command, checking for built-ins, aliases in the PATH, and locally executable programs.
Replacing the child process with the command, which can take arguments.
Once the command execution is complete, control returns to the parent process, which then displays the prompt again.
The shell is ready to process a new command.
The shell can be exited by pressing Ctrl-D or entering "exit," with or without a status code.
The shell also supports non-interactive mode.
The project's compilation process is detailed, specifying the use of the gcc compiler with the aforementioned flags and the command to create the executable named 'hsh'.
