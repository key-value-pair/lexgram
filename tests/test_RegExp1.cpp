#include "RegExp.h"
#include "test_tool.h"

void testRegExp1() {
    RegExp regExp{"abc"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Concat));
    TEST_T(root->getSubRegExpNodes().size() == 3);
    TEST_T(root->getSubRegExpNodes()[0]->getChar() == 'a');
    TEST_T(root->getSubRegExpNodes()[0]->nodeTypeIs(RegExpNode::Normal));
    TEST_T(root->getSubRegExpNodes()[1]->getChar() == 'b');
    TEST_T(root->getSubRegExpNodes()[1]->nodeTypeIs(RegExpNode::Normal));
    TEST_T(root->getSubRegExpNodes()[2]->getChar() == 'c');
    TEST_T(root->getSubRegExpNodes()[2]->nodeTypeIs(RegExpNode::Normal));
}

void testRegExp2() {
    RegExp regExp{"a|b"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Or));
    TEST_T(root->getSubRegExpNodes().size() == 2);
    TEST_T(root->getSubRegExpNodes()[0]->getChar() == 'a');
    TEST_T(root->getSubRegExpNodes()[1]->getChar() == 'b');
}

void testRegExp3() {
    RegExp regExp{"a*b"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Concat));
    TEST_T(root->getSubRegExpNodes().size() == 2);
    TEST_T(root->getSubRegExpNodes()[0]->nodeTypeIs(RegExpNode::Repeated));
    TEST_T(root->getSubRegExpNodes()[1]->getChar() == 'b');
}

void testRegExp4() {
    RegExp regExp {"a|b*"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Or));
    TEST_T(root->getSubRegExpNodes().size() == 2);
    TEST_T(root->getSubRegExpNodes()[0]->nodeTypeIs(RegExpNode::Normal));
    TEST_T(root->getSubRegExpNodes()[0]->getChar() == 'a');
    TEST_T(root->getSubRegExpNodes()[1]->nodeTypeIs(RegExpNode::Repeated));
}

void testRegExp5() {
    RegExp regExp {"a|b|c"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Or));
    TEST_T(root->getSubRegExpNodes().size() == 3);
    TEST_T(root->getSubRegExpNodes()[0]->getChar() == 'a');
    TEST_T(root->getSubRegExpNodes()[1]->getChar() == 'b');
    TEST_T(root->getSubRegExpNodes()[2]->getChar() == 'c');
}

ADD_TEST(testRegExp1);
ADD_TEST(testRegExp2);
ADD_TEST(testRegExp3);
ADD_TEST(testRegExp4);
ADD_TEST(testRegExp5);
