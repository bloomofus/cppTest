#include <bits/stdc++.h>
using namespace std;

int main()
{
    // -- 思路
    // 本题相当于在图结构中，找到起始节点到目标节点的最短路径，
    // 最短路径一般使用bfs，如果使用双向bfs，听着高级，但是处理很麻烦
    // 为什么使用邻接链表，在遍历一个节点的扇出节点的时候很方便
    // bfs有：1，队列，直到队列为空，2，层序轮次循环控制的遍历
    // 这里选择的是方案2，能够知道最短路径节点数

    // -- 输入数据
    int n = 0;
    cin >> n;
    string beginStr{};
    string endStr{};
    unordered_set<string> dict{}; // 一共有n+2个字符串
    cin >> beginStr >> endStr;
    dict.insert(beginStr);
    dict.insert(endStr);
    string tmpStr{"tmp"};
    for (int i = 0; i < n; ++i)
    {
        cin >> tmpStr;
        dict.insert(tmpStr);
    }

    // -- 构建邻接链表
    struct listNode
    {
        string str;
        listNode *next;
        listNode(const string &initStr) : str(initStr), next(nullptr) {};
    };
    auto findNeighbor = [&dict, &tmpStr](string tarStr) -> listNode *
    {
        listNode *res = nullptr;
        listNode *tailNode = nullptr;
        auto pushback = [&res, &tailNode](string &inputStr)
        {
            if (res == nullptr)
            {
                res = new listNode(inputStr);
                tailNode = res;
            }
            else
            {
                tailNode->next = new listNode(inputStr);
                tailNode = tailNode->next;
            }
        };

        for (int pos = 0; pos < tarStr.size(); ++pos)
        {
            // 对于每一个位置进行遍历
            tmpStr = tarStr;
            for (int thisChar = 'a'; thisChar <= 'z'; ++thisChar)
            {
                // 对该位置对每个字母进行遍历
                if (thisChar != tarStr[pos])
                {
                    tmpStr[pos] = thisChar;
                    if (dict.find(tmpStr) != dict.end())
                    {
                        // 改变一个字母后面在字典找到了
                        pushback(tmpStr);
                    }
                }
            }
        }
        return res;
    };
    unordered_map<string, listNode *> map{};
    for (auto str_ : dict)
    {
        map[str_] = findNeighbor(str_);
    }

    // -- 主循环，bfs搜索
    unordered_set<string> processQueue{}; // 按理来说这里应该使用deque方便一点
    unordered_set<string> closed{};
    processQueue.insert(beginStr);
    for (int step = 1;; ++step)
    {
        for (auto str_ : processQueue)
        {
            closed.insert(str_);
            if (str_ == endStr)
            {
                // 找到了
                cout << step;
                return 0;
            }
        }
        // 没找到，需要再扩展一层
        unordered_set<string> tmpStrSet{};
        for (auto str_ : processQueue)
        {
            listNode *curNode = map[str_];
            while (curNode != nullptr)
            {
                if (closed.find(curNode->str) == closed.end())
                {
                    // closed数组中不包含当前节点的字符串
                    tmpStrSet.insert(curNode->str);
                }
                curNode = curNode->next;
            }
        }
        processQueue = tmpStrSet;
    }

    return 0;
}