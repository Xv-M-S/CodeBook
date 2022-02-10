# 一道Hard类型的题目：【双周赛赛题】

## 题目描述：

![image-20210418095404080](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20210418095404080.png)

## 我的分析：

1. 这道题如果按照题目的要求按部就班的做的话铁定超时
2. 数学思维：

![img](file:///C:\Users\西安交通大学2193613091sxm\Documents\Tencent Files\1205507925\Image\C2C\1EB7FD3034E01105C075AFE41EB4358D.jpg)

​	3.这里的运算需要用到阶乘，并且可能用到的还非常的大，求大数阶乘可以用动态规划

​	4.这里还需要处理的一个问题式大整数的加法，乘法相关的取余问题

## 大佬代码，可以看懂一点

```C++
#define LL long long
const LL MOD = 1e9 + 7;
const int MAXN = 3050;
int cnt[30];
LL comb[MAXN][MAXN];



class Solution {
public:
    void init(int n){
        comb[0][0] = 1;
        for (int i = 1; i <= n; i++){
            comb[i][0] = comb[i][i] = 1;
            for (int j = 1; j < i; j++) comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }
    LL Comb(int n, int m){
        if (n == 0) return 1LL;
        if (m == 0) return 1LL;
        if (m > n) return 1LL;
        return comb[n][m];
    }
    int makeStringSorted(string S) {
        int n = S.length();
        init(n);
        LL ans = 0;
        memset(cnt, 0, sizeof(cnt));
                
        for (int i = n - 1; i >= 0; i--){
            int C = S[i] - 'a';
            cnt[C] += 1;
            
            for (int c = C - 1; c >= 0; c--){
                if (cnt[c] == 0) continue;
                cnt[c] -= 1;
                int left = n - i - 1; LL cur = 1;
                for (int k = 0; k < 26; k++){
                    cur = cur * Comb(left, cnt[k]) % MOD;
                    left -= cnt[k];
                }
                cnt[c] += 1;
                ans = (ans + cur) % MOD;
            }
        }
        
        return ans;
    }
};
```



