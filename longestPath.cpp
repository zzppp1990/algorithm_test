/*
* github test
* 文件最长绝对路径
* 存在的问题：耗时较高，消耗内存较多
*/

#include "CPathTree.h"

class Solution {
public:
    
    int lengthLongestPath(std::string input) {
        
        CPathTree t_oPathTree(input);
        t_oPathTree.InitPathTree();
        t_oPathTree.printPathTree(t_oPathTree.m_oRoot);
        
        std::string filePathStr = "";
        t_oPathTree.getFileAbsPath(t_oPathTree.m_oRoot, filePathStr);
        std::cout << "---------- longest length is " << t_oPathTree.m_iLongestLength << std::endl;
        return t_oPathTree.m_iLongestLength;
    }
};

int main ()
{
    Solution s;
    //s.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
    //s.lengthLongestPath("a");
    s.lengthLongestPath("file1.txt\nfile2.txt\nlongfile.txt");
    return 0;
}

