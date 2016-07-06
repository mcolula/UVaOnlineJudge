#include <iostream>

using namespace std;

const int M = 1000000;
const int A =   10001;

int memo[A];

int count(int n) {
  if (n == 0)
    return 0;
  if (memo[n] >= 0)
    return memo[n];
  int ans = M;
  for (int i = 1; i * i <= n; i++)
    ans = min(ans, 1 + count(n - i * i));
  return memo[n] = ans;
}


int main () {
  ios::sync_with_stdio(0); cin.tie(0);
  fill(memo, memo + A, -1);
  int n, t;
  cin >> t;
  while (t--)
    cin >> n, cout << count(n) << '\n';
  return 0;
}
