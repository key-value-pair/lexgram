#include "RegExp.h"

bool testRegExp1() {
    RegExp regExp{"abc"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();
    
    if (root == nullptr) {
        return false;
    }
    if (!root->nodeTypeIs(RegExpNode::Concat)) {
        return false;
    }
    if (root->getSubRegExpNodes().size() != 3) {
        return false;
    }
    if (root->getSubRegExpNodes()[0]->getChar() != 'a') {
        return false;
    }
    if (!root->getSubRegExpNodes()[0]->nodeTypeIs(RegExpNode::Normal)) {
        return false;
    }
    if (root->getSubRegExpNodes()[1]->getChar() != 'b') {
        return false;
    }
    if (!root->getSubRegExpNodes()[1]->nodeTypeIs(RegExpNode::Normal)) {
        return false;
    }
    if (root->getSubRegExpNodes()[2]->getChar() != 'c') {
        return false;
    }
    if (!root->getSubRegExpNodes()[2]->nodeTypeIs(RegExpNode::Normal)) {
        return false;
    }
    
    return true;
}

int main(int argc, char* argv[]) {
    if (!testRegExp1()) {
        return 1;
    }
    
    return 0;
}
