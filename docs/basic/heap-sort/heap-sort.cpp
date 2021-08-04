void sift_down(int arr[], int start, int end) {
  // 建立父结点指标和子结点指标
  int dad = start;
  int son = dad * 2 + 1;
  while (son <= end) {  // 子结点指标在范围内才做比较
    if (son + 1 <= end &&
        arr[son] < arr[son + 1])  // 先比较两个子结点大小，选择最大的
      son++;
    if (arr[dad] >=
        arr[son])  // 如果父结点比子结点大，代表调整完毕，直接跳出函数
      return;
    else {  // 否则交换父子内容，子结点再和孙结点比较
      swap(arr[dad], arr[son]);
      dad = son;
      son = dad * 2 + 1;
    }
  }
}

void heap_sort(int arr[], int len) {
  // 从最后一个节点的父节点开始sift down以完成堆化(heapify)
  for (int i = (len - 1 - 1) / 2; i >= 0; i--) sift_down(arr, i, len - 1);
  // 先将第一个元素和已经排好的元素前一位做交换，再重新调整（刚调整的元素之前的元素），直到排序完毕
  for (int i = len - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    sift_down(arr, 0, i - 1);
  }
}