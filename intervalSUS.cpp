#include <iostream>
#include "util.cpp"
#include "rmq.h"

#define NIL -1
#define INF 2147483647

int main (int argc, char * argv[]) {
  /*
  if (argc != 2) exit(1);
  std::string T;
  T = (std::string)argv[1];
  */
  std::cout << "input string: ";
  std::string T;
  std::cin >> T;

  // Preprocess
  int n = T.length();
  std::vector<std::pair<int, int> > MUS = compute_MUS(T);
  int m = MUS.size();

  int * pred_on_MUSend = new int[n];
  int j = 0;
  for (int i = 0; i < n; i++) {
    if (j == 0 && MUS[j].second > i) {
      pred_on_MUSend[i] = NIL;
    } else if (j == m-1 && MUS[j].second <= i) {
      pred_on_MUSend[i] = j;
    } else if (MUS[j+1].second == i) {
      j++;
      pred_on_MUSend[i] = j;
    } else {
      pred_on_MUSend[i] = j;
    }
  }
  int * succ_on_MUSstart = new int[n];
  j = 0;
  for (int i = 0; i < n; i++) {
    if (j == m-1 && MUS[j].first < i) {
      succ_on_MUSstart[i] = NIL;
    } else if (MUS[j].first < i) {
      succ_on_MUSstart[i] = j+1;
      j++;
    } else {
      succ_on_MUSstart[i] = j;
    }
  }

  VAL * MUSlen = new VAL[m];
  for (int i = 0; i < m; i++) MUSlen[i] = VAL(MUS[i].second - MUS[i].first + 1);
  struct rmqinfo * ri = rm_query_preprocess(MUSlen, INT(m));

  print_string(T);
  print_intervals(MUS);

  // Query interval: [p, q]
  while(true) {
    int p = 0, q = 0;
    printf("starting position of query interval: "); scanf("%d", &p);
    if (p < 1 || n < p) break; else p--;
    printf("ending position of query interval: "); scanf("%d", &q);
    if (q < p || n < q) break; else q--;

    int left_mus_index = pred_on_MUSend[q] == NIL ? -1 : pred_on_MUSend[q];
    int right_mus_index = succ_on_MUSstart[p] == NIL ? m : succ_on_MUSstart[p];
    std::vector<std::pair<int, int> > SUS;

    if (left_mus_index > right_mus_index) {
      SUS.push_back(std::make_pair(p, q));
    } else {
      int left_len = left_mus_index == -1 ? INF : cover_length(MUS[left_mus_index].first, MUS[left_mus_index].second, p, q);
      int right_len = right_mus_index == m ? INF : cover_length(MUS[right_mus_index].first, MUS[right_mus_index].second, p, q);
      int center_len = INF;
      if (left_mus_index + 1 <= right_mus_index - 1) {
        int center_idx = rm_query(ri, left_mus_index+1, right_mus_index-1);
        center_len = MUSlen[center_idx];
      }
      if (left_len <= center_len && left_len <= right_len) {
        SUS.push_back(cover(MUS[left_mus_index].first, MUS[left_mus_index].second, p, q));
      }
      if (right_len <= center_len && right_len <= left_len && left_mus_index != right_mus_index) {
        SUS.push_back(cover(MUS[right_mus_index].first, MUS[right_mus_index].second, p, q));
      }
      if (center_len <= left_len && center_len <= right_len) {
        std::vector<int> indcies;
        find_leq(MUSlen, ri, left_mus_index+1, right_mus_index-1, center_len, indcies);
        for (int i = 0; i < indcies.size(); i++) {
          SUS.push_back(std::make_pair(MUS[indcies[i]].first, MUS[indcies[i]].second));
        }
      }
    }

    printf("SUSs for interval [%2d, %2d]: ", p+1, q+1);
    for (int i = 0; i < SUS.size(); i++) {
      printf("[%2d, %2d] ", SUS[i].first+1, SUS[i].second+1);
    }
    printf("\n");
    print_intervals(SUS);
  }

  delete [] pred_on_MUSend;
  delete [] succ_on_MUSstart;
  delete [] MUSlen;
  rm_free(ri);
  return 0;
}
