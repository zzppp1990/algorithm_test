/*
* 单元测试
*/

#include <stdexcept>
#include <catch.hpp>
#include <BinTree.h>


TEST_CASE("My first test", "[my]")
{
  INFO("Testing");
  CHECK(1 + 1 == 2);
  BinNode<int> nodep;
  int size = nodep.size();
  CHECK(size == 0);
}


