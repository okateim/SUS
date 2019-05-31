#include <string>
#include <vector>
#include "divsufsort.h"

std::vector<std::pair<int, int> > compute_MUS (std::string Text) {
  int n = Text.length();
  int *SA = new int[n];
  int *ISA = new int[n];
  int *LCP = new int[n+1];

  // SA
  divsufsort((unsigned char *)Text.c_str(), SA, n);
  // ISA
  for(int i = 0; i < n; ++i) ISA[SA[i]] = i;
  // LCP
  int lcp = 0;
  LCP[0] = LCP[n] = 0;
  for (int i = 0; i < n; i++) {
    int index = ISA[i];
    if (index == 0) continue;
    int pos = SA[index];
    int prev_pos = SA[index-1];
    while (Text[pos+lcp] == Text[prev_pos+lcp]) {
      lcp++;
      if (pos+lcp == n || prev_pos+lcp == n) break;
    }
    LCP[index] = lcp;
    lcp = std::max(0, lcp-1);
  }

  // MUS
  int m = 0;
  for (int i = 0; i < n; i++) {
    int l1 = std::max(LCP[ISA[i]], LCP[ISA[i]+1]);
    int l2 = i == n-1 ? 0 : std::max(LCP[ISA[i+1]], LCP[ISA[i+1]+1]);
    if (i + l1 > n - 1) continue;
    if (l1 <= l2) m++;
  }

  std::vector<std::pair<int, int> > MUS;
  int mus_index = 0;
  for (int i = 0; i < n; i++) {
    int l1 = std::max(LCP[ISA[i]], LCP[ISA[i]+1]);
    int l2 = i == n-1 ? 0 : std::max(LCP[ISA[i+1]], LCP[ISA[i+1]+1]);
    if (i + l1 > n - 1) continue;
    if (l1 <= l2) {
      std::pair<int, int> p = std::make_pair(i, i+l1);
      MUS.push_back(p);
      mus_index++;
    }
  }
  delete[] SA;
  delete[] ISA;
  delete[] LCP;

  return MUS;
}

