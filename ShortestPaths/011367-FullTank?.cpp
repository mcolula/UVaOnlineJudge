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

const int A = 1001;
const int B =  101;
const int X =  1E8;
int dis[A][B];
int cst[A];
vv  graph ;

void shortestPath(int s, int c) {
  priority_queue<p3i> q;
  pii p = pii(0, s);
  q.push(p3i(0, p));
  dis[s][0] = 0;
  while (!q.empty()) {
    int curD = -q.top().fst;
    int curF =  q.top().snd.fst;
    int curU =  q.top().snd.snd; q.pop();
    for (auto & p: graph[curU]) {
      if (curF >= p.snd) {
        int nxtF = curF - p.snd;
        int nxtD = curD ;
        int nxtU = p.fst;
        if (dis[nxtU][nxtF] > nxtD)
          q.push(p3i(-(dis[nxtU][nxtF] = nxtD), pii(nxtF, nxtU)));
      }
      if (curF < c) {
        int nxtD = curD + cst[curU];
        int nxtF = curF + 1;
        int nxtU = curU;
        if (dis[nxtU][nxtF] > nxtD)
          q.push(p3i(-(dis[nxtU][nxtF] = nxtD), pii(nxtF, nxtU)));
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m, u, v, w;
  int q, c, d, s, t;
  cin >> n;
  cin >> m;
  graph  = vv(n);
  for (int i = 0; i < n; i++)
    cin >> cst[i];
  for (int i = 0; i < m; i++) {
    cin >> u >> v >> w;
    graph[u].push_back(pii(v, w));
    graph[v].push_back(pii(u, w));
  }
  cin >> m;
  while (m--) {
    cin >> c >> s >> t;
    for (int i = 0; i <= n; i++)
      fill(dis[i], dis[i] + c + 1, X);
    shortestPath(s, c);
    cout << (dis[t][0] == X ? "impossible" : to_string(dis[t][0])) << '\n';
  }
  return 0;
}
