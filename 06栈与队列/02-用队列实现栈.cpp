#include <bits/stdc++.h>
using namespace std;

class MyStack {
public:

    queue<int> q0{};
    queue<int> q1{};
    queue<int>* curq=&q0;
    queue<int>* nextCurq=&q1;
    MyStack() {
        
    }
    
    void push(int x) {
        curq->push(x);
    }
    
    int pop() {
        if(curq->empty()) throw runtime_error("Stack is empty");
        while(curq->size()>1)
        {
            nextCurq->push(curq->front());
            curq->pop();
        }
        int res=curq->front();
        curq->pop();
        swap(curq,nextCurq);
        return res;
    }
    
    int top() {
        if(curq->empty()) throw runtime_error("Stack is empty");
        while(curq->size()>1)
        {
            nextCurq->push(curq->front());
            curq->pop();
        }
        int res=curq->front();
        curq->pop();
        nextCurq->push(res);
        swap(curq,nextCurq);
        return res;
    }
    
    bool empty() {
        return curq->empty();
    }
};