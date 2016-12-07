#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> vi;
typedef vector< vi> vv;

struct BipartiteGraph {
  int  n;
  int  m;
  vi col;
  vi row;
  vv net;
  vi vis;

  BipartiteGraph(int n, int m): net(n), n(n), m(m) {}

  void addEdge(int u, int v) {
    net[u].push_back(v);
  }

  bool findMatch(int i) {
    for (auto & j: net[i]) if (!vis[j]) {
      vis[j] = true;
      if (col[j] < 0 || findMatch(col[j])) {
        row[i] = j;
        col[j] = i;
        return true;
      }
    }
    return false;
  }

  int maxMatching() {
    int cnt = 0;
    row = vi(n, -1);
    col = vi(m, -1);
    for (int i  = 0; i < n; i++)
      vis = vi(m), cnt += findMatch(i);
    return cnt;
  }

};

int main() {
  int n, m;
  int x, t;
  cin >> t;
  for (int T = 1; T <= t; T++) {
    cin >> n;
    cin >> m;
    BipartiteGraph net(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> x;
        if (x != 0)
          net.addEdge(i, j);
      }
    }
    cout << "Case " << T << ": a maximum of " << net.maxMatching() << " nuts and bolts can be fitted together\n";
  }
  return 0;
}
