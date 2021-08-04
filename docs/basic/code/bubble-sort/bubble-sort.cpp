void bubble_sort(int *a, int n) {//第一个参数是数组
  bool flag = true;
  while (flag) {
    flag = false;
    for (int i = 1; i < n; ++i) {
      if (a[i] > a[i + 1]) {//如果前一个比后一个大，就把他往后边冒泡
        flag = true;
        int t = a[i];//swap操作
        a[i] = a[i + 1];
        a[i + 1] = t;
      }
    }
  }
}