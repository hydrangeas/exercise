#include <stdio.h>
#include <stdlib.h>

/*
 * ソース。
 * スートはS/0x01, H/0x, D/2, C/3
 * A/J/Q/Kは1/11/12/13として考える
 */
#define S 0x01
#define H 0x02
#define D 0x04
#define C 0x08

/*
 * stdlib組み込みのqsortを使うための評価関数
 */
int
compare(const void *a, const void *b)
{
  return *(unsigned char*)a - *(unsigned char*)b;
}

int
main(int argc, char* argv[])
{
  char st_in[5] = {0};
  int nm_in[5] = {0};
  unsigned char st[5] = {0};
  unsigned char nm[5] = {0};

  fscanf(stdin, "%c %c %c %c %c", &st_in[0], &st_in[1], &st_in[2], &st_in[3], &st_in[4]);
  fscanf(stdin, "%d %d %d %d %d", &nm_in[0], &nm_in[1], &nm_in[2], &nm_in[3], &nm_in[4]);
  for (int i = 0; i < 5; i++) {
    switch (st_in[i]) {
      case 'S':
        st[i] = S;
        break;
      case 'H':
        st[i] = H;
        break;
      case 'D':
        st[i] = D;
        break;
      case 'C':
        st[i] = C;
        break;
      default:
        break;
    }
    nm[i] = (unsigned char) nm_in[i];
  }
  /*
   * スートをソートしておく
   */
  qsort(st, 5, sizeof(unsigned char), compare);

  /*
   * すべてのスートの排他的論理和が同じときはフラッシュの条件を満たす
   */
  int isFlash = 0;
  unsigned char checkFlash = st[0] ^ st[1] ^ st[2] ^ st[3] ^ st[4];
  if (checkFlash == st[0]) {
    isFlash = 1;
  }

  /*
   * 数字をソートしておく
   */
  qsort(nm, 5, sizeof(unsigned char), compare);

  int isStraight = 1;
  int pair[5] = {0};
  int dup = 1;
  for (int i = 1; i < 5; i++) {
    unsigned char diff = nm[i] - nm[i - 1];
    if (diff != 1 && ( ! (i == 1 && nm[0] == 1 && diff == 9))) {
      /*
       * 数字と数字とのステップが１でない場合はストレートの条件を満たさない
       * また、最初が１で次が１０の場合だけはストレートの要件を満たすとみなす
       * （ロイヤルストレートのため）
       */
      isStraight = 0;
    }

    /*
     * 差分がない場合は何回重複したか（何枚のカードが同じ番号か）をチェック
     * 差分が生じた場合に、ペアをカウントする配列をインクリメントする
     */
    if (diff == 0) {
      dup = dup + 1;
    } else {
      pair[dup] = pair[dup] + 1;
      dup = 1;
    }
  }
  // TODO: 最後の情報がループの中では取れない
  pair[dup] = pair[dup] + 1;

#ifdef DEBUG
  fprintf(stderr, "isFlash=%d, isStraight=%d\n", isFlash, isStraight);
  fprintf(stderr, "suit : %d\n", (int)checkFlash);
  fprintf(stderr, "pair\n");
  fprintf(stderr, "  [0]: %d\n", pair[0]);
  fprintf(stderr, "  [1]: %d\n", pair[1]);
  fprintf(stderr, "  [2]: %d\n", pair[2]);
  fprintf(stderr, "  [3]: %d\n", pair[3]);
  fprintf(stderr, "  [4]: %d\n", pair[4]);
#endif

  /*
   * とりあえずごりごり評価する
   */
  if (isFlash) {
    if (isStraight) {
      if (nm[0] == 1 && nm[4] == 13) {
        fprintf(stdout, "Royal Straight Flash!\n");
      } else {
        fprintf(stdout, "Straight Flash!\n");
      }
    } else {
      fprintf(stdout, "Flash!\n");
    }
    exit(EXIT_SUCCESS);
  } else {
    if (isStraight) {
      fprintf(stdout, "Straight!\n");
      exit(EXIT_SUCCESS);
    } else if (pair[4] > 0) {
      fprintf(stdout, "Four of a kind!\n");
      exit(EXIT_SUCCESS);
    } else if (pair[3] > 0) {
      if (pair[2] > 0) {
        fprintf(stdout, "Full House!\n");
      } else {
        fprintf(stdout, "Three of a kind!\n");
      }
      exit(EXIT_SUCCESS);
    } else if (pair[2] > 1) {
      fprintf(stdout, "Two pair!\n");
      exit(EXIT_SUCCESS);
    } else if (pair[2] > 1) {
      fprintf(stdout, "One pair!\n");
      exit(EXIT_SUCCESS);
    }
  }
  fprintf(stdout, "No pair..\n");

  return 0;
}

