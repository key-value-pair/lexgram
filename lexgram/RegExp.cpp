#include <stack>

#include "Exception.h"
#include "RegExp.h"

RegExpNode* RegExpNode::createOrNode() {
    if (hasParentRegExpNode()) {
        auto parent = getParentRegExpNode();
        if (parent->nodeTypeIs(Or)) {
            return parent;
        } else {
            return parent->createOrNode();
        }
    } else {
        auto parent = createParentRegExpNode();
        parent->setNodeType(Or);
        return parent;
    }
}

RegExpNode* RegExpNode::createNormalNode(char ch) {
    if (hasParentRegExpNode()) {
        auto parent = getParentRegExpNode();
        if (parent->nodeTypeIs(Concat)) {
            auto normalNode = new RegExpNode(ch);
            normalNode->setParentRegExpNode(parent);
            parent->addSubRegExpNode(normalNode);
            return parent;
        }

        if (parent->nodeTypeIs(Repeated)) {
            return parent->createNormalNode(ch);
        }

        if (parent->nodeTypeIs(Normal)) {
            throw InvalidRegExpException();
        }

        // parent->nodeTypeIs(Or) == true
        if (nodeTypeIs(Normal) || nodeTypeIs(Repeated)) {
            parent->removeSubRegExpNode(this);
            auto newParentNode = createParentRegExpNode();
            auto normalNode = new RegExpNode(ch);
            newParentNode->addSubRegExpNode(normalNode);
            normalNode->setParentRegExpNode(newParentNode);
            return newParentNode;
        }

        if (nodeTypeIs(Concat)) {
            auto normalNode = new RegExpNode(ch);
            parent->addSubRegExpNode(normalNode);
            normalNode->setParentRegExpNode(parent);
            return parent;
        }

        if (nodeTypeIs(Or)) {
            throw InvalidRegExpException();
        }
    } else {
        auto parent = createParentRegExpNode();
        parent->setNodeType(Concat);
        auto normalNode = new RegExpNode(ch);
        normalNode->setParentRegExpNode(parent);
        parent->addSubRegExpNode(normalNode);
        return parent;
    }
}

RegExpNode* RegExpNode::createRepeatedNode() {
    if (hasParentRegExpNode()) {
        auto parent = getParentRegExpNode();
        if (parent->nodeTypeIs(Repeated)) {
            return parent;
        }

        if (nodeTypeIs(Normal)) {
            parent->removeSubRegExpNode(this);
            auto newParent = createParentRegExpNode();
            newParent->setNodeType(Repeated);
            newParent->setParentRegExpNode(parent);
            parent->addSubRegExpNode(newParent);
            return parent;
        }
    } else {
        auto parent = createParentRegExpNode();
        parent->setNodeType(Repeated);
        return parent;
    }
}

RegExpNode* RegExpNode::createConcatNode() {
    if (hasParentRegExpNode()) {
        auto parent = getParentRegExpNode();
        if (parent-nodeTypeIs(Concat)) {
            return parent;
        }

        if (parent->nodeTypeIs(Repeated)) {
            return parent->createConcatNode();
        }

        if (parent->nodeTypeIs(Or)) {
            parent->removeSubRegExpNode(this);
            auto newParent = createParentRegExpNode();
            newParent->setNodeType(Concat);
            newParent->setParentRegExpNode(parent);
            parent->addSubRegExpNode(newParent);
            return newParent;
        }
    } else {
        auto parent = createParentRegExpNode();
        parent->setNodeType(Concat);
        return parent;
    }
}

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
    char prevCh;
    for (auto it = regExpStr_.begin(); it != regExpStr_.end(); ++it) {
        auto ch = *it;
        switch (ch) {
        case '|': {
            if (curNode == nullptr) {
                throw InvalidRegExpException();
            }

            auto curParentNode = curNode->createOrNode();
            curNode = curParentNode->getRightmostSubRegExpNode();
        }
            break;
        case '*': {
            if (curNode == nullptr) {
                throw InvalidRegExpException();
            }

            auto curParentNode = curNode->createRepeatedNode();
            curNode = curParentNode->getRightmostSubRegExpNode();
        }
            break;
        default: {
            if (curNode == nullptr) {
                curNode = new RegExpNode(ch);
                root_ = curNode;
            } else {
                if (prevCh != '|') {
                    auto curParentNode = curNode->createConcatNode();
                    curNode = curParentNode->getRightmostSubRegExpNode();
                }
                auto curParentNode = curNode->createNormalNode(ch);
                curNode = curParentNode->getRightmostSubRegExpNode();
            }
        }
            break;
        }
        prevCh = ch;
    }

    if (curNode == nullptr) {
        throw InvalidRegExpException();
    }

    while (curNode != nullptr) {
        root_ = curNode;
        curNode = curNode->getParentRegExpNode();
    }
}
