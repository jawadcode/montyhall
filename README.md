# Monty Hall simulation in C

"Plays" 100 Million Monty Hall problems/games and outputs the results, e.g.

```
❯ ./montyhall
Monty Hall problem simulator
100000000 games:

Stay:
33.341622% wins (33341622/100000000)

Swap:
66.658378% wins (66658378/100000000)
```

## How to Run:

- `cd` into cloned repository
- `gcc main.c -O3 -o montyhall` or `clang main.c -O3 -o montyhall` (this step can be skipped if you are running any 64bit Linux Distro, in which case you can use the included `montyhall` executable file)
- `./montyhall` runs the progam

## Performance:

~5.3s (averaged total time of 20 runs):

#### Compiled with GCC 10.2.0 (`-O3` optimisation flag) on Arch Linux (64bit), Intel(R) Core(TM) i3-2350M CPU @ 2.30GHz
