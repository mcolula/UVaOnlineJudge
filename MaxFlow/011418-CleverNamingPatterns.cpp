#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector< vi> vv;
const int X = 1E6;
const int A = 802;
const int B =  26;

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

vector<string> wrd[B];

string format(string & s) {
  string ans = "";
  for (int i = 0; i < s.size(); i++)
    ans += string(1, i == 0 ? toupper(s[i]) : tolower(s[i]));
  return ans;
}

string match(int i, char c) {
  for (auto & w: wrd[i])
    if (c == w[0])
      return w;
  return "";
}

#define cur(i, j) ((i) * B + j)
#define nxt(i, j) cur(n + i, j)

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  string  s;
  int m,  k;
  int n,  t;
  cin >>  t;
  int T = 0;
  while (t--) {
    cin >> n;
    FlowNetwork net(A);
    for (int i = 0; i < n; i++) {
      cin >> m; wrd[i].clear();
      net.addEdge(nxt(2, 0), nxt(0, i));
      net.addEdge(nxt(1, i), nxt(2, 1));
      for (int j = 0; j < m; j++) {
        cin >> s; s = format(s);
        int x =  s[0]  - 'A';
        wrd[i].push_back( s);
        net.addEdge(nxt(0, i), cur(i, x));
        net.addEdge(cur(i, x), nxt(1, x));
      }
    }
    net.maxFlow(nxt(2, 0), nxt(2, 1));
    cout << "Case #" << ++T  << ":\n";
    for (int i = 0; i < n; i++)
      for (auto & u: net.net[nxt(1, i)])
        if (u != nxt(2, 1) && net.flo[u][nxt(1, i)])
          cout << match(u / B, i + 'A') << '\n';
  }
  return 0;
}
