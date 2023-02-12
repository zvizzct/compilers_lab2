# Scanner App
This application is a scanner for a simple programming language which can process a file and produce a list of tokens.

## Description
The scanner is a tool that allows you to analyze your code and produce a list of tokens that represent the structure of your program. This application can recognize the following tokens:

- Types
- Operators
- Especial characters
- Numbers
- Keywords
- Non-essential characters
- Identifiers/variables
- Literal
- Non-recognized

The output of the scanner is saved in a file with the same name as the input file, but with the extension ".scn".

## Installation
To install the application, navigate to the directory where the files are located and run the command `make`. This will compile the source code and create the executable.

To clean the executable generated during the compilation and compile it again, run the command `make all`.

## Usage
To use the application, navigate to the directory where the files are located and run the command `./scanner [filename]`. Replace "[filename]" with the name of the file you want to process.

After running the command, the application will generate a file with the same name as the input file, but with the extension ".scn", in the results directory. This file will contain the list of tokens.

For example, to process a file called "file.c" allocated in test directory, you would run the command `./scanner test/file.c`.`