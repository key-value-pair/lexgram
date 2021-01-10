#include "RegExp.h"

int main(int argc, char* argv[]) {
    RegExp regExp{"abc"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();
    
    if (root == nullptr) {
        return 1;
    }
    if (!root->nodeTypeIs(RegExpNode::Concat)) {
        return 1;
    }
    if (root->getSubRegExpNodes().size() != 3) {
        return 1;
    }
    if (root->getSubRegExpNodes()[0]->getChar() != 'a') {
        return 1;
    }
    if (!root->getSubRegExpNodes()[0]->nodeTypeIs(RegExpNode::Normal)) {
        return 1;
    }
    if (root->getSubRegExpNodes()[1]->getChar() != 'b') {
        return 1;
    }
    if (!root->getSubRegExpNodes()[1]->nodeTypeIs(RegExpNode::Normal)) {
        return 1;
    }
    if (root->getSubRegExpNodes()[2]->getChar() != 'c') {
        return 1;
    }
    if (!root->getSubRegExpNodes()[2]->nodeTypeIs(RegExpNode::Normal)) {
        return 1;
    }
    
    return 0;
}
