#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> p3i;

typedef vector<int> vi;
typedef vector<pii> vp;
typedef vector<vp > vv;

#define snd second
#define fst first

const int A = 1E3;
const int B = 2E0;
const int X = 1E8;

int dis[A][B];

void shortestPath(vv & graph, int s) {
  priority_queue<p3i> q;
  int d = dis[s][0] = 0;
  pii p = pii(0, s);
  q.push(p3i(d, p));
  while (!q.empty()) {
    int curD = -q.top().fst;
    int curU =  q.top().snd.snd;
    int curP =  q.top().snd.fst; q.pop();
    for (auto & p: graph[curU]) {
      int nxtD = p.snd + curD;
      int nxtU = p.fst;
      int nxtP = !curP;
      if (dis[nxtU][nxtP] > nxtD) {
        int d = dis[nxtU][nxtP] = nxtD;
        pii p = pii(nxtP, nxtU);
        q.push(p3i(-d, p));
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n,  m;
  int u,  v;
  int w,  x;
  int T = 0;
  while (cin >> n >> m) {
    vv graph(n);
    while (m--) {
      cin >> u >> v >> w;
      graph[u].push_back(pii(v, w));
      graph[v].push_back(pii(u, w));
    }
    for (int i = 0; i < A; i++)
      fill(dis[i], dis[i] + B, X);
    shortestPath(graph, 0);
    cout << "Set #" << ++T << '\n' << (dis[n - 1][0] == X ? "?" : to_string(dis[n - 1][0])) << '\n';
  }
  return 0;
}
