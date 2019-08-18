#include <string>
#include <vector>
#include "MUS.cpp"

#if defined(USERMQ)
#include "rmq.h"
#endif

std::pair<int, int> cover(int i, int j, int k, int l) {
  int x = std::min(i, k);
  int y = std::max(j, l);
  std::pair<int, int> p = std::make_pair(x, y);
  return p;
}

int cover_length(int i, int j, int k, int l) {
  std::pair<int, int> p = cover(i, j, k, l);
  return p.second - p.first + 1;
}

void print_intervals(std::vector<std::pair<int, int> > MUS) {
  int m = MUS.size();
  int remain = m;
  int *REMAIN = new int[m];
  for (int i = 0; i < m; i++) REMAIN[i] = 1;
  int mus_index = 0;
  int mb = 0, me = -1;
  int pre_me = -1;

  while (remain > 0) {
    int i = 0;
    for (i = 0; i < m; i++) {
      if (REMAIN[i] == 0) continue;
      if (MUS[i].first > me) {
        mus_index = i;
        break;
      }
    }
    if (i == m) {
      me = pre_me = -1;
      printf("\n");
      continue;
    }
    mb = MUS[mus_index].first;
    me = MUS[mus_index].second;
    for (int j = 0; j < mb - pre_me - 1; j++) printf("   ");
    printf("|");
    for (int j = 3*mb+1; j < 3*me+2; j++) printf("-");
    printf("|");
    pre_me = me;
    REMAIN[mus_index] = 0;
    remain--;
  }
  printf("\n");
  delete[] REMAIN;
  return;
}

void print_string (std::string T) {
  int n = T.length();
  for (int i = 0; i < n; i++) {
    printf("%2d ", i+1);
  }
  printf("\n");
  for (int i = 0; i < n; i++) {
    printf(" %c ", T[i]);
  }
  printf("\n");
  return;
}

#if defined(USERMQ)
void find_leq(VAL * A, rmqinfo * ri, int left, int right, int threshold, std::vector<int>& indcies) {
  if (left > right) return;
  int idx = rm_query(ri, left, right);
  if (A[idx] > threshold) return;
  indcies.push_back(idx);
  find_leq(A, ri, left, idx-1, threshold, indcies);
  find_leq(A, ri, idx+1, right, threshold, indcies);
  return;
}
#endif
