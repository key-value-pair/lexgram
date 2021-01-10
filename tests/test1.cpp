#include "RegExp.h"

int main(int argc, char* argv[]) {
    RegExpNode node {'a'};
    return !node.nodeTypeIs(RegExpNode::Normal);
}
