# Minishell

42 Project `minishell` is a simple shell implementation written in C. It supports basic shell functionalities such as command execution, piping, redirection, and built-in commands.

https://github.com/user-attachments/assets/ce4236a0-1fce-4f14-b527-19425e5f017b


## Table of Contents

- [Features](#features)
- [Writeup](#writeup)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)

## Features
- Command execution
- Input and output redirection
- Piping
- Built-in commands (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
- Signal handling
- Environment variable management

To understand the features of minishell, the [test.sh](./test.sh) file would be a good starting point.

## Writeup
This project follows an incremental development approach, where the program is built step-by-step, ensuring it functions as a shell at each stage. The process involves reading documentation, executing sample code, writing tests, and revising code iteratively. The incremental method simplifies coding, understanding, and testing, ultimately speeding up development. For detailed steps, you can find my write up [here](https://usatie.notion.site/minishell-29921d3ea13447ad897349acd5733d5e?pvs=4).

## Installation

To install and build Minishell, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/minishell.git
    cd minishell
    ```

2. Install dependencies:
    ```sh
    brew install readline
    ```

3. Build the project:
    ```sh
    make
    ```

## Usage

To start the shell, run the following command:
```sh
./minishell
```

You will see a prompt like this:
```sh
minishell$
```

You can now enter commands just like you would in a regular shell.

## File Structure

The project is organized as follows:

- `src/`: Contains the source code for the shell.
  - `main.c`: Entry point of the shell.
  - `tokenize/`: Tokenization logic.
  - `parse/`: Parsing logic.
  - `expand/`: Expansion logic.
  - `redirect/`: Redirection logic.
  - `exec/`: Execution logic.
  - `builtin/`: Built-in command implementations.
  - `signal/`: Signal handling logic.
  - `lib/`: Utility functions.
  - `environ/`: Environment variable management.
  - `pipe/`: Piping logic.
  - `error/`: Error handling logic.
- `include/`: Contains header files.
  - `minishell.h`: Main header file for the shell.
- `libft/`: Contains the my own libc like functions.
- `Makefile`: Build script for the project.
- `test.sh`: Script for running tests.

## Acknowledgments
This project was developed with the support and guidance of various resources and tools. Special thanks to:

- The 42 Network for providing the project framework and learning environment.
- 42 peers for their help and feedback.
- ChatGPT-4o for assisting in generating this README.
- The authors of "The Linux Programming Interface" and "Advanced Programming in the UNIX Environment" for their invaluable reference materials.
