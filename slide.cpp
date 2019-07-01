#include <string>
#include <vector>
#include <set>
#include <map>
#include "MUS.cpp"

void print_intervals(std::vector<std::pair<int, int> > MUS);
void print_string (std::string Text);

typedef struct {
  std::pair<int, int> interval;
  std::set<int> start_positions;
} MUS;

int main (int argc, char * argv[]) {
  if (argc != 3) exit(1);
  std::string T;
  T = (std::string)argv[1];
  int n = T.length();
  int window_size = atoi(argv[2]);
  print_string(T);

  std::map<std::pair<int, int>, std::set<int> > all_MUSs;
  // [b, e], positions :
  //   [b, e]    : MUS
  //   positions : starting positions of windows.

  for (int i = 0; i < n-window_size+1; i++) {
    std::string w = T.substr(i, window_size);
    std::vector<std::pair<int, int> > muss = compute_MUS(w);
    for (int j = 0; j < (int)muss.size(); j++) {
      //printf("[%d, %d] ", muss[j].first + i + 1, muss[j].second + i + 1);
      std::pair<int, int> mus = std::make_pair(muss[j].first + i + 1, muss[j].second + i + 1);
      all_MUSs[mus].insert(i+1);
    }
    //printf("\n");
  }

  for(auto itr = all_MUSs.begin(); itr != all_MUSs.end(); ++itr) {
    int begin = itr->first.first;
    int end = itr->first.second;
    printf("[%2d, %2d] ", begin, end);
    std::set<int> st = itr->second;
    for(auto stitr = st.begin(); stitr != st.end(); ++stitr) {
      printf("%2d ", *stitr);
    }
    printf("\n");
  }
  //for (int i = 0; i < (int)all_MUSs.size(); i++) {
  //  int begin = all_MUSs[i].first.first;
  //}

  return 0;
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
