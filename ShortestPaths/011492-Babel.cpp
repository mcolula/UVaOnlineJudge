#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> p3i;

typedef vector<int> vi;
typedef vector<p3i> vp;
typedef vector<vp > vv;

#define id(s) (z.find(s) != z.end() ? z[s] : z[s] = z.size())
#define add   push_back
#define snd   second
#define fst   first

map<string, int> z;

const int B = 4005;
const int X =  1E7;
const int A =   29;

int dis[A][B];

void shortestPath(vv & graph, int s) {
  priority_queue<p3i>  q;
  int d = dis[s][28] = 0;
  pii p = pii(28, s);
  q.push(p3i(-d, p));
  while (!q.empty()) {
    int curD = -q.top().fst;
    int curC =  q.top().snd.fst;
    int curU =  q.top().snd.snd; q.pop();
    for (auto & p: graph[curU]) {
      int nxtD = p.snd.snd + curD;
      int nxtC = p.snd.fst;
      int nxtU = p.fst;
      if (dis[nxtC][nxtU] > nxtD && curC != nxtC) {
        int d = dis[nxtC][nxtU] = nxtD;
        pii p = pii(nxtC, nxtU);
        q.push(p3i(-d, p));
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m;
  string s;
  string t;
  string w;
  while (cin >> n, n != 0) {
    vv graph(2 * n + 5);  z.clear();
    cin >> s; int u = id(s);
    cin >> s; int v = id(s);
    for (int i = 0; i < n; i++) {
      cin >> s >> t >> w;
      int a = id(s);
      int b = id(t);
      graph[a].push_back(p3i(b ,pii(w[0] - 'a', w.size())));
      graph[b].push_back(p3i(a ,pii(w[0] - 'a', w.size())));
    }
    for (int i = 0; i < A; i++)
      fill(dis[i], dis[i] + z.size() + 5, X);
    shortestPath(graph, u);
    int ans = X;
    for (int i = 0; i < A; i++)
      ans = min(ans, dis[i][v]);
    cout << (ans >= X ? "impossivel" : to_string(ans)) << '\n';
  }
  return 0;
}
