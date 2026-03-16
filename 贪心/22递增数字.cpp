#include "core.h"
#include "myclass.h"
#include "mytree.h"

using namespace std;

void print_vec2(int* arr_head,int arr_lenth);


class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        if(n<=9) return n;
        int arr[10]={0};
        for(int i=0;i<10;++i)
        {
            arr[i]=n%10;
            n/=10;
            if(n==0) break;
        }
        for(int i=9;i>=0;--i)
        {
            cout<<arr[i]<<" ";
            if(i==0) cout<<endl;
        } 
        int noZeroIdx=-1;
        int decreaseIdx=-1;
        int lastSame=-1;
        for(int i=8;i>=0;--i)
        {
            if(noZeroIdx==-1&&arr[i]>0) noZeroIdx=i;
            if(decreaseIdx==-1&&arr[i]<arr[i+1]) decreaseIdx=i+1;
            if(decreaseIdx!=-1)
            {
                lastSame=decreaseIdx;
                //搜索前面相等的第一个数
                for(int j=lastSame+1;j<=noZeroIdx;++j){
                    if(arr[j]==arr[decreaseIdx]) lastSame=j;
                }
            }
            if(noZeroIdx!=-1&&decreaseIdx!=-1) break;
        }
        int tail=0;
        for(int i=lastSame;i>=0;--i){
            if(i==lastSame) tail=arr[i]-1;
            else{
                tail=tail*10+9;
            }
        }
        int head=0;
        for(int i=noZeroIdx;i>=0;--i){
            if(noZeroIdx==lastSame) break;
            if(i==noZeroIdx) head=arr[i];
            else if(i>lastSame){
                head=head*10+arr[i];
            }
            else head*=10;
        }

        ;
        return head+tail;
    }
};

int main()
{
    Solution so;
    vector<int> nums = {2,0,0};
    int num=55321;
    cout<<so.monotoneIncreasingDigits(num)<<endl;

}