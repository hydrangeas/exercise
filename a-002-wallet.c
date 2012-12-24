#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int
main(int argc, char* argv[]) {
  int price = 524;
  int *coin;
  int coinKind[7] = {0, 500, 100, 50, 10, 5, 1};
  int coinLen = 0;
  int *combination;
  int combinationLen = 0;
  int combinationMax = 0;

  /*
   * red data
   */
  int data[7] = {0};
  fscanf(stdin, "%d %d %d %d %d %d %d",
      &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6]);
  /*
   * summary
   */
  int coinCnt = 0;
  for (int i = 1; i < 7; i++) {
    coinCnt = coinCnt + data[i];
  }
  price = data[0];
  coin = (int*) calloc (coinCnt, sizeof(int));
  //coinLen = sizeof(coin) / sizeof(coin[0]);
  coinLen = coinCnt;
  combinationMax = pow(2, coinLen);
#ifdef DEBUG
  fprintf(stdout, "coinCnt/%d\n", coinCnt);
  fprintf(stdout, "coinLen/%d\n", coinLen);
#endif 

  int cnt = 0;
  for (int i = 1; i < 7; i++) {
    for (int j = 0; j < data[i]; j++) {
      coin[cnt] = coinKind[i];
      cnt++;
    }
  }

#ifdef DEBUG
  for (int i = 0; i < cnt; i++) {
    fprintf(stdout, "%d ", coin[i]);
  }
  fprintf(stdout, "\n");
#endif

  combination = (int *) calloc (combinationMax, sizeof(int));

  combination[0] = coin[0] * 0;
  combination[1] = coin[0] * 1;
  combinationLen = 2;

  /*
   * combination of coins by wallet
   */
  for (int i = 1; i < coinLen; i++) {
    int *tmp = (int *) calloc (combinationMax, sizeof(int));
    memcpy(tmp, combination, combinationMax * sizeof(int));
    for (int j = 0; j < combinationLen; j++) {
      combination[2 * j] = tmp[j] + coin[i] * 0;
      combination[2 * j + 1] = tmp[j] + coin[i] * 1;
    }
    combinationLen = combinationLen * 2;
    free(tmp);
  }

  qsort(combination, combinationLen, sizeof(int), compare_int);

  /*
   * Calculate all changes
   */
  int *change;
  change = (int*) calloc (combinationLen, sizeof(int));
  //memcpy(change, combination, combinationLen * sizeof(int));
  for (int i = 0; i < combinationLen; i++) {
    change[i] = combination[i] - price;
  }

  /*
   * Calculate coins from changes
   */
  int *changeCoin;
  changeCoin = (int*) calloc (combinationLen, sizeof(int));
  for (int i = 0; i < combinationLen; i++) {
#ifdef DEBUG
    fprintf(stdout, "%d ", combination[i]);
#endif
    changeCoin[i] = coinCount(change[i]);
  }
#ifdef DEBUG
  fprintf(stdout, "\n");
#endif

  qsort(changeCoin, combinationLen, sizeof(int), compare_int);

  /*
   * Minimum Coin Counts
   */
  int min = -1;
  for (int i = 0; i < combinationLen; i++) {
#ifdef DEBUG
    fprintf(stdout, "min? compare:%d (min:%d)\n", changeCoin[i], min);
#endif
    if (changeCoin[i] >= 0 && min < 0) {
      // only first
      min = changeCoin[i];
    } else if (changeCoin[i] < min) {
      min = changeCoin[i];
    }
  }

  if (min < 0) {
    fprintf(stderr, "[ERROR] You have not enough money!\n");
    exit(EXIT_FAILURE);
  }
  fprintf(stdout, "minimum change coins are %d\n", min);

  free(coin);
  free(combination);
  free(change);
  free(changeCoin);
  return 0;
}


