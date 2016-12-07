#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> vi;
typedef vector< vi> vv;
const int X = 1E3;

struct FlowNetwork {

  vv cpy;
  vv flo;
  vi prt;
  vv net;

  FlowNetwork(int n): net(n), cpy(n, vi(n)), flo(n, vi(n)), prt(n) {}

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

  char match(char s) {
    for (auto & u: net[s])
      if (u >= 'A' && u <= 'Z' && flo[u][s] == 1)
        return u;
    return '_';
  }

};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int  n, m;
  char a, c;
  string  s;
  while (getline(cin, s)) {
    FlowNetwork net(100); m = 0;
    do {
      stringstream ss(s);
      ss >> a;
      ss >> n;
      m  += n;
      net.addEdge(0, a, n);
      while (ss >> c, c != ';')
        net.addEdge(a, c);
    } while(getline(cin, s), s != "");
    for (char i = '0'; i <= '9'; i++)
      net.addEdge(i, 1);
    if (m == net.maxFlow(0, 1))
      for (int i = '0'; i <= '9'; i++)
        cout << net.match(i);
    else
      cout << '!';
    cout << '\n';
  }
  return 0;
}
