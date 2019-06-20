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

  int n = T.length();
  int b = MUS[m-1].first;
  int e = MUS[m-1].second;
  std::vector<std::pair<int, int> > LSinterval;
  LSinterval.push_back(std::make_pair(b+1, n-1));
  printf("Longest Repeating Suffix (LS): \n");
  print_intervals(LSinterval);

  std::string SS = "";
  int startSS = n;
  for (int i = b; i <= n-1; i++) {
      std::string suf = T.substr(i, n-i);
      //printf("%s\n", suf.c_str());
      int j = 0;
      int occ = 0;
      while(j < n) {
          int c = T.find(suf, j);
          if (c == -1) break;
          occ++;
          if (occ > 2) {
              SS += T.substr(i-1, n-(i-1)+1);
              startSS = i-1;
              break;
          }
          //printf("c = %d\n", c+1);
          j = c+1;
      }
      //printf("occ = %d\n", occ);
      if (SS != "") break;
  }
  //printf("SS = %s\n", SS.c_str());

  std::vector<std::pair<int, int> > SSinterval;
  SSinterval.push_back(std::make_pair(startSS, n-1));
  printf("Shortest occ \\leq 2 Suffix (SS): \n");
  print_intervals(SSinterval);




  //printf("%d %d\n", b+1, e+1);
  /*
  int * MUSlen = new int[m];
  for (int i = 0; i < m; i++) {
      MUSlen[i] = MUS[i].second - MUS[i].first + 1;
//      printf("%d\n", MUSlen[i]);
  }

  delete [] MUSlen;
  */
  return 0;
}
