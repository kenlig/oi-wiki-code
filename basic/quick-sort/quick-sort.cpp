struct Range {
  int start, end;
  Range(int s = 0, int e = 0) { start = s, end = e; }
};

template <typename T>//模板
void quick_sort(T arr[], const int len) {
  if (len <= 0) return;
  Range r[len];
  int p = 0;
  r[p++] = Range(0, len - 1);
  while (p) {
    Range range = r[--p];
    if (range.start >= range.end) continue;
    T mid = arr[range.end];//分治
    int left = range.start, right = range.end - 1;
    while (left < right) {
      while (arr[left] < mid && left < right) left++;//移动left和right
      while (arr[right] >= mid && left < right) right--;
      std::swap(arr[left], arr[right]);//排序交换
    }
    if (arr[left] >= arr[range.end])
      std::swap(arr[left], arr[range.end]);
    else
      left++;
    r[p++] = Range(range.start, left - 1);
    r[p++] = Range(left + 1, range.end);//修改起始点
  }
}