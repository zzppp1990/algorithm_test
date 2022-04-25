/*
* 单元测试
*/

#include <stdexcept>
#include <catch.hpp>
#include <CPathNode.h>
#include <CPathTree.h>

class Solution {
public:
    CStrategy* m_poStrategy;
public:
    void setStrategy(CStrategy* in_strategy) {
        m_poStrategy = in_strategy;
    }
    
    int lengthLongestPath(std::string input) {
        m_poStrategy->Init(input);
        int len = m_poStrategy->getFileAbsPath();
        std::cout << "---------- longest length is " << len << std::endl;
        return len;
    }
};

/*CPathNode类构造函数测试*/
TEST_CASE("CPathNode test", "[1]")
{
  INFO("CPathNode test");
  CPathNode t_oPathNode;
  CHECK(t_oPathNode.m_vecChildPathNode.size() == 0);
  CHECK(t_oPathNode.m_iNodePathDepth == -1);
  CHECK(t_oPathNode.m_enNodeType == FILE_TYPE);
  CHECK(t_oPathNode.m_poParentPathNode == nullptr);
  CHECK(t_oPathNode.m_sNodeName == "");
}

/*CPathTree::getNodeName 函数测试*/
TEST_CASE("CPathTree test getNodeName", "[my]")
{
  INFO("CPathTree test getNodeName");
  CPathTree t_oPathTree;

  std::string input = "file1.txt";
  std::string nodeName = "file1.txt";
  std::string t_sRemainInputStr = "";
  t_oPathTree.getNodeName(input, nodeName, t_sRemainInputStr);
  CHECK(nodeName == "file1.txt");
  CHECK(t_sRemainInputStr == "");

  input = "file1.txt\nfile2.txt\nlongfile.txt";
  nodeName = "file1.txt";
  t_sRemainInputStr = "";
  t_oPathTree.getNodeName(input, nodeName, t_sRemainInputStr);
  CHECK(nodeName == "file1.txt");
  CHECK(t_sRemainInputStr == "\nfile2.txt\nlongfile.txt");

  input = "";
  nodeName = "";
  t_sRemainInputStr = "";
  t_oPathTree.getNodeName(input, nodeName, t_sRemainInputStr);
  CHECK(nodeName == "");
  CHECK(t_sRemainInputStr == "");
}

/*CPathTree::getNodeName 函数测试*/
TEST_CASE("CPathTree test getNodeType", "[my]")
{
  INFO("CPathTree test getNodeType");
  CPathTree t_oPathTree;

  std::string nodeName = "file1.txt";
  NodeType ret = t_oPathTree.getNodeType(nodeName);
  CHECK(ret == FILE_TYPE);

  nodeName = "dir";
  ret = t_oPathTree.getNodeType(nodeName);
  CHECK(ret == DIR_TYPE);
}

/*Solution::lengthLongestPath 函数测试*/
TEST_CASE("Solution test lengthLongestPath pathTree strategy", "[my]")
{
  INFO("Solution test lengthLongestPath pathTree strategy");
  CStrategy* t_poStrategy1 = new CPathTree;
  
  Solution s;
  s.setStrategy(t_poStrategy1);
  int ret = s.lengthLongestPath("file1.txt\nfile2.txt\nlongfile.txt");
  CHECK(ret == 12);

  ret = s.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
  CHECK(ret == 32);

  ret = s.lengthLongestPath("a");
  CHECK(ret == 0);

  ret = s.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");
  CHECK(ret == 20);
}

TEST_CASE("Solution test lengthLongestPath easy strategy", "[my]")
{
  INFO("Solution test lengthLongestPath easy strategy");
  CStrategy* t_poStrategy2 = new CEasyStrategy;
  
  Solution s;
  s.setStrategy(t_poStrategy2);
  int ret = s.lengthLongestPath("file1.txt\nfile2.txt\nlongfile.txt");
  CHECK(ret == 12);

  ret = s.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
  CHECK(ret == 32);

  ret = s.lengthLongestPath("a");
  CHECK(ret == 0);

  ret = s.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");
  CHECK(ret == 20);
}


