#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int X = 1E8;

typedef pair<int, int> pii;
typedef pair<int, pii> p3i;
typedef vector<int> vi;
typedef vector<pii> vp;
typedef vector< vp> vv;
#define snd second
#define fst first

void shortestPath(vv & graph, vi & dis, int s) {
  priority_queue<pii> q;
  int d = dis[s] = 0;
  q.push(pii(-d, s));
  while (!q.empty()) {
    int curU =  q.top().snd;
    int curD = -q.top().fst; q.pop();
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
  int n, m, s, t, u;
  int v, p, q, w, T;
  cin >> T;
  while (T--) {
    vector<p3i> edges;
    cin >> n; n++;
    cin >> m >> s;
    cin >> t >> p;
    vv gst(n);
    vv gts(n);
    while (m--) {
      cin >> u >> v >> w ;
      gst[u].push_back(pii(v, w));
      gts[v].push_back(pii(u, w));
      edges.push_back(p3i(u, pii(v, w)));
    }
    vi st = vi(n, X); shortestPath(gst, st, s);
    vi ts = vi(n, X); shortestPath(gts, ts, t);
    int ans = -1;
    for (auto e: edges) {
      int u = e.fst;
      int v = e.snd.fst;
      int w = e.snd.snd;
      if (st[u] + w + ts[v] <= p)
        ans = max(ans, w);
    }
    cout << ans << '\n';
  }
  return 0;
}
