#include <string>
#include <vector>
#include "divsufsort.h"

int Ham(std::string A, std::string B) {
  int n = A.length();
  int m = B.length();
  if (n != m) {
    return -1;
  }
  int mis = 0;
  for (int i = 0; i < n; i++) {
    if (A[i] != B[i]) mis++;
  }
  return mis;
}

std::vector<std::pair<int, int> > compute_kMUS (std::string Text, int k) {
  int n = Text.length();
  std::vector<std::pair<int, int> > kMUS;
  int *kLMUS = new int[n];

  for (int i = 0; i < n; i++) {
    kLMUS[i] = n;
    int j = i+k;
    while (j < n) {
      int l = j-i+1;
      std::string A = Text.substr(i, l);
      bool is_k_unique = true;
      for (int p = 0; p < n-l+1; p++) {
        if (p == i) continue;
        std::string B = Text.substr(p, l);
        int d = Ham(A, B);
        //printf("%s, %s, %d\n", A.c_str(), B.c_str(), d);
        if (d <= k) {
          is_k_unique = false;
          j++;
          break;
        }
      }
      if (is_k_unique) {
        kLMUS[i] = j;
        break;
      }
    }
  }

  /*
  for (int i = 0; i < n; i++) {
    printf("%d", kLMUS[i]);
  }
  printf("\n");
  */

  for (int i = 1; i < n; i++) {
    if (kLMUS[i-1] != kLMUS[i]) {
      std::pair<int, int> p = std::make_pair(i-1, kLMUS[i-1]);
      kMUS.push_back(p);
    }
  }
  if (kLMUS[n-1] == n-1) {
    std::pair<int, int> p = std::make_pair(n-1, kLMUS[n-1]);
    kMUS.push_back(p);
  }

  delete [] kLMUS;

  return kMUS;
}

