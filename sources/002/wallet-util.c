#include "wallet.h"

int
compare_int(const void *a, const void *b) {
  return *(int*)a - *(int*)b;
}

int
coinCount (const int change) {
  if (change >= 500) {
    return coinCount(change - 500) + 1;
  } else if (change >= 100) {
    return coinCount(change - 100) + 1;
  } else if (change >= 50) {
    return coinCount(change - 50) + 1;
  } else if (change >= 10) {
    return coinCount(change - 10) + 1;
  } else if (change >= 5) {
    return coinCount(change - 5) + 1;
  }
  return change;
}

