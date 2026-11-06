#include "sma3_controls.h"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
int main(){
 sma3::Controls c; const auto defaults=c.buttons;
 assert(c.assign(0,3)); // Simulate the user's action currently on physical Y.
 assert(c.assign(0,2)); // Move that same GBA action to physical X.
 assert(c.keyinput(1u<<2)==0x03FEu);
 assert(c.keyinput(1u<<3)==0x03FFu);
 assert(c.assign(1,0)); // B -> A, preserving GBA action B.
 assert(c.keyinput(1u<<0)==0x03FDu);
 assert(c.keyinput(1u<<1)==0x03FFu);
 c.defaults(); assert(c.assign(1,0)); // A already occupied: swap, no duplicate.
 assert(c.buttons[0]==1 && c.buttons[1]==0);
 assert(c.keyinput(1u<<0)==0x03FDu && c.keyinput(1u<<1)==0x03FEu);
 assert(!c.assign(0,sma3::Guide)); assert(!c.assign(-1,0));
 sma3::Capture capture;capture.begin(0);
 assert(!capture.accept(2,c)); // Opening press cannot be captured.
 capture.released();assert(capture.accept(2,c));assert(capture.action==-1);
 capture.begin(8);capture.released();assert(!capture.accept(sma3::Guide,c));
 capture.cancel();assert(capture.action==-1);
 capture.begin(8);capture.released();assert(capture.accept(15,c));
 assert((c.keyinput(1u<<15)&(1u<<8))==0);
 auto path=std::filesystem::current_path()/"controls-fixture.ini";
 assert(c.save(path.string()));sma3::Controls fresh;assert(fresh.load(path.string()));assert(c.buttons==fresh.buttons);
 {std::ofstream f(path);f<<"0\n0\n";}const auto before=fresh.buttons;assert(!fresh.load(path.string()));assert(fresh.buttons==before);
 std::filesystem::remove(path);fresh.defaults();assert(fresh.buttons==defaults);
 std::cout<<"PASS: capture/release/cancel, Y->X, B->A, swap uniqueness, triggers, persistence/reload, invalid config, defaults\n";
}
