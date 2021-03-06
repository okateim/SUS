#include <string>
#include <vector>
#include "kMUS.cpp"

void print_MUS_intervals(std::vector<std::pair<int, int> > MUS);
void print_string (std::string Text);

int main (int argc, char * argv[]) {
  if (argc != 3) exit(1);
  std::string T;
  T = (std::string)argv[1];
  int k = atoi(argv[2]);
  print_string(T);
  std::vector<std::pair<int, int> > kMUS = compute_kMUS(T, k);
  print_MUS_intervals(kMUS);

  int m = kMUS.size();
  if (k == 0) printf("number of MUSs: %d\n", m);
  else printf("number of %d-MUSs: %d\n", k, m);
  return 0;
}

void print_MUS_intervals(std::vector<std::pair<int, int> > MUS) {
  int m = MUS.size();
  int remain = m;
  int *REMAIN = new int[m];
  for (int i = 0; i < m; i++) REMAIN[i] = 1;
  int mus_index = 0;
  int mb = 0, me = -1;
  int pre_me = -1;

//  printf("%d\n", m);
//  return;

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
