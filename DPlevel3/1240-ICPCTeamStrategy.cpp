#include <iostream>

using namespace std;

const int A = 281;
const int B =  12;

int memo[A][4][1 << B];
int test[A][4][1 << B];
int data[3][B];
int N, T = 0;

int maxvalue(int sum, int lst, int msk) {
  if (test[sum][lst][msk] == T)
    return memo[sum][lst][msk];
  int ans = 0;
  for (int i = 0; i < 3; i++)
    if (i != lst)
      for (int j = 0; j < N; j++)
        if ((msk & (1 << j)) == 0  && sum + data[i][j] <= 280)
          ans = max(ans, 1 + maxvalue(sum + data[i][j], i, msk | (1 << j)));
  test[sum][lst][msk] = T;
  return memo[sum][lst][msk] = ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int    t;
  cin >> t;
  while (T++, t--) {
    cin >> N;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < N; j++)
        cin >> data[i][j];
    cout << maxvalue(0, 3, 0) << "\n";
  }
  return 0;
}
