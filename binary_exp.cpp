/*
 * source: cp-algorithms.com/algebra/binary-exp.html
 * date: 06-01-2020
 *
 */
#include <iostream>
using namespace std;

#define ll long long

ll binpow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1) res *= a;
    a *= a;
    b >>= 1;
  }
  return res;
}

ll binpowmod(ll a, ll b, ll m) {
  a %= m;
  ll res = 1;
  while (b) {
    if (b & 1) res = (res * a) % m;
    a = (a * a) % m;
    b >>= 1;
  }
  return res;
}

int main() {
  ll a, b, m;
  cin >> a >> b >> m;
  cout << binpow(a, b) << "\n";
  cout << binpowmod(a, b, m) << "\n";
  return 0;
}
