#include <bits/stdc++.h>
using namespace std;

class MyQueue {
public:

    stack<int> data_{};
    stack<int> cache_{};

    MyQueue() {

    }
    
    void push(int x) {
        if(data_.empty()==true) data_.push(x);
        else
        {
            while(data_.empty()==false)
            {
                int tmp=data_.top();
                data_.pop();
                cache_.push(tmp);
            }
            data_.push(x);
            while(cache_.empty()==false)
            {
                int tmp=cache_.top();
                cache_.pop();
                data_.push(tmp);
            }
        }
    }
    
    int pop() {
        if(data_.empty()==false)
        {
            int res=data_.top();
            data_.pop();
            return res;
        }
        else return -999;
    }
    
    int peek() {
        return data_.empty()?-999:data_.top();
    }
    
    bool empty() {
        return data_.empty();
    }
};