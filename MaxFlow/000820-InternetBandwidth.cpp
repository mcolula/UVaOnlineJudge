#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector< vi> vv;
const int X = 1E6;
const int A = 102;

struct FlowNetwork {

  int prt[A];
  vv  cpy;
  vv  flo;
  vv  net;

  FlowNetwork(int n): cpy(A, vi(A)), flo(A, vi(A)), net(n) {}

  void addEdge(int u, int v, int w = 1) {
    net[u].push_back(v);
    net[v].push_back(u);
    cpy[u][v] += w;
    cpy[v][u] += w;
    flo[v][u] += w;
  }

  int updateFlow(int u, int f = X) {
    int p = prt[u];
    f = p == u ? f: updateFlow(p, min(f, cpy[p][u] - flo[p][u]));
    flo[p][u] += f;
    flo[u][p] -= f;
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

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n,  m;
  int s,  t;
  int u,  v;
  int w,  x;
  int T = 0;
  while (cin >> n, n != 0) {
    FlowNetwork net(n + 1);
    cin >> s >> t >> m;
    while (m--)
      cin >> u  >> v >> w ,
      net.addEdge(v, u, w),
      net.addEdge(u, v, w);
    cout << "Network " << ++T << "\nThe bandwidth is " << net.maxFlow(s, t) << ".\n\n";
  }
  return 0;
}
