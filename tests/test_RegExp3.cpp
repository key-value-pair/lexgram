#include "RegExp.h"

int main(int argc, char* argv[]) {
    RegExp regExp{"a*b"};
    regExp.convertStrToRegExpNode();
    auto root = regExp.getRoot();

    if (root == nullptr) {
        return 1;
    }
    if (!root->nodeTypeIs(RegExpNode::Concat)) {
        return 2;
    }
    if (root->getSubRegExpNodes().size() != 2) {
        return 3;
    }
    if (!root->getSubRegExpNodes()[0]->nodeTypeIs(RegExpNode::Repeated)) {
        return 4;
    }
    if (root->getSubRegExpNodes()[1]->getChar() != 'b') {
        return 5;
    }
    if (!root->getSubRegExpNodes()[1]->nodeTypeIs(RegExpNode::Normal)) {
        return 6;
    }

    return 0;
}
