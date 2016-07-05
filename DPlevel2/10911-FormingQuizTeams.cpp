#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int A = 17;

string name[A];
int xs[A];
int ys[A];
int N = 0;
int T = 0;

double memo[1 << A][A][2];
double test[1 << A][A][2];

double cost(int p,  int q) {
  return sqrt(pow(xs[p] - xs[q], 2) + pow(ys[p] - ys[q], 2));
}

double mincost(int msk, int lst, bool usd) {
  if (msk == (1 << N) - 1)
    return  0;
  if (test[msk][lst][usd] == T)
    return memo[msk][lst][usd];
  double ans = 1  / 0.0;
  for (int i = 0; i < N; i++) if (!(msk & 1 << i))
    ans = min(ans, usd * cost(lst, i) + mincost(msk | 1 << i, i, !usd));
  test[msk][lst][usd] = T;
  return memo[msk][lst][usd] = ans;
}


int main() {
  cout << fixed << setprecision(2);
  ios::sync_with_stdio(0); cin.tie(0);
  while (T++, cin >> N, N *= 2, N != 0) {
    for (int i = 0; i < N; i++)
      cin >> name[i] >> xs[i] >> ys[i];
    double ans = 1  / 0.0;
    for (int i = 0; i < N; i++)
      ans = min(ans, mincost(1 << i, i, 1));
    cout << "Case " << T << ": " << ans << "\n";
  }
  return 0;
}
