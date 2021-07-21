#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < n; ++i)
template <class T>
inline bool checkMax(T &a, const T b) {
  return a < b ? a = b, 1 : 0;
}
const int N = 8, M = 8;
const int offset = 3, mask = (1 << offset) - 1;
int A[N + 1][M + 1];
int n, m;
int ans, d;
const int MaxSZ = 16796, Prime = 9973;
struct hashTable {
  int head[Prime], next[MaxSZ], sz;
  int state[MaxSZ];
  int key[MaxSZ];
  inline void clear() {
    sz = 0;
    memset(head, -1, sizeof(head));
  }
  inline void push(int s) {
    int x = s % Prime;
    for (int i = head[x]; ~i; i = next[i]) {
      if (state[i] == s) {
        checkMax(key[i], d);
        return;
      }
    }
    state[sz] = s, key[sz] = d;
    next[sz] = head[x];
    head[x] = sz++;
  }
  void roll() { for(int i=0;i<sz;i++) state[i] <<= offset; }
} H[2][3], *H0, *H1;
int b[M + 1], bb[M + 1];
int encode() {
  int s = 0;
  memset(bb, -1, sizeof(bb));
  int bn = 1;
  bb[0] = 0;
  for (int i = m; i >= 0; --i) {
#define bi bb[b[i]]
    if (!~bi) bi = bn++;
    s <<= offset;
    s |= bi;
  }
  return s;
}
void decode(int s) {
  REP(i, m + 1) {
    b[i] = s & mask;
    s >>= offset;
  }
}
void push(int c, int j, int dn, int rt) {
  b[j] = dn;
  b[j + 1] = rt;
  H1[c].push(encode());
}
void init() {
  cin >> n >> m;
  H0 = H[0], H1 = H[1];
  REP(c, 3) H1[c].clear();
  d = 0;
  H1[0].push(0);
  memset(A, 0, sizeof(A));
  REP(i, n) REP(j, m) cin >> A[i][j];
}
void solve() {
  ans = 0;
  REP(i, n) {
  REP(j, m) {
    checkMax(ans, A[i][j]);  // 需要单独处理一个格子的情况
    if (!A[i][j]) continue;  // 如果有障碍，则跳过，注意这时状态数组不需要滚动
    swap(H0, H1);
    REP(c, 3)
    H1[c].clear();  // c 表示生成和消失事件发生的总次数，最多不超过 2 次
    REP(c, 3) REP(ii, H0[c].sz) {
      decode(H0[c].state[ii]);
      d = H0[c].key[ii] + A[i][j];
      int lt = b[j], up = b[j + 1];
      bool dn = A[i + 1][j], rt = A[i][j + 1];
      if (lt && up) {
        if (lt == up) {  // 在一条路径问题中，我们不能合并相同的插头。
          // Cannot deploy here...
        } else {  // 有可能参与合并的两者中有独立插头，但是也可以用同样的代码片段处理
          REP(i, m + 1) if (b[i] == lt) b[i] = up;
          push(c, j, 0, 0);
        }
      } else if (lt || up) {
        int t = lt | up;
        if (dn) {
          push(c, j, t, 0);
        }
        if (rt) {
          push(c, j, 0, t);
        }
        // 一个插头消失的情况，如果是独立插头则意味着消失，如果是成对出现的插头则相当于生成了一个独立插头，
        // 无论哪一类事件都需要将 c + 1。
        if (c < 2) {
          push(c + 1, j, 0, 0);
        }
      } else {
        d -= A[i][j];
        H1[c].push(H0[c].state[ii]);
        d += A[i][j];    // 跳过插头生成，本题中不要求全部覆盖
        if (dn && rt) {  // 生成一对插头
          push(c, j, m, m);
        }
        if (c < 2) {  // 生成一个独立插头
          if (dn) {
            push(c + 1, j, m, 0);
          }
          if (rt) {
            push(c + 1, j, 0, m);
          }
        }
      }
    }
  }
  REP(c, 3) H1[c].roll();  // 一行结束，调整轮廓线
}
  REP(ii, H1[2].sz) checkMax(ans, H1[2].key[ii]);
  cout << ans << endl;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
#endif
  int T;
  cin >> T;
  while (T--) {
    init();
    solve();
  }
}