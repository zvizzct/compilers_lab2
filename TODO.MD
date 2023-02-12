# TO DO:
## DFA:
- [ ] Alphabet (all characters)
- [X] Types: int, double, char, void
- [ ] Operators: = > + *
- [ ] Especial characters: ( ) { } [ ] ; ,
- [X] Numbers: 0-9
- [X] Keywords: if, else, while, main, return.
- [ ] Non-essential characters: space, eol, tabs (and similar delimiter characters)
- [ ] Identifiers/variables: a-z, A-Z, 0-9, _
- [ ] Literal
- [ ] Non-recognized

# Handle input file
- [ ] Open file
- [ ] Read file
- [ ] Close file

# Handle output file
- [ ] Open file with the same name as input file but with .cscn extension
- [ ] Write to file
- [ ] Close file

# Function to handle each token
- [ ] Loop through each character in the input file
- [ ] Check if character is in DFA
- [ ] Structure to hold a token (lexeme, category, line number)

# Function to write debuging output
- [ ] Write the line number of the input file before each token line in the debug format
- [ ] Write the tokens in the output file separated by a space character
- [ ] Write additional debugging messages as per the requirement in the debug format
- [ ] Write the output in a format of your choice, as long as it works for debugging purposes

# Function to write release output

- [ ] Ensure that the function does not add empty lines to the output file
- [ ] Ensure that each line of code in the input file corresponds to one line of tokens in the output file
- [ ] Ensure that each token in the output file is separated by a space character