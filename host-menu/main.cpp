#include "runtime.h"
#include "recomp_runtime_ui.h"
#include "sma3_controls.h"
#include <array>
#include <cstring>
#include <map>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdio>
namespace {
std::map<std::string,int> settings;
const char* file="menu-profile/settings.ini";
bool allowed(const std::string& key){return key=="display.fullscreen" || key=="display.window_scale" || key=="graphics.linear_filter" || key=="audio.enabled" || key=="audio.volume" || key=="display.fps_readout";}
int get(const char* key,int* out){auto i=settings.find(key);if(i==settings.end())return 0;*out=i->second;return 1;}
int set(const char* key,int value){
 if(!allowed(key))return 0;
 settings[key]=value;
 std::filesystem::create_directories("menu-profile");
 std::string temp=std::string(file)+".tmp";
 {std::ofstream f(temp);for(auto& [k,v]:settings)f<<k<<'='<<v<<'\n';if(!f)return 0;}
 std::error_code ec;std::filesystem::rename(temp,file,ec);
 if(ec){std::fprintf(stderr,"settings save failed: %s\n",ec.message().c_str());return 0;}
 std::fprintf(stderr,"menu setting %s=%d persisted\n",key,value);return 1;
}
}
int main(int argc,char**argv){
 sma3::load_controls();
 std::array<RecompRuntimeUiItem,11> rows{};
 std::array<std::string,10> keys;
 for(int i=0;i<10;++i){keys[i]="pad."+std::to_string(i);auto& item=rows[i];item.key=keys[i].c_str();item.section="Controles";item.label=sma3::control_label(i);item.description="Selecciona y pulsa el boton fisico. Duplicados: intercambio. Esc/Guide cancela.";item.type=RECOMP_RUNTIME_UI_ACTION;}
 rows[10].key="pad.reset";rows[10].section="Controles";rows[10].label="Restaurar predeterminados";rows[10].description="Restaura solo las asignaciones del mando.";rows[10].type=RECOMP_RUNTIME_UI_ACTION;
 std::ifstream f(file);std::string line;
 while(std::getline(f,line)){auto pos=line.find('=');if(pos==std::string::npos)continue;auto key=line.substr(0,pos);if(!allowed(key))continue;try{settings[key]=std::stoi(line.substr(pos+1));}catch(...){} }
 gbarecomp::RunOptions options;
 options.builtin_game_name="Yoshi SMA3 - Ajustes";
 options.builtin_rom_sha1="7352d2bd064d9ebaec579e264228aa21c7345b80";
 options.diagnostic_replay_default=false;
 options.ui_get=get;options.ui_set=set;
 options.ui_extra_items=rows.data();options.ui_extra_item_count=rows.size();
 options.ui_action=[](const char* key)->int{
  if(!std::strcmp(key,"pad.reset")){bool ok=sma3::reset_controls();for(int i=0;i<10;++i)sma3::control_label(i);return ok;}
  if(!std::strncmp(key,"pad.",4)){try{sma3::request_capture(std::stoi(key+4));return 1;}catch(...){return 0;}}return 0;
 };
 return gbarecomp::run_game(argc,argv,options);
}
