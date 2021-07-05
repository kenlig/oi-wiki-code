const int N = 100010;

int n, w, a[N];
vector<int> bucket[N]; //数组

void insertion_sort(vector<int>& A) { //插入排序
  for (int i = 1; i < A.size(); ++i) {
    int key = A[i];
    int j = i - 1;
    while (j >= 0 && A[j] > key) {
      A[j + 1] = A[j];
      --j;
    }
    A[j + 1] = key;
  }
}

void bucket_sort() {//桶排序
  int bucket_size = w / n + 1;//桶大小
  for (int i = 0; i < n; ++i) {
    bucket[i].clear();//清除
  }
  for (int i = 1; i <= n; ++i) {
    bucket[a[i] / bucket_size].push_back(a[i]);//放到桶里
  }
  int p = 0;
  for (int i = 0; i < n; ++i) {
    insertion_sort(bucket[i]);//把桶排序
    for (int j = 0; j < bucket[i].size(); ++j) {
      a[++p] = bucket[i][j];
    }
  }
}