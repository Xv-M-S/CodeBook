#include <iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<limits.h>
using namespace std;

class Solution {
    //哈希映射
    unordered_map<int, string>map1;
    unordered_map<string, int>map2;
    vector<int>datas;
    //dp动态规划
    vector<vector<int>>dp;//表示长度为i,递增长度为len的最后一个字符串的值
    vector<int>min_dp;
    

private:
    //字符串比较函数
    int cmp(string& s1, string& s2) {
        int n1 = s1.size(), n2 = s2.size();
        int i = 0, j = 0;
        while (i < n1 && j < n2) {
            if (s1[i] == s2[j]) {
                ++i;
                ++j;
            }
            else {
                if (i == n1 && j == n2)return 0;
                else if (i == n1)return -1;
                else if (j == n2)return 1;
                else if (s1[i] > s2[j])return 1;
                else if (s1[i] < s2[j])return -1;
            }
        }
    }
    //适用于sort的字符串比较函数
    //比较函数中的等于好切记摸棱两可
    bool static cmp1(const string& s1,const string& s2) {
        int n1 = s1.size(), n2 = s2.size();
        int i = 0, j = 0;
        while (i < n1 && j < n2) {
            if (s1[i] == s2[j]) {
                ++i;
                ++j;
            }
            else {
                if (s1[i] < s2[j])return true;
                else return false;
            }
        }
        if (i == n1&&j!=n2)return true;
        else return false;
    }

public:
    string main_func(vector<string>strs) {
        vector<string>temp = strs;//不知此处编译是否有问题
        sort(temp.begin(), temp.end(), cmp1);
        //验证2：
        cout << "验证2：" << endl;
        for (auto& tp : temp)cout << tp << endl;


        for (int i = 0; i < (int)temp.size(); i++) {
            map1[i] = temp[i];
            map2[temp[i]] = i;
        }

        //验证三：
        cout << "验证三：" << endl;
        for (auto&v : map1) {
            cout << v.first<< ":" << v.second << endl;
        }
        for (auto&v: map2) {
            cout << v.first << ":" << v.second << endl;
        }

        //将字符串转换成数字-以减少空间消耗
        for (auto& str : strs) {
            datas.push_back(map2[str]);
        }
        cout << datas.size() << endl;

        //动态规划初始化
        int n = strs.size();
        //dp.resize(n);
        min_dp.push_back(datas[0]);
        //dp[0].push_back(datas[0]);
        //动态规划开始
        for (int i = 1; i < n; i++) {
            //首先更新min_dp-用于求最长子序列的长度
            if (datas[i] > min_dp.back())min_dp.push_back(datas[i]);
            else {
                int begin = 0, end = min_dp.size() - 1, tag = -1, mid;
                while (begin <= end) {
                    mid = (begin + end) >> 1;
                    if (min_dp[mid] >= datas[i]) {
                        tag = mid;
                        end = mid - 1;
                    }
                    else begin = mid + 1;
                }
                cout << " TAG:" << tag << endl;
                min_dp[tag] = datas[i];
               
                
            }
            dp.push_back(min_dp);
            /*
            //其次对dp
            for (int j = 0; j < i; j++) {
                if (dp[i - 1][j] != INT_MAX)dp[i].push_back(min(dp[i - 1][j], datas[i]));
                else if (datas[i] > dp[i - 1][j - 1])dp[i].push_back(datas[i]);
                else dp[i].push_back(INT_MAX);
            }
            if (datas[i] > dp[i].back())dp[i].push_back(datas[i]);
            else dp[i].push_back(INT_MAX);
            */
        }
        cout << "OK";
        //验证4：
        for (int i = 0; i < dp.size(); i++) {


            for (int j = 0; j < dp[i].size(); j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }

            //求结果
            int len = min_dp.size()-1;
            vector<int>ans;
            int target = min_dp.back();
            ans.push_back(target);
            for (int i = n - 1; i >= 0 && len >= 0; i--) {
                if (datas[i] == target) {
                    cout << "i:" << i << endl;
                    cout << "len:" << len << endl;
                    if (len > 0 && i > 0) {
                        target = dp[i - 1][len - 1];
                        ans.push_back(target);
                    }
    
                    --len;
                }
            }
            
            reverse(ans.begin(), ans.end());
            string res;
            for (auto& data : ans) {
                res += map1[data];
            }
            return res;
        


    }

};
int main()
{
    //处理输入
    string input;
    cin >> input;
    //将输入分隔成字符串
    vector<string>strs;
    string temp;
    int n = input.size(), i = 0;
    while (i < n) {
        temp.clear();
        temp.push_back(input[i++]);
        while (i < n && input[i] <= 'z' && input[i] >= 'a') {
            temp.push_back(input[i++]);
        }
        strs.push_back(temp);
    }
    //验证1
    for (auto& tp : strs)cout << tp << endl;
    //建立实例-返回结果
    Solution A;
    cout << A.main_func(strs);
    // 请在此输入您的代码
    return 0;
}