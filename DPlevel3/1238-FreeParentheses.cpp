#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const int A = 6001;
const int B = 3000;
const int C =   31;
int memo[C][C][A];
int test[C][C][A];
vector<int> num;
vector<int> sgn;
int T = 1;

bool valid(int idx, int opn, int sum) {
  if (idx == num.size() && sum == 0)
    return  1;
  if (idx == num.size() && sum != 0)
    return  0;
  if (test[idx][opn][sum + B] == T)
    return memo[idx][opn][sum + B];
  int ans = 0;
  int nxt = 0;
  if (opn > 0)
    ans |= valid(idx, opn - 1, sum);
  nxt += num[idx] * sgn[idx];
  nxt *= (opn & 1 ? -1 :  1);
  if (sgn[idx] < 0)
    ans |= valid(idx + 1, opn + 1, sum - nxt);
  ans |= valid(idx + 1, opn, sum - nxt);
  test[idx][opn][sum + B] = T;
  return memo[idx][opn][sum + B] = ans;
}


int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int    n;
  char   c;
  string s;
  while (T++, getline(cin, s)) {
    stringstream ss(s); ss >> n;
    num.clear(); sgn.clear();
    num.push_back(n);
    sgn.push_back(1);
    while (ss >> c >> n)
      sgn.push_back((c == '+' ? 1 : -1)), num.push_back(n);
    int ans = 0;
    for (int i = -3000; i <= 3000; i++)
      if (valid(0, 0, i))
        ans++;
    cout << ans << "\n";
  }
  return 0;
}
