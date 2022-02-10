#include<vector>
#include<iostream>
using namespace std;


class Heap {
private:
	vector<int>heap;
public:
	//插入一个数据
	//将数据插入到最末尾，然后一步步的上浮
	void insert(int data) {
		heap.push_back(data);
		swim(heap.size() - 1);
	}
	//上浮
	void swim(int pos) {
		while (pos > 0 && heap[(pos-1) / 2] < heap[pos]) {
			swap(heap[(pos-1) / 2], heap[pos]);
			pos = (pos - 1) / 2;
		}
	}
	//删除最大值
	//将最后一个数移动到开头，然后下沉
	void pop() {
		if (heap.size() == 0)return;
		swap(heap[heap.size() - 1], heap[0]);
		heap.pop_back();
		sink(0);
	}
	void sink(int pos) {
		int n = heap.size();
		//大顶堆，选择子结点中较小的进行交换
		while (2 * pos + 1 < n) {
			int temp = 2 * pos + 1;
			if (2 * pos + 2 < n && heap[2 * pos + 1] < heap[2 * pos + 2])
				temp = 2 * pos + 2;
			if (heap[temp] > heap[pos])
				swap(heap[temp], heap[pos]);
			else break;
			pos = temp;
		}
		/*
		while (2 * pos + 1 < n) {
			if (heap[2 * pos + 1] > heap[pos])
				swap(heap[2 * pos + 1], heap[pos]);
			else if (2 * pos + 2 < n) {
				if (heap[2 * pos + 2] > heap[pos])
					swap(heap[2 * pos + 2], heap[pos]);
				else break;
			}
		}
		*/
	}
	void print() {
		for (int i = 0; i < heap.size(); i++)
			cout << heap[i] << endl;
	}
	void print1() {
		while (!heap.empty()) {
			cout << heap[0] << " ";
			pop();
		}
		cout << endl;
	}
};

int main() {
	vector<int>datas = {2,7,3,1,25,17,19,36,100};
	Heap A;
	for (int i = 0; i < datas.size(); i++) {
		A.insert(datas[i]);
	}
	A.print();
	A.print1();
	
}