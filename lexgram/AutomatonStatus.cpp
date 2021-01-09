#include "AutomatonStatus.h"

void AutomatonStatus::addTransfer(char ch, AutomatonStatus* transferStatus) {
    transferTables_[ch].insert(transferStatus);
}

std::set<AutomatonStatus*> AutomatonStatus::transfer(char ch) {
    return transferTables_[ch];
}
