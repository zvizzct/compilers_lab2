# User Manual for Scanner Implementation
This manual provides information about the scanner implementation and its features. The scanner is a component of a compiler and is responsible for breaking the input program into smaller components known as tokens. These tokens are then passed to the parser for further processing.

## Table of Contents
1. Introduction
2. System Requirements
3. Input Format
4. Output Format
5. Tokens
6. Error Handling
7. Number of Operations
8. Interaction with Next Phase (Parser)
9. How to Run the Scanner
10. Configuration

## Introduction

The scanner implementation is a program that reads an input program and breaks it into tokens. The tokens are then written to an output file in a specified format.

## System Requirements
The scanner implementation is written in C and requires a system with a C compiler installed. The program has been tested on Linux operating system and should run on other operating systems as well.

## Input Format
The input program is a text file that contains the program code to be scanned. The file can contain multiple lines and should end with a newline character.

## Output Format
The output of the scanner is a text file that contains the list of tokens produced from the input program. The tokens are written in the following format:

```
Token_Type Token_Value
```
Where `Token_Type` is the type of the token, and `Token_Value` is the value of the token.

## Tokens
The scanner implementation recognizes the following tokens:

- Types
- Operators
- Especial characters
- Numbers
- Keywords
- Non-essential characters
- Identifiers/variables
- Literal
- Non-recognized

## Error Handling
The scanner implementation has error handling capabilities. In case of any error in the input program, an error message is printed to the standard error indicating the line number and the type of error. The scanner then continues processing the next line.

## Number of Operations
The number of comparisons needed to identify each token is a measure of the efficiency of the implementation. The program has the ability to count and print information on the number of operations performed during the scanning process. This feature can be enabled or disabled through a configuration constant (`COUNTOP`).

## Interaction with Next Phase (Parser)
The output of the scanner is the input of the parser. The program is designed in such a way that it can be used with or without the parser. The program can either write the tokens to an output file or directly call the parser without having to load the tokens file.

## How to Run the Scanner
To run the scanner, compile the program using the following command:

```bash
make all
``` 
Then, run the program with the input file as an argument:

```bash
./scanner input_file
```
The program will then produce an output file containing the list of tokens.

## Configuration
The program can be configured through the following constants:

- `DEBUG`: Enables or disables debug messages
- `COUNTOP`: Enables or disables counting and printing of the number of operations

