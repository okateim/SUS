#include "util.cpp"

int main (int argc, char * argv[]) {
  if (argc != 2) exit(1);
  std::string T;
  T = (std::string)argv[1];
  print_string(T);
  std::vector<std::pair<int, int> > MUS = compute_MUS(T);
  print_intervals(MUS);

  int m = MUS.size();
  printf("number of MUSs: %d\n", m);
  int * MUSlen = new int[m];
  for (int i = 0; i < m; i++) {
      MUSlen[i] = MUS[i].second - MUS[i].first + 1;
      printf("%d\n", MUSlen[i]);
  }

  delete [] MUSlen;
  return 0;
}
