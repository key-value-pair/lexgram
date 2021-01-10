#include "RegExp.h"

int main(int argc, char* argv[]) {
    RegExp regExp{"a|b"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    if (root == nullptr) {
        return 1;
    }
    if (!root->nodeTypeIs(RegExpNode::Or)) {
        return 2;
    }
    if (root->getSubRegExpNodes().size() != 2) {
        return 3;
    }
    if (root->getSubRegExpNodes()[0]->getChar() != 'a') {
        return 4;
    }
    if (root->getSubRegExpNodes()[1]->getChar() != 'b') {
        return 5;
    }

    return 0;
}
