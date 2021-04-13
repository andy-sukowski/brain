# brain - brainfuck interpreter

This is a simple interpreter for the [brainfuck][1] programming language,
written in C.

## Behavior

- All characters except the eight commands `><+-.,[]` are ignored and
  treated as comments.

- The array has 30,000 cells and each cell in the array contains a byte
  (most commonly 8 bits).

- Moving the pointer outside the bounds of the array will result in
  undefined behavior.

## Installation

Edit `config.mk` to match your local setup (brain is installed into the
`/usr/local` namespace by default).

Afterwards enter the following command to build and install brain (if
necessary as root):

    make clean install

## Running brain 

After successfully installing brain, you can run it:

    brain <file>

This is an example of running brain:

    brain example.bf

[1]: https://en.wikipedia.org/wiki/Brainfuck
