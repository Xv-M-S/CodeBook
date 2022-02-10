# 第十二届蓝桥杯软件组省赛A组

## 试题A：卡片

![image-20220118124317465](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220118124317465.png)

**这道题比较简单：暴力模拟**

**答案：3181**

```C++
#include <iostream>
using namespace std;

//暴力模拟
int nums[10]={0};

bool formNum(int num){
  while(num>0){
    if(nums[num%10])--nums[num%10];
    else return false;
    num/=10;
  }
  return true;
}

int main()
{
  for(int i=0;i<10;i++)nums[i]=2021;

  int num=1;
  while(true){
    if(formNum(num))++num;
    else{
      cout<<(num-1);
      break;
    }
  }

  // 请在此输入您的代码
  return 0;
}
```

## 试题B：直线

![image-20220118162014713](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220118162014713.png)

### **方法1：点斜式处理（double）**

- **点斜式：y=ax+b;易错点：斜率无穷大或为0的情况**
- **暴力模拟，枚举所有情况，统计（a,b）系数对的数量**
- **问题：double类型数据的比较问题**

1. **关于double的比较问题，主要体现在set或unordered_set模板的比较问题：https://blog.csdn.net/aggie4628/article/details/104147211**

   **自定义类的set比较**

   ```C++
   //set实现底层是红黑树
   //其实都是三步走：
        1.自定义对象；
        2.重载operator(<和==)
   //这里的重载认为当两个double数值的数相减小于一个很小的数时，就认为这两个数相等
   class DOUBLE{
   private:
   	double x,y;
   public:
   	DOUBLE(double xt,double yt){
   		this->x=xt;
   		this->y=yt;
   	}
   	bool operator<(const DOUBLE &p) const {
           if (abs(x-p.x)<=eps) return y<p.y;
           return x<p.x;
       }
   	bool operator==(const DOUBLE&tp)const{
   		bool bx=abs(tp.x-x)<=eps;
   		bool by=abs(tp.y-y)<=eps;
   		return bx&&by;
   	}
   }; 
   ```

2. **double的内置比较：对于C++来说，double是可以比较的，但是由于不同的运算方法等到的运算结果会有不同程度的精度损失，可能会使得原本相等的数而不相等；这就要求在使用double的时候规定好运算方式**

   - **将int转换为double通过将int类型的数据乘以1.0**
   - **int类型的数据不和double类型的数据进行运算；**
   - **int类型的数和int类型的数运算；double类型的数只和double类型的数运算**

   ```C++
   #include <bits/stdc++.h>
   using namespace std;
   
   vector<pair<int,int>> p;
   int ans = 0;
   int N =20, M = 21;
   set<pair<double,double>>s;	//set的作用是去重
   //生成所有点到数组
   void getPoint(){
   	for(int i =0;i<N;i++)
   		for(int j=0;j<M;j++) p.push_back(make_pair(i,j));
   }
   //将两点确定的直线的斜率和截距放进set里
   void countLine(int i, int j){
   	int x1 = p[i].first , y1 = p[i].second;
   	int x2 = p[j].first , y2 = p[j].second;
   	if(x1 == x2 || y1 == y2) return;
   	double fm = (x2 - x1) * 1.0;
   	double k = (y2-y1)*1.0/ (x2-x1);
   	double b = (y1*x2 - x1*y2) * 1.0 / fm;
   	s.insert(make_pair(k,b));
   }
   void solve(){
   	getPoint();
   	int n = p.size();
   	//每个点，和这个点后面的所有点做一次计算
   	for(int i = 0;i<n;i++)
   		for(int j = i+1;j<n;j++)
               countLine(i,j);
   	ans = s.size() + N + M;	//结果就是set的大小，加上和x轴y轴平行的直线的数量
   }
   int main(){
   	solve();
   	cout<< ans << endl;
       return 0;
   }
   
   ```

### 方法2：两点式(求最大公约数)

- **ax+by+c=0**
- ![image-20220118182402100](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220118182402100.png)
- **求a,b,c的最大公约数t以避免对double类型数据的处理**

```C++
#include<iostream>
#include<cmath>
#include<set>
using namespace std;
struct node{//点
    int x,y;
}p[1000];
struct line{//直线
    int a,b,c;//直线一般方程的系数
    bool operator<(const line &p) const {
        if (a == p.a) return b == p.b ? c < p.c : b < p.b;
        return a < p.a;
    }
    bool operator==(const line &p) const {
        return a == p.a && b == p.b && c == p.c;
    }
};
int cnt;
set<line> se;
int gcd(int a,int b){//妙啊
    return b==0?a:gcd(b,a%b);
}
int gcdd(int a,int b,int c){
    return gcd(gcd(a,b),gcd(b,c));
}
int main()
{
    int n=20,m=21;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            p[++cnt]={i,j};
    for(int i=1;i<=cnt;i++){
        for(int j=i+1;j<=cnt;j++){
            int a=p[i].y-p[j].y;
            int b=p[j].x-p[i].x;
            int c=p[i].y * (p[i].x-p[j].x)- p[i].x *(p[i].y-p[j].y);
            int t=gcdd(fabs(a),fabs(b),fabs(c));
            se.insert({a/t,b/t,c/t});
        }

    }
    cout<<se.size();
    return 0;
}

```

### 建议：

```c++
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define eps 1e-8          //自己先定义精度

class DOUBLE{
private:
	double x,y;
public:
	DOUBLE(double xt,double yt){
		this->x=xt;
		this->y=yt;
	}
	
	
	bool operator<(const DOUBLE &p) const {
        if (abs(x-p.x)<=eps) return y<p.y;
        return x<p.x;
    }
    
	bool operator==(const DOUBLE&tp)const{
		bool bx=abs(tp.x-x)<=eps;
		bool by=abs(tp.y-y)<=eps;
		return bx&&by;
	}
}; 
int main(){
	//数据输入 
	vector<pair<int,int>>datas;
	for(int i=0;i<20;i++){
		for(int j=0;j<21;j++){
			datas.push_back({i,j});
		}
	}

	
	//建立一个集合
	int cut=datas.size(); 
	set<DOUBLE>res;
	set<pair<double,double>>s;
	for(int i=0;i<cut;i++){
		for(int j=i+1;j<cut;j++){
			int x1=datas[i].first,y1=datas[i].second;
			int x2=datas[j].first,y2=datas[j].second;
			if(x1==x2||y1==y2)continue;
			double dy=(y2-y1)*1.0;//int转化为double:通过乘以1.0 
			double dx=(x2-x1)*1.0;
			//DOUBLE tp=DOUBLE(dy/dx,y1*1.0-x1*dy/dx);
			DOUBLE tp=DOUBLE(dy/dx,(y1*x2-x1*y2)*1.0/dx);
			res.insert(tp);
			s.insert({dy/dx,(y1*x2-x1*y2)*1.0/dx});
		}
	} 
	 
	cout<<res.size()+41<<endl;
	cout<<s.size()+41;
	return 0;
}
```

- 能不用STL就不用STL
- 命名越简洁越好
- 想办法用控件换时间

**代码链接：**

https://blog.csdn.net/Supreme7/article/details/115902501?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522164249434816780255241591%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=164249434816780255241591&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-25-115902501.first_rank_v2_pc_rank_v29&utm_term=%E8%93%9D%E6%A1%A5%E6%9D%AF+%E7%9B%B4%E7%BA%BF&spm=1018.2226.3001.4187

## 试题C：货物摆放

![image-20220125121726415](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220125121726415.png)

**题目分析：题目的本质-将n分解成L、W、H三个数相乘的形式，找符合条件的（L,W,H）三元组的形式。**

### 暴力解法（超时）：

**原因分析：数字n=2021041820210418太大；一般的计算机每秒的运行速度为几亿次每秒，从1遍历到n都需要 大约2021041多秒，故需要在暴力的基础上优化。**

```C++
#include<iostream>
using namespace std;

typedef long long int ll;
int main(){
	//2021041820210418 
	ll n=202,m=0,res=0;
	for(int i=1;i<=n;i++){
		if(n%i==0){
			m=n/i;
		}else continue;
		
		for(int j=1;j<=n;j++){
			if(m%j==0){
				++res;
			}else continue;
		}
	} 
	cout<<res;
	return 0;
} 
```

### （优化）暴力解法：

**优化1：L,W,H一定是n的因式；找出数n的所有因式，在因式中暴力找出所有解。**

**优化2：求所有因式的优化**

```C++
#include<iostream>
using namespace std;

typedef long long int ll;

int main(){
	ll n=2021041820210418;
	ll childs[200];
	ll num=0;
	cout<<"ok"<<endl;
	//此处求n的所有因式要优化 
	/*
	for(ll i=1;i<=n;i++){
		if(n%i==0)childs[num++]=i;
	}
	*/ 
	for(ll i=1;i<=n/i;i++){
		if(n%i==0){
			childs[num++]=i;
			if(i*i!=n){
				childs[num++]=n/i;
			}
		}
	} 
	cout<<num<<endl;
	ll res=0;
	for(ll i=0;i<num;i++){
		for(ll j=0;j<num;j++){
			if(n%(childs[i]*childs[j])==0)
			++res;
		}
	}
	cout<<res;
}

```

## 试题D：路径

![image-20220126185127509](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220126185127509.png)

**思路：构建图-用最短路径算法求最短路径-数学知识：求最小公倍数+优先队列的自定义排序**

```C++
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

/*
	1.构图，邻接矩阵vector<vector<int>>edges; 
	2. 运用最短路径算法求最短路径 
*/ 
int getPathLen(int m,int n){
	//求a,b的最小公倍数
	//32 12
	//12 8
	//8 4
	//4 0
	int a=m,b=n,t=0;
	while(b!=0){
		t=a%b;
		a=b;
		b=t;
		//cout<<a<<" "<<b<<endl;
	} 
	return m*n/a;
}
//优先队列自定义排序 
struct cmp
{
    bool operator()(const pair<int, int>& a, const pair<int, int>& b)
    {
        //优先队列的排序与普通排序相反
        //此为从小到大排序
        return a.second > b.second;
    }
};
int main(){
	vector<vector<pair<int,int>>>edges(2021+1);
	//cout<<getPathLen(32,12);
	//构图
	for(int i=1;i<=2021;i++){
		for(int j=1;j<=21;j++){
			if(i+j>2021)continue;
			int len=getPathLen(i,i+j);
			edges[i].push_back({i+j,len});
			edges[i+j].push_back({i,len});
		}
	} 
	//用最短路径算法求最短路径
	vector<bool>visited(2022,false);//表示是否访问过
	vector<int>dist(2022,INT_MAX);//表示点1到其他点j的距离
	priority_queue<pair<int,int>,vector<pair<int,int>>,cmp>que;//优先队列,距离最端优先级越高
	
	//初始化
	visited[1]=true;
	dist[1]=0;
	for(int i=0;i<edges[1].size();i++){
		que.push(edges[1][i]);
	}
	
	
	while(!que.empty()){
		pair<int,int>temp=que.top();
		que.pop();
		int node=temp.first;
		int plen=temp.second;
		if(visited[node])continue;
		
		dist[node]=plen;
		visited[node]=true;
		
		for(int i=0;i<edges[node].size();i++){
			int no=edges[node][i].first;
			int llen=edges[node][i].second;
			if(visited[no])continue;
			if(plen+llen<dist[no]){
				dist[no]=plen+llen;
				que.push({no,dist[no]});
			}
		}
	}
	
	cout<<dist[2021];
	return 0;
	
} 
```

## 试题E：回路计数（回溯算法+记忆化）

![image-20220204141355953](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220204141355953.png)

### 题目分析：

**在构建图的基础上寻找哈密顿路；但是由于编号较大，会超时，所以通过记忆化来压缩搜索的时间。**

#### **记忆化搜索是回溯的高阶状态**

**写好写对记忆化搜索要细心的谋划回溯函数；多多训练，掌握一定的技巧**

```C++

```

## 试题F：砝码称重

![image-20220204141657537](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220204141657537.png)

![image-20220204141709469](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220204141709469.png)

![image-20220204141718336](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220204141718336.png)

**对于50%的评测用例，可以用暴力求解；**

```C++
#include<iostream>
#include<bits/stdc++.h> 
using namespace std;

int n;
unordered_set<int>myset;//答案集合
int d[110];

void getWeight(int td[],int tn){
	int sum=0,ts=0;
	for(int i=0;i<tn;i++)sum+=td[i];
	
	for(int i=0;i<(1<<tn);i++){
		ts=0;
		for(int j=0;j<tn;j++){
			if(1&(i>>j))ts+=td[j];
		}
		myset.insert(abs(2*ts-sum));
	} 
}

//先打暴力，处理50%的用例 
int main(){
	//输入 
	cin>>n;//输入的数的个数 
	for(int i=0;i<n;i++)cin>>d[i];//输入各个数 
	
	int td[100];
	int tn=0;
	for(int i=0;i<(1<<n);i++){
		tn=0;
		for(int j=0;j<n;j++){
			if((i>>j)&1){
				td[tn++]=d[j];
				
				//cout<<d[j]<<" ";
			}
		}
		
		//cout<<endl;
		getWeight(td,tn);
	}
	 
	cout<<myset.size()-1;
	
	return 0; 
}
```

**对于N>15的情况，暴力求解会超时。需要转换思路，用一下逆向的思维，考虑到N《=100000；通过动态规划来解这道题。**

```C++
#include <bits/stdc++.h>
using namespace std;
const long long inf = 0x7fffffffffffffff;
bool dp[106][200006];
int a[106];
int main()
{
    int i,j,n,sum = 0; cin>>n;
   for(i = 1;i <= n;i++){
      cin>>a[i];
      sum+= a[i];
   }

   for(i = 1;i <= n;i++){
       for(j = 1;j <= sum;j++){
           dp[i][j] = dp[i-1][j];
           if(!dp[i][j]){
               if(j == a[i]) dp[i][j] = 1; 
                //判定的值与当前选择的砝码相等
               if(dp[i-1][j + a[i]])  dp[i][j] = 1;
      //检查当前i砝码与上一个状态（之前组合出的值）放在不同侧，是否可以组成j。
               if(dp[i-1][abs(j-a[i])]) dp[i][j] = 1;
      //检查当前i砝码与上一个状态（之前组合出的值）放在同一侧，是否可以组成j。
           }
       }
   }

   long long ans = 0;
    for(j = 1;j <= sum;j++) if(dp[n][j]) ans++;
    cout<<ans;
    return 0;
}


```

**万物皆可动态规划及记忆化搜索**

## 试题G：异或数列（博弈）

**![image-20220209160840654](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220209160840654.png)**

![image-20220209160859331](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220209160859331.png)

**分析:博弈点为最高位。**

- 异或的性质：同为1，异为0
- **当最高位为1的个数为奇数且n为偶数时，先手赢；**
- **同时，当最高位为1的个数为奇数且n为奇数时，后手赢；**
- **由此推之，当最高位为1的个数为偶数时，看次高位，次高位为1个数是偶数，看次次高位……**

**找到博弈点，由简单博弈得出一般结论，再推广一般结论**

```C++
#include<bits/stdc++.h>
using namespace std;
// A和B初始的数值都是0。
int num[23];
long long a;
void pre(long long a)
{
    int cnt=1;
    while(a){
        if(a&1)num[cnt]++;
        cnt++;
        a>>=1;
    }
}
int main()
{
    int T;
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>T;
    while(T--){
        memset(num,0,sizeof(num));
        int n,sum=0;
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>a;
            pre(a);
            sum^=a;
        }
        if(!sum)puts("0");
        else{
            for(int i=20;i>0;i--)
            if(num[i]==1){puts("1");break;}
            else if(num[i]%2==1){
                if(n%2==1){puts("1");break;}
                else if(n%2==0){puts("-1");break;}
            }
        }
    }
    return 0;
}
```

## 试题H：左孩子右兄弟（树的数据结构+递归）

![image-20220209170638840](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220209170638840.png)

![image-20220209170715811](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220209170715811.png)

**理解左孩子右兄弟的概念，f(u)=子节点的个数+最高的子树的高度**

```C++
#include<bits/stdc++.h>//手残党必备
using namespace std;
int N;int f;vector<int> v[100005];
int height(int node)
{
	int m=0;//初始化
	for(int i=0;i<v[node].size();i++)
		m=max(m,height(v[node][i]));//递归,找最大高度的孩子节点
	return m+v[node].size();//高度+深度
}
int main()
{
	cin>>N;
	for(int i=2;i<=N;i++)
	{
		cin>>f;
		v[f].push_back(i);
	}
	cout<<height(1);//递归
	return 0;
}
```

## 试题I:括号序列

![image-20220209173045112](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20220209173045112.png)

**思路：先求出需要的左括号和右括号的数量，再求用记忆化搜索或者动态规划**

## 试题J：分果果
