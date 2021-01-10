#include <stack>

#include "Exception.h"
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
    RegExpNode* curNode = nullptr;
    for (auto it = regExpStr_.begin(); it != regExpStr_.end(); ++it) {
        auto ch = *it;
        switch (ch) {
        case '|': {
            if (curNode == nullptr) {
                throw InvalidRegExpException();
            }
            auto parentNode = curNode->getParentRegExpNode();
            if (parentNode == nullptr) {
                parentNode = curNode->createParentRegExpNode();
                parentNode->setNodeType(RegExpNode::Or);
                root_ = parentNode;
            } else {
                if (parentNode->nodeTypeIs(RegExpNode::Or)) {
                    // do nothing
                } else if (parentNode->nodeTypeIs(RegExpNode::Concat)) {
                    auto grandparent = parentNode->getParentRegExpNode();
                    if (grandparent == nullptr) {
                        grandparent = parentNode->createParentRegExpNode();
                        grandparent->setNodeType(RegExpNode::Or);
                        root_ = grandparent;
                    }
                    if (!grandparent->nodeTypeIs(RegExpNode::Or)) {
                        throw InvalidRegExpException();
                    }
                    curNode = parentNode;
                } else if (parentNode->nodeTypeIs(RegExpNode::Repeated)) {
                    throw InvalidRegExpException();
                }
            }
        }
            break;
        case '*': {
            if (curNode == nullptr) {
                throw InvalidRegExpException();
            }
            auto parentNode = curNode->getParentRegExpNode();
            if (parentNode == nullptr) {
                parentNode = curNode->createParentRegExpNode();
                parentNode->setNodeType(RegExpNode::Repeated);
                root_ = parentNode;
                curNode = parentNode;
            } else {
                if (parentNode->nodeTypeIs(RegExpNode::Or)) {
                    throw InvalidRegExpException();
                } else if (parentNode->nodeTypeIs(RegExpNode::Concat)) {
                } // TODO
            }
        }
            break;
        default:
            if (curNode == nullptr) {
                curNode = new RegExpNode(ch);
                root_ = curNode;
            } else {
                auto parentNode = curNode->getParentRegExpNode();
                if (parentNode == curNode) {
                    parentNode = curNode->createParentRegExpNode();
                    parentNode->setNodeType(RegExpNode::Concat);
                    root_ = parentNode;
                    curNode = new RegExpNode(ch);
                    parentNode->addSubRegExpNode(curNode);
                    curNode->setParentRegExpNode(parentNode);
                }
            }
            break;
        }
    }
}
