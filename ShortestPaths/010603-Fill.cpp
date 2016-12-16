  #include <iostream>
  #include <vector>
  #include <queue>

  using namespace std;

  typedef pair<int, int> pii;
  typedef pair<pii, pii> p4i;

  #define snd second
  #define fst first

  const int X = 1E8;
  const int A = 201;
  const int B =   4;

  int dis[A][A][A];
  int wat[A];
  int cur[B];
  int nxt[B];
  int cpy[B];

  void shortestPath(int a, int b, int c) {
    wat[a] = wat[b] = wat[c] = 0;
    priority_queue<p4i>    q;
    int d = dis[a][b][c] = 0;
    pii u = pii(d, a);
    pii v = pii(b, c);
    q.push(p4i(u, v));
    while (!q.empty()) {
      cur[3] = -q.top().fst.fst;
      cur[0] =  q.top().fst.snd;
      cur[1] =  q.top().snd.fst;
      cur[2] =  q.top().snd.snd; q.pop();
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < B; k++)
            nxt[k] = cur[k];
          if (i != j && cur[i] > 0 && cur[j] < cpy[j]) {
            int pour = min(cur[i], cpy[j] - cur[j]);
            nxt[i]  -= pour;
            nxt[j]  += pour;
            nxt[3]  += pour;
            if (dis[nxt[0]][nxt[1]][nxt[2]] > nxt[3]) {
              int d = dis[nxt[0]][nxt[1]][nxt[2]] = nxt[3];
              pii u = pii(    -d, nxt[0]);
              pii v = pii(nxt[1], nxt[2]);
              wat[nxt[0]] = min(wat[nxt[0]], nxt[3]);
              wat[nxt[1]] = min(wat[nxt[1]], nxt[3]);
              wat[nxt[2]] = min(wat[nxt[2]], nxt[3]);
              q.push(p4i(u, v));
            }
          }
        }
      }
    }
  }

  int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int d, t;
    cin >> t;
    while (t--) {
      cin >> cpy[0] >> cpy[1] >> cpy[2] >> d;
      for (int i = 0; i <= cpy[0]; i++)
        for (int j = 0; j <= cpy[1]; j++)
          for (int k = 0; k <= cpy[2]; k++)
            dis[i][j][k] = X;
      fill(wat, wat + A,  X);
      shortestPath(0, 0, cpy[2]);
      while ( wat[d] == X)   d--;
      cout << wat[d] <<  ' ' << d << '\n';
    }
    return 0;
  }
