#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_GAMES 100000000

typedef void (*Method)(bool *);
static uint8_t cars[NUM_GAMES], guesses[NUM_GAMES];

uint8_t rand_to_2() {
  uint8_t num;
  do {
    num = rand() & 3;
  } while (num > 2);
  return num;
}

void init(uint8_t *cars) {
  for (int i = 0; i < NUM_GAMES; i++) {
    cars[i] = rand_to_2();
  }
}

void fn_stay(bool *stay) {
  for (int i = 0; i < NUM_GAMES; i++) {
    stay[i] = cars[i] == guesses[i];
  }
}

void fn_swap(bool *swap) {
  for (int i = 0; i < NUM_GAMES; i++) {
    uint8_t guess = guesses[i];
    uint8_t car = cars[i];
    uint8_t notcar = (guess == 1 || guess == 2) && (car == 1 || car == 2)   ? 0
                     : (guess == 0 || guess == 2) && (car == 0 || car == 2) ? 1
                                                                            : 2;
    uint8_t choice =
        (guess == 1 || guess == 2) && (notcar == 1 || notcar == 2)   ? 0
        : (guess == 0 || guess == 2) && (notcar == 0 || notcar == 2) ? 1
                                                                     : 2;
    swap[i] = choice == cars[i];
  }
}

void play(bool *win_arr, Method method, const char *title) {
  method(win_arr);
  fputs(title, stdout);

  int wins = 0;
  for (int i = 0; i < NUM_GAMES; i++)
    wins += win_arr[i];

  double percentage = (wins / (double)NUM_GAMES) * 100;
  printf("%f%% wins (%d/%d)\n\n", percentage, wins, NUM_GAMES);
}

int main() {
  static bool stay_wins[NUM_GAMES], swap_wins[NUM_GAMES];

  printf("%d games:\n\n", NUM_GAMES);

  srand(time(NULL));
  init(cars);
  init(guesses);

  play(stay_wins, fn_stay, "Stay:\n");
  play(swap_wins, fn_swap, "Swap:\n");

  return 0;
}
