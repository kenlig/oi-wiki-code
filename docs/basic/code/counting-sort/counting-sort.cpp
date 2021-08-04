const int N = 100010;
const int W = 100010;

int n, w, a[N], cnt[W], b[N];

void counting_sort() {
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= n; ++i) ++cnt[a[i]]; //计数
  for (int i = 1; i <= w; ++i) cnt[i] += cnt[i - 1]; 
  for (int i = n; i >= 1; --i) b[cnt[a[i]]--] = a[i];
}