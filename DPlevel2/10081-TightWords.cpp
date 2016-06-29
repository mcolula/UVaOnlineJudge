#include <iostream>
#include <iomanip>

using namespace std;

const int A = 101;
const int B =  11;
int N, K, T =   0;
double test[A][B];
double memo[A][B];

double probability(int idx, int num) {
  if (idx == N)
    return 100;
  if (test[idx][num] == T)
    return memo[idx][num];
  double ans = probability(idx + 1, num) / (K + 1.0);
  if (num + 1 <= K)
    ans += probability(idx + 1, num + 1) / (K + 1.0);
  if (num - 1 >= 0)
    ans += probability(idx + 1, num + 1) / (K + 1.0);
  test[idx][num] = T;
  return memo[idx][num] = ans;
}


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout <<  fixed  <<  setprecision(5);
  while (T++, cin >> K >> N) {
    double ans = 0.0;
    for (int i = 0; i <= K; i++)
      ans += probability(1, i) / (K + 1.0);
    cout << ans << "\n";
  }
  return 0;
}
