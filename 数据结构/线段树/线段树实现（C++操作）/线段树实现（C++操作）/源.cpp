#include<iostream>
#include<vector>
using namespace std;

/*
假设有编号从1到n的n个点，每个点都存了一些信息，
用[L,R]表示下标从L到R的这些点。
线段树的用处就是，对编号连续的一些点进行修改或者
统计操作，修改和统计的复杂度都是O(log2(n)).
*/
//线段树-数组实现
/*
1:空间大小
简单的记法： 足够的空间 = 数组大小n的四倍。
实际上足够的空间 =  （n向上扩充到最近的2的某个次方）的两倍。
举例子：假设数组长度为5，就需要5先扩充成8，8*2=16.线段树需
要16个元素。如果数组元素为8，那么也需要16个元素。
*/

//线段树，修改点，查询区间
class segment_tree {
private:
	vector<int>tree;
	vector<int>datas;
public:
	//构建线段树
	void buildtree(int l,int r,int tag) {
		if (r == l) {
			//此时为叶子结点
			//tag表示位置,r==l表示在datas中的下标
			tree[tag] = datas[r];
			return;
		}
		int mid = (r + l) >> 1;
		buildtree(l, mid, 2 * tag + 1);//建立左子树
		buildtree(mid + 1, r, 2 * tag + 2);//建立右子树

		tree[tag] = tree[tag * 2 + 1] + tree[tag * 2 + 2];
	}
	//查找区间的和--注意不要写错
	int serch_sum(int left, int right,int l,int r,int tag) {
		//求区间【left,right】之间的和
		//r,l为tag所处的范围
		/*
		* 如果这个区间被完全包括在目标区间里面，直接返回这个区间的值
		*如果这个区间的左儿子和目标区间有交集，那么搜索左儿子
		*如果这个区间的右儿子和目标区间有交集，那么搜索右儿子
		*/
		cout << l << " " << r << " " << tag << " " << endl;
		int res = 0;
		if (left <= l && right >= r) {
			//这个区间被完全包括在目标区间里面
			//直接返回该区间的值
			return tree[tag];
		}
		int mid = (l + r) >> 1;
		//注意if中的条件
		if (left<=mid)res+=serch_sum(left,right,l, mid, 2 * tag + 1);
		if (right>=mid+1)res+=serch_sum(left,right,mid + 1, r,2 * tag + 2);

		return res;

	}
	//修改点
	void change_point(int l, int r, int tag,int index,int val) {
		if (r == l) {
			//修改子节点
			//此时也应有l==r==index
			tree[tag] = val;
			return ;
		}
		int mid = (l + r) >> 1;
		if (mid >= index)change_point(l, mid, 2 * tag + 1, index, val);
		else change_point(mid+1, r, 2 * tag + 2, index, val);

		//修改影响了的和
		tree[tag] = tree[tag * 2 + 1] + tree[tag * 2 + 2];

	}
	//构造函数
	segment_tree(vector<int>& nums) {
		//足够的空间 = 数组大小n的四倍
		tree.resize(4 * nums.size());
		datas = nums;
	}
	//打印树
	void print() {
		for (int i = 0; i < tree.size(); i++) {
			cout << tree[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	vector<int>nums = { 9,-8 };
	segment_tree A(nums);
	A.buildtree(0, 1, 0);
	A.print();
	A.change_point(0, 1, 0, 0, 3);
	A.print();
	cout<<endl<<A.serch_sum(1, 1, 0, 1, 0);
	return 0;
}