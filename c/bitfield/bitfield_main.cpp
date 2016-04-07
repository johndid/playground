#include <iostream>
#include "bitfield.h"

enum KeyMod
{
    Alt     = 1 << 0,  // 1
    Shift   = 1 << 1,  // 2
    Control = 1 << 2   // 4
};

void printState(const FlagSet<KeyMod>& keyMods)
{
    std::cout << "Alt is "     << (keyMods.test(Alt)     ? "set" : "unset") << ".\n";
    std::cout << "Shift is "   << (keyMods.test(Shift)   ? "set" : "unset") << ".\n";
    std::cout << "Control is " << (keyMods.test(Control) ? "set" : "unset") << ".\n";
}

int main(int argc, char* argv[])
{
    FlagSet<KeyMod> keyMods(Shift | Control);

    printState(keyMods);

    keyMods.set(Alt);
    //keyMods.set(24);    // error - an int is not a KeyMod value
    keyMods.set(Shift);
    keyMods.flip(Control);

    printState(keyMods);

    return 0;
}
