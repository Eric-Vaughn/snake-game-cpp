# Snake Game C++

A C++ version of the classic game Snake, using raylib for visualization.

## Overview

This project is the first stepping stone on my journey with raylib!

Overall, this project was good. It wasn't very hard and served as good exposer to raylib's functions / basic structure. I plan on making another classic game, or something similar, next — this time using a tutorial as a "help me, I'm stuck" resource instead of following along.

## The tutorial this project follows

- The video: [Link](https://www.youtube.com/watch?v=LGqsnM_WEK4&t=1235s)
- The channel: [Link](https://www.youtube.com/@programmingwithnick)

## What I learned

- Basics of raylib
    - Useful functions
    - To Init both the game window and the audio manager
    - Utilizing grid-based movement without the need to keep track of a grid (just move!)
    - Deque in raylib
- Some CMake
- Formatter for C/C++ (Clang-Format)

## Gripes/Improvements

The tutorial was good, but I have some complaints.

I followed it to the T, except I added in a High Score for fun, and the way the code is orginized is... strange at times.

Not to mention A) having everything in one file, B) not using const or private ANYWHERE, or C) having so many hard coded values / restating portions of code. The most egregious example of C) is with `cellSize * cellCount`. Like, bro... make it a variable already — make it a global constant!

```
const int CELL_SIZE = 30;
const int CELL_COUNT = 25;
const int BORDER_OFFSET = 75;
const int GRID_SIZE = CELL_COUNT * CELL_SIZE;
const int GRID_SIZE_AND_OFFSET = GRID_SIZE + BORDER_OFFSET;

```

Now, if we need any of these values by themselves, we can have them. But usually, we would just use `GRID_SIZE` and `GRID_SIZE_AND_OFFSET`.

Also, the main function is CLOGGED with that user input if-else chain. I'd put that in the `Game` class and just call it something like `game.lookForInputs()` / `game.getInputs()`.
