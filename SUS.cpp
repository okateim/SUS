#include <iostream>
#include "util.cpp"
#define NIL -1

int main (int argc, char * argv[]) {
  /*
  if (argc != 2) exit(1);
  std::string T;
  T = (std::string)argv[1];
  */
  std::cout << "input string: ";
  std::string T;
  std::cin >> T;
  int n = T.length();
  std::vector<std::pair<int, int> > MUS = compute_MUS(T);
  int m = MUS.size();

  int * pred_on_MUSend = new int[n];
  int j = 0;
  for (int i = 0; i < n; i++) {
    if (j == m-1 && MUS[j].second <= i) {
      pred_on_MUSend[i] = j;
    } else if (MUS[j+1].second == i) {
      pred_on_MUSend[i] = j+1;
      j++;
    } else if (MUS[j].second > i) {
      pred_on_MUSend[i] = NIL;
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

  print_string(T);
  print_intervals(MUS);
  while(true) {
    int p = 0;
    printf("query position: "); scanf("%d", &p);
    if (p < 1 || n < p) break; else p--;
    int left_mus_index = pred_on_MUSend[p] == NIL ? 0 : pred_on_MUSend[p];
    int right_mus_index = succ_on_MUSstart[p] == NIL ? m-1 : succ_on_MUSstart[p];
    int MIN = n+1;
    int ans_mus_index = 0;
    for (int i = left_mus_index; i <= right_mus_index; i++) {
      int len = cover_length(MUS[i].first, MUS[i].second, p);
      if (len < MIN) {
        MIN = len;
        ans_mus_index = i;
      }
    }
    printf("SUSs for position %2d: ", p+1);
    std::vector<std::pair<int, int> > SUS;
    for (int i = left_mus_index; i <= right_mus_index; i++) {
      int len = cover_length(MUS[i].first, MUS[i].second, p);
      if (len == MIN) {
        std::pair<int, int> sus = cover(MUS[i].first, MUS[i].second, p);
        SUS.push_back(sus);
        printf("[%2d, %2d] ", sus.first+1, sus.second+1);
      }
    }
    printf("\n");
    print_intervals(SUS);
  }

  delete [] pred_on_MUSend;
  delete [] succ_on_MUSstart;
  return 0;
}
