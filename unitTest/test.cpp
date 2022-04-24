/*
* 单元测试
*/
#include <catch.hpp>
#include <CPathNode.h>
#include <stdexcept>

void test(int n)
{
  if (n == 42) {
    return;
  }
  throw std::runtime_error(
    "Not the answer");
}

TEST_CASE("CPathNode test", "[CPathNode]")
{
  INFO("CPathNode test");
  CPathNode t_oPathNode;
  CHECK(t_oPathNode.m_vecChildPathNode.size() == 1);

}

