#include "RegExp.h"
#include "test_tool.h"

void testRegExp1() {
    RegExp regExp{"abc"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    AssertEqualDefaultMsg(root != nullptr);
    AssertEqualDefaultMsg(root->nodeTypeIs(RegExpNode::Concat));
    AssertEqualDefaultMsg(root->getSubRegExpNodes().size() == 3);
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[0]->getChar() == 'a');
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[0]->nodeTypeIs(RegExpNode::Normal));
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[1]->getChar() == 'b');
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[1]->nodeTypeIs(RegExpNode::Normal));
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[2]->getChar() == 'c');
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[2]->nodeTypeIs(RegExpNode::Normal));
}

void testRegExp2() {
    RegExp regExp{"a|b"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    AssertEqualDefaultMsg(root != nullptr);
    AssertEqualDefaultMsg(root->nodeTypeIs(RegExpNode::Or));
    AssertEqualDefaultMsg(root->getSubRegExpNodes().size() == 2);
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[0]->getChar() == 'a');
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[0]->getChar() == 'b');
}

void testRegExp3() {
    RegExp regExp{"a*b"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    AssertEqualDefaultMsg(root != nullptr);
    AssertEqualDefaultMsg(root->nodeTypeIs(RegExpNode::Concat));
    AssertEqualDefaultMsg(root->getSubRegExpNodes().size() == 2);
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[0]->nodeTypeIs(RegExpNode::Repeated));
    AssertEqualDefaultMsg(root->getSubRegExpNodes()[1]->getChar() == 'b');
}

ADD_TEST(testRegExp1);
ADD_TEST(testRegExp2);
ADD_TEST(testRegExp3);
