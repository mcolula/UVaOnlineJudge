#include <iostream>

using namespace std;


typedef long long lld;

const lld    A = 51;
lld N, M, K, T =  0;

lld memo[A][A];
lld test[A][A];

lld count(lld n, lld k) {
  if (n == N && k == 0)
    return 1;
  if (n == N && k != 0)
    return 0;
  if (test[n][k] == T)
    return memo[n][k];
  lld ans = 0;
  for (lld i = 1; i <= M; i++)
    if (n + i <= N)
      ans += count(n + i, k - 1); 
  test[n][k] = T;
  return memo[n][k] = ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  while (T++, cin >> N >> K >> M)
    cout << count(0, K) <<  "\n";
  return 0;
}
