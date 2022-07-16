#include <QCoreApplication>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;


struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
            val(x), next(NULL) {
    }
};

class Solution {
public:
    void printList(ListNode* node) {
        while(node) {
            cout << node->val << "\t" ;
            node = node->next;
        }
        cout << endl;
    }

    /*NC78 还是画个图会比较好*/
    ListNode* ReverseList(ListNode* pHead) {
        ListNode* pre = NULL;
        ListNode* next = NULL;
        while(pHead) {
            next = pHead->next;
            pHead->next = pre;
            pre = pHead;
            pHead = next;
        }
        return pre;
    }

    /*NC61 请在数组中找出两个加起来等于目标值的数的下标，返回的下标按升序排列*/
    vector<int> twoSum(vector<int>& numbers, int target) {
       // write code here
       map<int,int> stmap;
       vector<int> ret;
       ret.clear();
       for(size_t i = 0; i < numbers.size(); ++i) {
           stmap[numbers[i]] = i;
       }

       int times = numbers.size() - 1;
       for(int i = 0; i <= times; ++i) {
           int findNum = (target - numbers[i]);

           if(stmap.end() != stmap.find(findNum) && stmap[findNum] != i) {
               ret.push_back(i+1);
               ret.push_back(stmap[findNum] + 1);
               break;
           }
       }
       return ret;
    }

    /*NC68 跳台阶*/
    int jumpFloor(int number) {
        if(number <= 0)
            return 0;
        if(number == 1)
            return 1;
        if(number == 2)
            return 2;

        return jumpFloor(number - 1) + jumpFloor(number - 2);
    }
};

/*NC140*/
struct myclass {
    bool operator() (int i, int j) {
        return (i < j);
    }
}myobject;

int main_bak(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ListNode* node = new ListNode(1);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(3);

    node->next = node2;
    node2->next = node3;
    Solution s;
    s.printList(node);

    ListNode* pstRet = s.ReverseList(node);
    s.printList(pstRet);

    /*排序题*/
    vector<int> avec = {5,4,3,2,1};
    sort(avec.begin(), avec.end(), myobject);
    for(auto i : avec) {
        cout << i << "\t";
    }
    cout << endl;


    vector<int> numbers = {3,2,4};
    int target  = 6;
    s.twoSum(numbers, target);

    cout << "sf7 : " << s.jumpFloor(7) << endl;
    return a.exec();
}
