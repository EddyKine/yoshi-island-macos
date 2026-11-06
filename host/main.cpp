#include "runtime.h"
int main(int argc,char** argv){
 gbarecomp::RunOptions options;
 options.builtin_game_name="Yoshi's Island: SMA3 (USA) - viability test";
 options.builtin_rom_sha1="7352d2bd064d9ebaec579e264228aa21c7345b80";
 options.diagnostic_replay_default=false;
 return gbarecomp::run_game(argc,argv,options);
}
