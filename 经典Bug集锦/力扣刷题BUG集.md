# 力扣刷题BUG集

## unordered_map<pair<int,int>int>报错

![image-20210913101848418](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20210913101848418.png)

![image-20210913101913515](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20210913101913515.png)

### 自定义pair_hash函数

```C++
#include<bits/stdc++.h>
using namespace std;
struct pair_hash {
    inline size_t operator()(const pair<int,int> & p) const {
        return p.first * 100 + p.second;
    }
};
unordered_map<pair<int, int>, bool, pair_hash> pHash;

————————————————
版权声明：本文为CSDN博主「zhb1nk」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/zhaohaibo_/article/details/90340120
```

