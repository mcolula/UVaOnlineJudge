#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector< vi> vv;

struct BipartiteGraph {
  int  n;
  int  m;
  vi col;
  vi vis;
  vv net;

  BipartiteGraph(int n, int m): net(n), n(n), m(m) {}

  void addEdge(int u, int v) {
    net[u].push_back(v);
  }

  bool findMatch(int i) {
    for (auto & j: net[i]) if (!vis[j]) {
      vis[j] = true;
      if (col[j] < 0 || findMatch(col[j])) {
        col[j]  = i;
        return true;
      }
    }
    return false;
  }

  int maxMatching() {
    int cnt = 0;
    col = vi(m, -1);
    for (int i  = 0; i < n; i++)
      vis = vi(m), cnt += findMatch(i);
    return cnt;
  }

};

const int B = 1001;
const int A =   22;
const int K =    2;

int good[A][B];
int data[A][B];
int side[A][B];

bool valid(int i, int j, int n, int m) {
  return i >= 0 && j >= 0 && i < n && j < m && good[i][j];
}

int is[K] = {1, 0};
int js[K] = {0, 1};

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  char    c;
  int n,  m;
  int T = 0;
  for (int i = 0; i < A; i++)
    for (int j = 0; j < B; j++)
      side[i][j] = (i + j) & 1;
  while (cin >> n >> m, n + m != 0) {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        cin >> c, good[i][j] = c != '#';
    int o = 0;
    int e = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (good[i][j])
          data[i][j] = (i + j) & 1 ? o++ : e++;
    BipartiteGraph net(o, e);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (good[i][j])
          for (int k = 0; k < K; k++) {
            int nxtI = i + is[k];
            int nxtJ = j + js[k];
            if (valid(nxtI, nxtJ, n, m))
              if (side[i][j])
                net.addEdge(data[i][j], data[nxtI][nxtJ]);
              else
                net.addEdge(data[nxtI][nxtJ], data[i][j]);
          }
    cout << "Case #" << ++T << ": " << (o + e + 1 - 2 * net.maxMatching()) / 2 << '\n';
  }
  return 0;
}
