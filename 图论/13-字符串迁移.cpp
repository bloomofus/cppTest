#include <bits/stdc++.h>
using namespace std;

// #define debug

#ifdef debug
#define dbg cout << "[DEBUG] " << __FILE__ << ":" << __LINE__ << endl;
#else
#define dbg ;
#endif

// -- tools
// 辅助函数：获取整数转换为字符串后的长度
int get_digit_width(int val)
{
    string s = to_string(val);
    return s.length();
}

// 模板版本：打印一维数组（支持指定宽度）
template <typename T>
void print_arr(const vector<T> &arr, int width)
{
    cout << "[";
    for (size_t i = 0; i < arr.size(); ++i)
    {
        if (i > 0)
            cout << ", ";
        // setw(width) 设置最小宽度，right 表示右对齐（数字通常右对齐更整齐）
        cout << setw(width) << arr[i];
    }
    cout << "]";
}

// 模板版本：打印二维数组（矩阵）- 自动计算最大宽度并对齐
template <typename T>
void print_mat(const vector<vector<T>> &mat)
{
    if (mat.empty())
    {
        cout << "[]" << endl;
        return;
    }

    // 1. 遍历所有元素，找到最大数字的字符串长度
    int max_width = 1;
    for (const auto &row : mat)
    {
        for (const auto &val : row)
        {
            int w = get_digit_width(val);
            if (w > max_width)
                max_width = w;
        }
    }

    // 为了美观，可以额外加1个空格 padding
    max_width += 1;

    cout << "[" << endl;
    for (const auto &row : mat)
    {
        cout << "  "; // 行首缩进
        print_arr(row, max_width);
        cout << endl;
    }
    cout << "]" << endl;
}

int main()
{
    // -- 思路
    // 本题相当于在图结构中，找到起始节点到目标节点的最短路径，
    // 一般使用bfs，如果使用双向bfs，听着高级，但是处理很麻烦
    // 为什么使用邻接链表，在遍历一个节点的扇出节点的时候很方便

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