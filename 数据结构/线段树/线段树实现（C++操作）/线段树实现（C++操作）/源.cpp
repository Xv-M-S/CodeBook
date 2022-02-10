#include<iostream>
#include<vector>
using namespace std;

/*
�����б�Ŵ�1��n��n���㣬ÿ���㶼����һЩ��Ϣ��
��[L,R]��ʾ�±��L��R����Щ�㡣
�߶������ô����ǣ��Ա��������һЩ������޸Ļ���
ͳ�Ʋ������޸ĺ�ͳ�Ƶĸ��Ӷȶ���O(log2(n)).
*/
//�߶���-����ʵ��
/*
1:�ռ��С
�򵥵ļǷ��� �㹻�Ŀռ� = �����Сn���ı���
ʵ�����㹻�Ŀռ� =  ��n�������䵽�����2��ĳ���η�����������
�����ӣ��������鳤��Ϊ5������Ҫ5�������8��8*2=16.�߶�����
Ҫ16��Ԫ�ء��������Ԫ��Ϊ8����ôҲ��Ҫ16��Ԫ�ء�
*/

//�߶������޸ĵ㣬��ѯ����
class segment_tree {
private:
	vector<int>tree;
	vector<int>datas;
public:
	//�����߶���
	void buildtree(int l,int r,int tag) {
		if (r == l) {
			//��ʱΪҶ�ӽ��
			//tag��ʾλ��,r==l��ʾ��datas�е��±�
			tree[tag] = datas[r];
			return;
		}
		int mid = (r + l) >> 1;
		buildtree(l, mid, 2 * tag + 1);//����������
		buildtree(mid + 1, r, 2 * tag + 2);//����������

		tree[tag] = tree[tag * 2 + 1] + tree[tag * 2 + 2];
	}
	//��������ĺ�--ע�ⲻҪд��
	int serch_sum(int left, int right,int l,int r,int tag) {
		//�����䡾left,right��֮��ĺ�
		//r,lΪtag�����ķ�Χ
		/*
		* ���������䱻��ȫ������Ŀ���������棬ֱ�ӷ�����������ֵ
		*���������������Ӻ�Ŀ�������н�������ô���������
		*������������Ҷ��Ӻ�Ŀ�������н�������ô�����Ҷ���
		*/
		cout << l << " " << r << " " << tag << " " << endl;
		int res = 0;
		if (left <= l && right >= r) {
			//������䱻��ȫ������Ŀ����������
			//ֱ�ӷ��ظ������ֵ
			return tree[tag];
		}
		int mid = (l + r) >> 1;
		//ע��if�е�����
		if (left<=mid)res+=serch_sum(left,right,l, mid, 2 * tag + 1);
		if (right>=mid+1)res+=serch_sum(left,right,mid + 1, r,2 * tag + 2);

		return res;

	}
	//�޸ĵ�
	void change_point(int l, int r, int tag,int index,int val) {
		if (r == l) {
			//�޸��ӽڵ�
			//��ʱҲӦ��l==r==index
			tree[tag] = val;
			return ;
		}
		int mid = (l + r) >> 1;
		if (mid >= index)change_point(l, mid, 2 * tag + 1, index, val);
		else change_point(mid+1, r, 2 * tag + 2, index, val);

		//�޸�Ӱ���˵ĺ�
		tree[tag] = tree[tag * 2 + 1] + tree[tag * 2 + 2];

	}
	//���캯��
	segment_tree(vector<int>& nums) {
		//�㹻�Ŀռ� = �����Сn���ı�
		tree.resize(4 * nums.size());
		datas = nums;
	}
	//��ӡ��
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