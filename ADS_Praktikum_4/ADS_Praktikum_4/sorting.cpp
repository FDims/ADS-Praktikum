#include "sorting.h"



namespace sorting {

	//************
	// QuickSort *
	//************      
	void QuickSort(vector<int>& arr, int left, int right)
	{
		if (left < right) {
			int q = Partition(arr, left, right);//Pivot
			QuickSort(arr, left, q - 1);
			QuickSort(arr, q + 1, right);
		}
	}
	int Partition(vector<int>& arr, int p, int r) {
		int x = arr[r];
		int i = p - 1;
		for (int j = p; j < r; j++) {
			if (arr[j] <= x) {
				i++;
				swap(arr[j], arr[i]);
			}
		}
		swap(arr[i + 1], arr[r]);

		return i + 1;
	}

	void InsertionSort(vector<int>& arr)
	{
		for (int i = 1; i < arr.size(); i++) {
			int tmp = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j] > tmp) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = tmp;
		}
	}
	int median(vector<int>& a, int left, int right) {
		int center = (left + right) / 2;
		if (a[center] < a[left])
			swap(a[left], a[center]);
		if (a[right], a[left])
			swap(a[left], a[right]);
		if (a[right] < a[center])
			swap(a[center], a[right]);
		swap(a[center], a[right]);
		return center;
	}
	void HybridQuickSort(vector<int>& arr, int left, int right)
	{
		while(left < right) {
			if ((right - left) + 1 < 10	) {
				InsertionSort(arr);
				break;
			}
			else {
				int q = median(arr, left, right);
				if (q - left < right - q) {
					HybridQuickSort(arr, left, q - 1);
					left = q + 1;
				}
				else {
					HybridQuickSort(arr, q + 1, right);
					right = q - 1;
				}
			}
			
		}
	}

	//************
	// MergeSort *
	//************
	void Merge(vector<int>& a, vector<int>& b, int low, int pivot, int high)
	{
		int leftEnd = pivot - 1, tmpPos = low, n = high - low + 1;
		int leftPos = low, rightPos = pivot, rightEnd = high;
		while (leftPos <= leftEnd && rightPos <= rightEnd) {
			if (a[leftPos] <= a[rightPos]) {
				b[tmpPos] = a[leftPos];
				leftPos++;
			}
			else {
				b[tmpPos] = a[rightPos];
				rightPos++;
			}
			tmpPos++;
		}
		while (leftPos <= leftEnd) {
			b[tmpPos] = a[leftPos];
			tmpPos++;
			leftPos++;
		}
		while (rightPos <= rightEnd) {
			b[tmpPos] = a[rightPos];
			rightPos++;
			tmpPos++;
		}
		int i = 0;
		while (i < n) {
			a[rightEnd] = b[rightEnd];
			rightEnd--;
			i++;
		}
	}


	void MergeSort(vector<int>& a, vector<int>& b, int low, int high)
	{
		if (low < high) {
			size_t m = size_t(floor((low+high)/2));
			MergeSort(a, b, low, m);
			MergeSort(a, b, m + 1, high);
			Merge(a, b, low, m + 1, high);
		}
	}

	void natMerge(vector<int>& a, vector<int>& b, int left, int middle, int right)
	{
		int leftEnd = middle - 1, tmpPos = left, n = right - left + 1;
		int leftPos = left, rightPos = middle, rightEnd = right;
		while (leftPos <= leftEnd && rightPos <= rightEnd) {
			if (a[leftPos] <= a[rightPos]) {
				b[tmpPos] = a[leftPos];
				leftPos++;
			}
			else {
				b[tmpPos] = a[rightPos];
				rightPos++;
			}
			tmpPos++;
		}
		while (leftPos <= leftEnd) {
			b[tmpPos] = a[leftPos];
			tmpPos++;
			leftPos++;
		}
		while (rightPos <= rightEnd) {
			b[tmpPos] = a[rightPos];
			rightPos++;
			tmpPos++;
		}
		int i = 0;
		while (i < n) {
			a[rightEnd] = b[rightEnd];
			rightEnd--;
			i++;
		}
	}

	void natMergeSort(vector<int>& a, vector<int>& b)
	{
		int run = 0, rest = 0;
		vector<int> end(a.size() + 1);
		for (int i = 1; i <= a.size(); i++) {
			if (i == a.size()) {
				run++;
				end[run] = i;
			}
			else if (a[i] < a[i - 1]) {
				run++;
				end[run] = i;
			}
		}
		while (run > 1) {
			int newrun = 0;
			for (int i = 0; i < run; i += 2) {
				natMerge(a, b, end[i], end[i + 1], end[i + 2] - 1);
				end[newrun] = end[i];
				newrun++;
			}
			end[newrun] = end[run];
			run = newrun;
			
		}

	}


	//************
	// Heapsort  *
	//************
	void heapify(vector<int> &a, int n, int i)
	{
		int child = i;
		int tmp = a[i];
		for (tmp = a[i]; leftChild(i) < n; i = child) {
			child = leftChild(i);
			if (child != n - 1 && a[child] < a[child + 1]) {
				child++;
			}
			if (tmp < a[child]) {
				a[i] = a[child];
			}
			else
				break;
		}
		a[i] = tmp;
	}
	int leftChild(int const i) {
		return 2 * i + 1;
	}

	void HeapSort(vector<int> &a, int n) 
	{
		for (int i = a.size() / 2; i >= 0; i--) {
			heapify(a, a.size(), i);
		}
		for (int i = a.size() - 1; i > 0; i--) {
			swap(a[0], a[i]);
			heapify(a, i, 0);
		}
	}

	//************
	// Shellsort *
	//************
	void ShellSort_2n(vector<int> &a, int n)
	{
		int gap = pow(2, (int)(log(n) / log(2))) - 1, tmp, j;
		for (gap; gap > 0; gap /= 2) {
			for (int i = gap; i < n; i++) {
				tmp = a[i];
				for (j = i; j >= gap; j -= gap) {
					if (tmp < a[j - gap])
						a[j] = a[j - gap];
					else
						break;
				}
				a[j] = tmp;
			}
		}
	}


	void ShellSort_3n(vector<int>& a, int n)
	{
		int folge = 1, gap = 1, tmp, j;
		while (folge < n) {
			gap = folge;
			folge = (3 * folge) + 1;
		}
		for (gap; gap > 0; gap /= 3) {
			for (int i = gap; i < n; i++) {
				tmp = a[i];
				for (j = i; j >= gap; j -= gap) {
					if (tmp < a[j - gap])
						a[j] = a[j - gap];
					else
						break;
				}
				a[j] = tmp;
			}
		}
	}


  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }


}





