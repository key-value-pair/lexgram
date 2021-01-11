#ifndef REGEXP_H
#define REGEXP_H

#include <string>
#include <vector>

class RegExpNode {
public:
    enum NodeType {
        Normal, // 'a' 'b' ...
        Repeated, // 'a*' 'b*' ...
        Or, // 'a|b' 'b|c' ...
        Concat // 'a.b' or 'ab' ...
    };
    
    RegExpNode() = default;
    RegExpNode(NodeType nodeType):
        nodeType_(nodeType) {}
    RegExpNode(char ch):
        ch_(ch) {}
    
    void setNodeType(NodeType nodeType) {
        nodeType_ = nodeType;
    }
    
    NodeType getNodeType() {
        return nodeType_;
    }
    
    bool nodeTypeIs(NodeType nodeType) {
        return nodeType_ == nodeType;
    }
    
    void setChar(char ch) {
        ch_ = ch;
    }
    
    char getChar() {
        return ch_;
    }

    RegExpNode* createOrNode();
    RegExpNode* createNormalNode(char ch);
    RegExpNode* createRepeatedNode();
        
    void addSubRegExpNode(RegExpNode* regExpNode) {
        subRegExpNodes_.push_back(regExpNode);
    }

    RegExpNode* getRightmostSubRegExpNode() {
        if (subRegExpNodes_.size() == 0) {
            return nullptr;
        }

        return subRegExpNodes_.back();
    }

    void removeSubRegExpNode(RegExpNode* regExpNode) {
        for (auto it = subRegExpNodes_.begin(); it != subRegExpNodes_.end(); ++it) {
            if (*it == regExpNode) {
                (*it)->setParentRegExpNode(nullptr);
                subRegExpNodes_.erase(it);
                break;
            }
        }
    }
    
    void setSubRegExpNodes(const std::vector<RegExpNode*>& regExpNodes) {
        subRegExpNodes_ = regExpNodes;
    }
    
    std::vector<RegExpNode*> getSubRegExpNodes() {
        return subRegExpNodes_;
    }

    void setParentRegExpNode(RegExpNode* parentNode) {
        parentNode_ = parentNode;
    }

    RegExpNode* getParentRegExpNode() {
        return parentNode_;
    }

    bool hasParentRegExpNode() {
        return parentNode_ != nullptr;
    }

    RegExpNode* createParentRegExpNode() {
        auto parent = new RegExpNode();
        parent->addSubRegExpNode(this);
        parentNode_ = parent;
        return parent;
    }
private:
    NodeType nodeType_ = Normal;
    char ch_;
    std::vector<RegExpNode*> subRegExpNodes_;
    RegExpNode* parentNode_ = nullptr;
};

class RegExp {
public:
    RegExp(const std::string& regExpStr):
        regExpStr_(regExpStr) {}
    ~RegExp();
    void convertStrToRegExpNode();
    RegExpNode* getRoot() {
        return root_;
    }
private:
    std::string regExpStr_;
    RegExpNode* root_ = nullptr;
};
#endif // REGEXP_H
