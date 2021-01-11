#include "RegExp.h"
#include "test_tool.h"

void testRegExp1() {
    RegExp regExp{"abc"};
    NO_EXCEPTION(regExp.convertStrToRegExpNode());
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
    NO_EXCEPTION(regExp.convertStrToRegExpNode());
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Or));
    TEST_T(root->getSubRegExpNodes().size() == 2);
    TEST_T(root->getSubRegExpNodes()[0]->getChar() == 'a');
    TEST_T(root->getSubRegExpNodes()[1]->getChar() == 'b');
}

void testRegExp3() {
    RegExp regExp{"a*b"};
    NO_EXCEPTION(regExp.convertStrToRegExpNode());
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Concat));
    TEST_T(root->getSubRegExpNodes().size() == 2);
    TEST_T(root->getSubRegExpNodes()[1]->getChar() == 'b');
    auto start = root->getSubRegExpNodes()[0];
    TEST_T(start->nodeTypeIs(RegExpNode::Repeated));
    TEST_T(start->getSubRegExpNodes().size() == 1);
    TEST_T(start->getSubRegExpNodes()[0]->getChar() == 'a');
}

void testRegExp4() {
    RegExp regExp {"a|b*"};
    NO_EXCEPTION(regExp.convertStrToRegExpNode());
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Or));
    TEST_T(root->getSubRegExpNodes().size() == 2);
    TEST_T(root->getSubRegExpNodes()[0]->nodeTypeIs(RegExpNode::Normal));
    TEST_T(root->getSubRegExpNodes()[0]->getChar() == 'a');

    auto star = root->getSubRegExpNodes()[1];
    TEST_T(star->nodeTypeIs(RegExpNode::Repeated));
    TEST_T(star->getSubRegExpNodes().size() == 1);
    TEST_T(star->getSubRegExpNodes()[0]->getChar() == 'b');
    
}

void testRegExp5() {
    RegExp regExp {"a|b|c"};
    NO_EXCEPTION(regExp.convertStrToRegExpNode());
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Or));
    TEST_T(root->getSubRegExpNodes().size() == 3);
    TEST_T(root->getSubRegExpNodes()[0]->getChar() == 'a');
    TEST_T(root->getSubRegExpNodes()[1]->getChar() == 'b');
    TEST_T(root->getSubRegExpNodes()[2]->getChar() == 'c');
}

void testRegExp6() {
    RegExp regExp {"a|bc"};
    NO_EXCEPTION(regExp.convertStrToRegExpNode());
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Or));
    TEST_T(root->getSubRegExpNodes().size() == 2);
    TEST_T(root->getSubRegExpNodes()[0]->getChar() == 'a');

    auto concat = root->getSubRegExpNodes()[1];
    TEST_T(concat->nodeTypeIs(RegExpNode::Concat));
    TEST_T(concat->getSubRegExpNodes().size() == 2);
    TEST_T(concat->getSubRegExpNodes()[0]->getChar() == 'b');
    TEST_T(concat->getSubRegExpNodes()[1]->getChar() == 'c');
}

void testRegExp7() {
    RegExp regExp {"ab|c"};
    NO_EXCEPTION(regExp.convertStrToRegExpNode());
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Or));
    TEST_T(root->getSubRegExpNodes().size() == 2);
    TEST_T(root->getSubRegExpNodes()[1]->getChar() == 'c');
    auto concat = root->getSubRegExpNodes()[0];
    TEST_T(concat->nodeTypeIs(RegExpNode::Concat));

    TEST_T(concat->getSubRegExpNodes().size() == 2);
    TEST_T(concat->getSubRegExpNodes()[0]->getChar() == 'a');
    TEST_T(concat->getSubRegExpNodes()[1]->getChar() == 'b');
}

void testRegExp8() {
    RegExp regExp {"a*|c"};
    NO_EXCEPTION(regExp.convertStrToRegExpNode());
    auto root = regExp.getRoot();

    TEST_T(root != nullptr);
    TEST_T(root->nodeTypeIs(RegExpNode::Or));
    TEST_T(root->getSubRegExpNodes().size() == 2);
    TEST_T(root->getSubRegExpNodes()[1]->getChar() == 'c');
    auto star = root->getSubRegExpNodes()[0];
    TEST_T(star->nodeTypeIs(RegExpNode::Repeated));

    TEST_T(concat->getSubRegExpNodes().size() == 1);
    TEST_T(concat->getSubRegExpNodes()[0]->getChar() == 'a');
}

ADD_TEST(testRegExp1);
ADD_TEST(testRegExp2);
ADD_TEST(testRegExp3);
ADD_TEST(testRegExp4);
ADD_TEST(testRegExp5);
ADD_TEST(testRegExp6);
ADD_TEST(testRegExp7);
ADD_TEST(testRegExp8);
