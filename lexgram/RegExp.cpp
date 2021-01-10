#include <stack>
#include "RegExp.h"

RegExp::~RegExp() {
    std::stack<RegExpNode*> curNodes;
    curNodes.push(root_);
    while (curNodes.size()) {
        auto curNode = curNodes.top();
        curNodes.pop();
        for (auto subNode : curNode->getSubRegExpNodes()) {
            curNodes.push(subNode);
        }
        delete curNode;
    }
}

void RegExp::convertStrToRegExpNode() {
    // TODO
}
