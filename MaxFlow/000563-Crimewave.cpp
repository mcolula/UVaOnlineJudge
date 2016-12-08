#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector< vi> vv;
const int A = 5010;
const int X =  1E5;

struct FlowNetwork {

  int prt[A];
  vv  cpy;
  vv  flo;
  vv  net;

  FlowNetwork(int n): cpy(n, vi(n)), flo(n, vi(n)), net(n) {}

  void addEdge(int u, int v, int w = 1) {
    net[u].push_back(v);
    net[v].push_back(u);
    cpy[u][v] += w;
    cpy[v][u] += w;
    flo[v][u] += w;
  }

  int updateFlow(int s, int f = X) {
    int p = prt[s];
    f = p == s ? f: updateFlow(p, min(f, cpy[p][s] - flo[p][s]));
    flo[p][s] += f;
    flo[s][p] -= f;
    return f;
  }

  int bfs(int s, int t) {
    queue<int> q; q.push(s);
    fill(prt, prt + A,  -1);
    prt[s] = s;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == t) break;
      for (auto & v: net[u])
        if (prt[v] < 0 && cpy[u][v] > flo[u][v])
          prt[v] = u, q.push(v);
    }
    return prt[t] >= 0 ? updateFlow(t) : 0;
  }

  int maxFlow(int s, int t) {
    int ans = 0;
    while (int f = bfs(s, t))
      ans += f;
    return ans;
  }
};

#define cur(i, j) ((i) * m + j)
#define nxt(i, j) cur(n + i, j)

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, m;
  int u, v;
  int k, t;
  cin >> t;
  while (t--) {
    cin >> n;
    cin >> m;
    cin >> k;
    int s = 2 * n * m;
    int t = 2 * n * m + 1;
    FlowNetwork net(t + 1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (i == 0 || i + 1 == n || j == 0 || j + 1 == m)
          net.addEdge(nxt(i, j), t);
        if (i + 1 < n)
          net.addEdge(nxt(i, j), cur(i + 1, j)),
          net.addEdge(nxt(i + 1, j), cur(i, j));
        if (j + 1 < m)
          net.addEdge(nxt(i, j), cur(i, j + 1)),
          net.addEdge(nxt(i, j + 1), cur(i, j));
        net.addEdge(cur(i, j), nxt(i, j));
      }
    }
    for (int i = 0; i < k; i++) {
      cin >> u; u -= 1;
      cin >> v; v -= 1;
      net.addEdge(s, cur(u, v));
    }
    cout << (k == net.maxFlow(s, t) ? "" : "not ") <<  "possible\n";
  }
  return 0;
}
