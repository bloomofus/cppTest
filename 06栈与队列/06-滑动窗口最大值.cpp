#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // -- 思路
        // 由于需要保存之前的记录的最大值，并且之前的一个窗口里的剩余值都必须保存
        // 那么也就意味着所有的数字都必须按照一定的顺序存储
        // 而且，每次当窗口滑动的时候，都舍弃最前面的值，所以本题的数据结构也必须有删除机制
        // 于是就可以使用优先级的栈结构，数字越大的放上面，并且每个栈数据单元也要储存其索引信息
        if(k==1) return nums;
        struct Node
        {
            int val,idx;
        };
        // 先把前k-1个数字加入栈，剩余的数字一个循环搞定
        vector<Node> data{};
        vector<Node> cache{};
        for(int i=0;i<k-1;++i)
        {
            if(data.size()==0) data.push_back({nums[i],i});
            else
            {
                while(data.size()>0 && data.back().val>nums[i])
                {
                    // 先把所有大于当前数字的节点先放到缓存栈里面
                    // 然后把当前数字节点加入数据栈里面后，再把缓存栈的全部节点加入数据栈
                    Node tmp=data.back();
                    cache.push_back(tmp);
                    data.pop_back();
                }
                data.push_back({nums[i],i});
                while(cache.size()>0)
                {
                    Node tmp=cache.back();
                    data.push_back(tmp);
                    cache.pop_back();
                }
            }
        }
        vector<int> res{};
        for(int i=k-1;i<nums.size();++i)
        {
            // 每轮循环都会把当前数字节点加入数据栈，然后产生一个窗口值，就是数字栈的栈顶
            // 当前的窗口范围是i-k+1->i，超出这个范围的数字需要剔除
            bool isAdd=false;
            while(data.size()>0) // data里面没有数据的场景在一开始就剪纸过了
            {
                Node tmp=data.back();
                if(tmp.idx<i-k+1 ||tmp.idx>i) 
                {
                    data.pop_back();
                    continue;
                }
                else
                {
                    // 当前节点在窗口范围之内
                    // 如果其val大于当前遍历的节点，那么就需要将其加入缓存栈
                    // 反之，就需要直接把当前遍历的节点加入数据栈
                    if(tmp.val>nums[i])
                    {
                        cache.push_back(tmp);
                        data.pop_back();
                    }
                    else
                    {
                        data.push_back({nums[i],i});
                        isAdd=true;
                        break;
                    }
                }

            }
            if(!isAdd) data.push_back({nums[i],i});
            while(cache.size()>0)
            {
                Node tmp=cache.back();
                data.push_back(tmp);
                cache.pop_back();
            }
            res.push_back(data.back().val);
        }
        return res;
    }
};


class Solution2 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // -- 优化思路
        // 每次往数据栈里面添加新的值的时候，因为比该值更小的旧值就完全没有意义
        // 所以在添加之前，直接清空数据栈
        if(k==1) return nums;
        struct Node
        {
            int val,idx;
        };
        vector<Node> data{};
        vector<Node> cache{};
        for(int i=0;i<k-1;++i)
        {
            if(data.size()==0) data.push_back({nums[i],i});
            else
            {
                while(data.size()>0 && data.back().val>nums[i])
                {
                    // 先把所有大于当前数字的节点先放到缓存栈里面
                    // 然后把当前数字节点加入数据栈里面后，再把缓存栈的全部节点加入数据栈
                    Node tmp=data.back();
                    cache.push_back(tmp);
                    data.pop_back();
                }
                while(data.size()>0) data.pop_back();
                data.push_back({nums[i],i});
                
                while(cache.size()>0)
                {
                    Node tmp=cache.back();
                    data.push_back(tmp);
                    cache.pop_back();
                }
            }
        }
        vector<int> res{};
        for(int i=k-1;i<nums.size();++i)
        {
            // 每轮循环都会把当前数字节点加入数据栈，然后产生一个窗口值，就是数字栈的栈顶
            // 当前的窗口范围是i-k+1->i，超出这个范围的数字需要剔除
            bool isAdd=false;
            while(data.size()>0) // data里面没有数据的场景在一开始就剪纸过了
            {
                Node tmp=data.back();
                if(tmp.idx<i-k+1 ||tmp.idx>i) 
                {
                    data.pop_back();
                    continue;
                }
                else
                {
                    // 当前节点在窗口范围之内
                    // 如果其val大于当前遍历的节点，那么就需要将其加入缓存栈
                    // 反之，就需要直接把当前遍历的节点加入数据栈
                    if(tmp.val>nums[i])
                    {
                        cache.push_back(tmp);
                        data.pop_back();
                    }
                    else
                    {
                        while(data.size()>0) data.pop_back();
                        data.push_back({nums[i],i});
                        isAdd=true;
                        break;
                    }
                }

            }
            if(!isAdd) data.push_back({nums[i],i});
            while(cache.size()>0)
            {
                Node tmp=cache.back();
                data.push_back(tmp);
                cache.pop_back();
            }
            res.push_back(data.back().val);
        }
        return res;
    }
};

class Solution3 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // -- 思路3
        // 实际上从头部进行遍历比较太麻烦，还要把数据来回在栈之间倒腾
        // 所以直接从尾部进行遍历更方便，不需要倒腾数据
        // 为了更省空间，在数据结构里面只需要记录idx即可
        vector<int> res{};
        deque<int> q{};
        for(int i=0;i<nums.size();++i)
        {
            while(q.size()>0&&i>=k-1&&q.front()<i-k+1) q.pop_front();
            while(q.size()>0&&nums[q.back()]<=nums[i]) q.pop_back();
            q.push_back(i);
            if(i>=k-1)
            {
                // 在输出每一轮窗口最大值的时候，还需要检查队列头部的索引是否在范围之内：i-k+1->i
                // 就是因为这个原因数据结构采用deque而不是vector
                res.push_back(nums[q.front()]);
            }
        }
        return res;
    }
};