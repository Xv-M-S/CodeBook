# C++STL:代码简洁之道一

## 1：C++-STL中lower_bound与upper_bound的用法

### 函数lower_bound()

- **头文件：#include<algorithm>**
- **函数模板： 如 二分查找：binary_search()**
- **函数功能： 函数lower_bound()在first和last中的前闭后开区间进行二分查找，返回大于或等于val的第一个元素位置。如果所有元素都小于val，则返回last的位置**

### 函数upper_bound()

- **头文件：#include<algorithm>**
- **函数模板： 如二分查找binary_search()**
- **函数功能：函数upper_bound()返回的在前闭后开区间查找的关键字的上界，返回大于val的第一个元素位置**

### 总结：

-  **lower_bound(val):返回容器中第一个值【大于或等于】val的元素的iterator位置。**
- **upper_bound(val): 返回容器中第一个值【大于】val的元素的iterator位置。**

![image-20210910113648424](C:\Users\西安交通大学2193613091sxm\AppData\Roaming\Typora\typora-user-images\image-20210910113648424.png)

