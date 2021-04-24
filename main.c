#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_GAMES 100000000

// Function pointer that represents the "stay()" and "swap()" strategies
typedef int (*Strategy)(void);

// Positions of the car for each game
static uint8_t cars[NUM_GAMES];
// The (first) guess for each game
static uint8_t guesses[NUM_GAMES];

// Returns a random number in-between 0 and 2 (inclusive)
uint8_t rand_to_2() {
  uint8_t num;
  do {
    num = rand() & 3;
  } while (num > 2);
  return num;
}

// Populates "arr" with random values
void init(uint8_t *arr) {
  for (int i = 0; i < NUM_GAMES; i++) {
    arr[i] = rand_to_2();
  }
}

// Plays game (using "cars" and "guesses") using the stay strategy and returns
// the number of wins
int stay() {
  int wins = 0;
  // Loop through "cars" (and "guesses")
  for (int i = 0; i < NUM_GAMES; i++) {
    // Adds 0 if the guess is wrong, adds 1 if the guess is correct
    wins += cars[i] == guesses[i];
  }
  return wins;
}

// Plays game (using "cars" and "guesses") using the swap strategy and returns
// the number of wins
int swap() {
  int wins = 0;
  for (int i = 0; i < NUM_GAMES; i++) {
    // The first guess
    uint8_t guess = guesses[i];
    // The position of the car
    uint8_t car = cars[i];
    // The position of a goat that isn't the first guess (or the car of course)
    uint8_t notcar = (guess == 1 || guess == 2) && (car == 1 || car == 2)   ? 0
                     : (guess == 0 || guess == 2) && (car == 0 || car == 2) ? 1
                                                                            : 2;
    // New guess that is neither the goat that was revealed previously nor the
    // first guess
    uint8_t newguess =
        (guess == 1 || guess == 2) && (notcar == 1 || notcar == 2)   ? 0
        : (guess == 0 || guess == 2) && (notcar == 0 || notcar == 2) ? 1
                                                                     : 2;
    // Adds 0 if the guess is wrong, adds 1 if the guess is correct
    wins += newguess == cars[i];
  }
  return wins;
}

void play(Strategy strategy, const char *title) {
  // Prints the title of the strategy (i.e. "Stay:" or "Swap:")
  fputs(title, stdout);

  // Call strategy (i.e. "stay()" or "swap()")
  int wins = strategy();
  double percentage = (wins / (double)NUM_GAMES) * 100;
  printf("%f%% wins (%d/%d)\n\n", percentage, wins, NUM_GAMES);
}

int main() {
  printf("Monty Hall problem simulator:\n%d games:\n\n", NUM_GAMES);

  // Seed Random Number Generator
  srand(time(NULL));
  // Fill "cars" and "guesses" arrays with random values using "rand_to_2()"
  init(cars);
  init(guesses);

  // Play the game using the "stay" and "swap" strategies
  play(stay, "Stay:\n");
  play(swap, "Swap:\n");

  return 0;
}
