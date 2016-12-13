#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> p3i;
typedef vector<int> vi;
typedef vector<pii> vp;
typedef vector< vp> vv;
#define snd second
#define fst first

const int X = 1E8;

void shortestPath(vv & graph, vi & dis, int s) {
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
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int n, m, s, t;
  int u, v, w, x;
  while (cin >> n >> m, n + m != 0) {
    vector<p3i> edges;
    vv gst(n);
    vv gts(n);
    cin >> s;
    cin >> t;
    while (m--) {
      cin >> u >> v >> w;
      gst[u].push_back(pii(v, w));
      gts[v].push_back(pii(u, w));
      edges.push_back(p3i(u, pii(v, w)));
    }
    vi st(n, X); shortestPath(gst, st, s);
    vi ts(n, X); shortestPath(gts, ts, t);
    vv graph(n);
    for (auto & e: edges) {
      int u = e.fst;
      int v = e.snd.fst;
      int w = e.snd.snd;
      if (st[u] + w + ts[v] != st[t])
        graph[u].push_back(pii(v, w));
    }
    vi ans(n, X);  shortestPath(graph,  ans, s);
    cout << (ans[t] == X ? -1 : ans[t]) << '\n';
  }
  return 0;
}
