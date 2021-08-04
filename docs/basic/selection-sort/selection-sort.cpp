void selection_sort(int* a, int n) {
  for (int i = 1; i < n; ++i) {
    int ith = i;//初始化ith变量，这个变量是编号
    for (int j = i + 1; j <= n; ++j) {//找一个更小的和他交换，找不到那么就是他了
      if (a[j] < a[ith]) {
        ith = j;
      }
    }
    int t = a[i];//交换操作
    a[i] = a[ith];
    a[ith] = t;
  }
}