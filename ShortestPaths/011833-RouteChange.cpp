#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

typedef vector<int> vi;
typedef vector<pii> vp;
typedef vector<vp > vv;

#define add push_back
#define snd second
#define fst first

const int X = 1E8;
const int A = 3E3;

int has[A];
int dis[A];

void shortestPath(vv & graph, int s) {
  priority_queue<pii> q;
  int d = dis[s] = 0;
  q.push(pii(-d, s));
  while (!q.empty()) {
    int curD = -q.top().fst;
    int curU =  q.top().snd; q.pop();
    for (auto & p: graph[curU]) {
      int nxtD = p.snd + curD;
      int nxtU = p.fst;
      if (dis[nxtU] > nxtD)
        q.push(pii(-(dis[nxtU] = nxtD), nxtU));
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m;
  int u, v;
  int k, t;
  int x, q;
  cin >> t;
  for (int T = 1; T <= t; T++) {
    cin >> n;
    cin >> m;
    cin >> k;
    vv graph(n + 1);
    fill(has, has + A, 0);
    for (int i = 0; i <  k; i++)
      cin >> x, has[x] = 1;
    for (int i = 0; i <  m; i++) {
      cin >> u >> v;
      graph[u].push_back(pii(v, !has[v]));
      graph[v].push_back(pii(u, !has[u]));
    }
    cout << "Case " << T << ":\n";
    cin  >> q;
    while ( q--) {
      cin >> u >> v;
      fill(dis, dis + A,  X);
      shortestPath(graph, u);
      cout << (dis[v] == X ? -1 : dis[v] + (!has[u] && u != v)) << '\n';
    }
    cout << '\n';
  }
  return 0;
}
