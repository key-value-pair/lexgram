#ifndef TEST_TOOL_H
#define TEST_TOOL_H

#include <exception>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

/*****************************************************
 * private interface
 *   - AssertFail
 *   - RegisterTest
 *****************************************************/
class AssertFail final: public std::exception {
 public:
 AssertFail(const std::string& msg, const std::string& filename,
	    const std::string& funcname, int line)
   : m_msg{msg}, m_filename{filename}, m_funcname{funcname}, m_line{line} {}
  const char* what() const noexcept {
    static std::string format_msg;

    format_msg = "[" + m_filename + "]"
      + "[" + m_funcname + "]"
      + "[" + std::to_string(m_line) + "]: "
      + m_msg;

    return format_msg.c_str();
  }
 private:
  const std::string m_msg;
  const std::string m_filename;
  const std::string m_funcname;
  const int m_line;
};

class RegisterTest final {
 public:
  explicit RegisterTest(std::function<void(void)> fun) {
    m_functionList.push_back(fun);
  }
  static const std::vector<std::function<void(void)>>& getFunList() {
    return m_functionList;
  }
 private:
  static std::vector<std::function<void(void)>> m_functionList;
};


/*****************************************************
 * public interface
 *   - runTest
 *   - AssertEqual
 *   - AssertEqualDefaultMsg
 *   - AssertTrue
 *   - AssertTrueDefaultMsg
 *   - ADD_TEST
 *****************************************************/
void runTest();

#define AssertEqual(actual, expect, msg)			\
  do {								\
    if (!((actual) == (expect))) {				\
      throw AssertFail(msg, __FILE__, __FUNCTION__, __LINE__);	\
    }								\
  } while (false)

#define AssertEqualDefaultMsg(actual, expect)			\
  AssertEqual(actual, expect,					\
	      "Expect<" + std::to_string(expect) + ">, "	\
	      + "Actual<" + std::to_string(actual) + ">")

#define AssertTrue(cond, msg)					\
  do {								\
    if (!(cond)) {						\
      throw AssertFail(msg, __FILE__, __FUNCTION__, __LINE__);	\
    }								\
  } while (false)

#define AssertTrueDefaultMsg(cond)			\
  AssertTrue(cond, "Expect<true>, Actual<false>")

#define TEST_T(cond)                                            \
    AssertTrue(cond, #cond ", Expect<true>, Actual<false>")

#define TEST_F(cond)                                            \
    AssertTure(!(cond), #cond ", Expect<false>, Actual<true>")

#define ADD_TEST(fun)					\
  static const RegisterTest RegisterTest##fun{fun};

#endif // TEST_TOOL_H
