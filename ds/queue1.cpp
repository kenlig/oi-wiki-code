#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
typedef long long lld;
typedef long double lf;
typedef unsigned long long uld;
typedef pair<int, int> pii;
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
/******************heading******************/
const int M = 5e4 + 5, P = 505;
int I, m, p;
inline int _(int d) { return (d + p) % p; }
namespace DQ {       // 双栈模拟双端队列
pii fr[M], bc[M];    // front,back; fi:w,se:v;
int tf = 0, tb = 0;  // top
int ff[M][P], fb[M][P];
void update(pii *s, int f[][P], int i) {  // update f[i] from f[i-1]
  FOR(j, 0, p - 1) {
    f[i][j] = f[i - 1][j];
    if (~f[i - 1][_(j - s[i].fi)])
      f[i][j] = max(f[i][j], f[i - 1][_(j - s[i].fi)] + s[i].se);
  }
}
void push_front(pii x) { fr[++tf] = x, update(fr, ff, tf); }
void push_back(pii x) { bc[++tb] = x, update(bc, fb, tb); }
void pop_front() {
  if (tf) {
    --tf;
    return;
  }
  int mid = (tb + 1) / 2, top = tb;
  ROF(i, mid, 1) push_front(bc[i]);
  tb = 0;
  FOR(i, mid + 1, top) push_back(bc[i]);
  --tf;
}
void pop_back() {
  if (tb) {
    --tb;
    return;
  }
  int mid = (tf + 1) / 2, top = tf;
  ROF(i, mid, 1) push_back(fr[i]);
  tf = 0;
  FOR(i, mid + 1, top) push_front(fr[i]);
  --tb;
}
int q[M], ql, qr;
int query(int l, int r) {
  const int *const f = ff[tf], *const g = fb[tb];
  int ans = -1;
  ql = 1, qr = 0;
  FOR(i, l - p + 1, r - p + 1) {
    int x = g[_(i)];
    while (ql <= qr && g[q[qr]] <= x) --qr;
    q[++qr] = _(i);
  }
  ROF(i, p - 1, 0) {
    if (ql <= qr && ~f[i] && ~g[q[ql]]) ans = max(ans, f[i] + g[q[ql]]);
    // 删 l-i，加 r-i+1
    if (ql <= qr && _(l - i) == q[ql]) ++ql;
    int x = g[_(r - i + 1)];
    while (ql <= qr && g[q[qr]] <= x) --qr;
    q[++qr] = _(r - i + 1);
  }
  return ans;
}
void init() { FOR(i, 1, P - 1) ff[0][i] = fb[0][i] = -1; }
}  // namespace DQ
int main() {
  DQ::init();
  scanf("%d%d%d", &I, &m, &p);
  FOR(i, 1, m) {
    char op[5];
    int x, y;
    scanf("%s%d%d", op, &x, &y);
    if (op[0] == 'I' && op[1] == 'F')
      DQ::push_front(mk(_(x), y));
    else if (op[0] == 'I' && op[1] == 'G')
      DQ::push_back(mk(_(x), y));
    else if (op[0] == 'D' && op[1] == 'F')
      DQ::pop_front();
    else if (op[0] == 'D' && op[1] == 'G')
      DQ::pop_back();
    else
      printf("%d\n", DQ::query(x, y));
  }
  return 0;
}