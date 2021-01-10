#ifndef REGEXP_H
#define REGEXP_H

#include <string>
#include <vector>

class RegExpNode {
public:
    enum NodeType {
        Normal,
        Repeated,
        Or,
        Concat
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
        
    void addSubRegExpNode(RegExpNode* regExpNode) {
        subRegExpNodes_.push_back(regExpNode);
    }
    
    void setSubRegExpNodes(const std::vector<RegExpNode*>& regExpNodes) {
        subRegExpNodes_ = regExpNodes;
    }
    
    std::vector<RegExpNode*> getSubRegExpNodes() {
        return subRegExpNodes_;
    }
private:
    NodeType nodeType_ = Normal;
    char ch_;
    std::vector<RegExpNode*> subRegExpNodes_;
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
