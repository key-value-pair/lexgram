#include "AutomatonStatus.h"

void AutomatonStatus::addTransfer(char ch, AutomatonStatus* transferStatus) {
    transferTables_[ch].insert(transferStatus);
}
