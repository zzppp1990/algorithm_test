#include <QCoreApplication>
#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
using namespace std;

class Solution_nc76
{
public:

    void push(int node) {
        while(!stack2.empty()) {
            int elem = stack2.top();
            stack2.pop();
            stack1.push(elem);
        }
        stack1.push(node);
    }

    int pop() {
        while(!stack1.empty()) {
            int node = stack1.top();
            stack2.push(node);
            stack1.pop();
        }
        int ret = stack2.top();
        stack2.pop();
        return ret;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Solution_nc76 s;
    s.push(1);

    cout << s.pop() << endl;
       s.push(2);
    cout << s.pop() << endl;
    return a.exec();
}
