#include "test_tool.h"

void runTest() {
  std::vector<AssertFail> afList;
  std::vector<bool> passList;
  
  for (auto fun : RegisterTest::getFunList()) {
    try {
      fun();
      passList.push_back(true);
    } catch (const AssertFail& af) {
      afList.push_back(af);
      passList.push_back(false);
    }
  }

  std::cerr << "all: " << RegisterTest::getFunList().size()
	    << ", fail: " << afList.size()
	    << ", pass: " << (RegisterTest::getFunList().size()-afList.size())
	    << std::endl;

  for (auto p : passList)
    std::cerr << (p ? "." : "x");
  std::cerr << std::endl;
  
  for (auto af : afList)
    std::cerr << af.what() << std::endl;
}

std::vector<std::function<void(void)>> RegisterTest::m_functionList{};
