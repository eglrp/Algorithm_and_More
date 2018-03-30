// Sudoku Solver
#define REP(i, n) for (int i = 0; i < (n); i++)

class Solution {
private:
  static const int N = 9, MAXR = N*N*N, MAXC = N*N*4, M = MAXC+1+MAXR*4;
  int L[M], R[M], U[M], D[M], col[M], size[M], res[N*N];
  pair<int, int> mean[M];
  void cover(int c) {
    L[R[c]] = L[c];
    R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i])
      for (int j = R[i]; j != i; j = R[j]) {
        U[D[j]] = U[j];
        D[U[j]] = D[j];
      }
  }
  void uncover(int c) {
    for (int i = U[c]; i != c; i = U[i])
      for (int j = L[i]; j != i; j = L[j])
        U[D[j]] = D[U[j]] = j;
    L[R[c]] = R[L[c]] = c;
  }
  void insert(int i, int l, int r, int c) {
    L[i] = l; R[i] = r;
    D[U[i] = U[c]] = i;
    U[D[i] = c] = i;
    col[i] = c;
    size[c]++;
  }
  bool dlx(vector<vector<char> > &a) {
    if (R[MAXC] == MAXC)
      return true;
    int c, mins = INT_MAX;
    for (int i = R[MAXC]; i != MAXC; i = R[i])
      if (size[i] < mins)
        mins = size[c = i];
    cover(c);
    for (int i = D[c]; i != c; i = D[i]) {
      for (int j = R[i]; j != i; j = R[j])
        cover(col[j]);
      a[mean[i].first/9][mean[i].first%9] = '1'+mean[i].second;
      if (dlx(a)) return true;
      for (int j = L[i]; j != i; j = L[j])
        uncover(col[j]);
    }
    uncover(c);
    return false;
  }
public:
  void solveSudoku(vector<vector<char> > &a) {
    int cur = MAXC+1, lo, hi;
    REP(i, cur) {
      L[i] = i-1;
      R[i] = i+1;
      U[i] = D[i] = i;
      size[i] = 0;
    }
    R[L[0] = MAXC] = 0;
    REP(i, N)
      REP(j, N) {
        if (a[i][j] != '.') {
          lo = a[i][j]-'1';
          hi = a[i][j]-'0';
        } else {
          lo = 0;
          hi = 9;
        }
        for (int k = lo; k < hi; k++) {
          pair<int, int> me = make_pair(i*N+j, k);
          insert(cur, cur+3, cur+1, i*N+k); mean[cur] = me;
          insert(cur+1, cur, cur+2, N*N+j*N+k); mean[cur+1] = me;
          insert(cur+2, cur+1, cur+3, N*N*2+i*N+j); mean[cur+2] = me;
          insert(cur+3, cur+2, cur, N*N*3+(i/3*3+j/3)*N+k); mean[cur+3] = me;
          cur += 4;
        }
      }
    dlx(a);
  }
};
