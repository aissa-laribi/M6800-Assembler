# M6800 Assembler

## Description

This project is currently under development. It aims to convert the Motorola M6800

## Current Status

- 🚧 **In Development**: Working on [feature/set of features].
- 🛠 Major updates and features will be added periodically as time allows.

## To-Do List

Improve IDX operand type parsing
Continue operand value parsing for LDX, REL addressing modes
ERROR HANDLING(Wrong syntax, operand exceedings bytes capacity of addressing modes)                            


## Getting Started

While the project is still in development, here's how you can get started with it:

1. Clone the repository:
    ```sh
    git clone https://github.com/aissa-laribi/M6800-Assembler.git
    ```
2. Compile:
    ```sh
    gcc -o main  main.c instructions.c parser.c
    ```
3. Executing the program:
    ```sh
    ./main
    ```
    Note: a sample of instructions is provided "instructions.asm"

## Contributing

If you'd like to contribute, feel free to fork the repository and submit a pull request. Please understand that the project is still in an early stage and I may not be able to review PRs immediately.

## Timeline

Due to time constraints, progress may be slow, but the project will be actively worked on whenever possible.

## License

This project is licensed under the [MIT License](LICENSE).
