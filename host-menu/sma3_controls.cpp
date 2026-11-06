#include "sma3_controls.h"
#include <filesystem>
#include <fstream>
#include <cstdio>
#include <set>
namespace sma3 {
namespace { Controls current; int request=-1; char labels[Count][96]; const char* path="menu-profile/controller.ini";
const char* actions[Count]={"GBA A","GBA B","GBA Select","GBA Start","GBA Derecha","GBA Izquierda","GBA Arriba","GBA Abajo","GBA R","GBA L"};
bool valid(int b){return b>=0 && b<=16 && b!=Guide;}
}
uint16_t Controls::keyinput(uint32_t pressed) const {uint16_t keys=0x03FFu;for(int i=0;i<Count;++i)if(pressed&(1u<<buttons[i]))keys&=uint16_t(~(1u<<i));return keys;}
void Controls::defaults(){buttons={0,1,4,6,14,13,11,12,10,9};}
bool Controls::assign(int a,int b){
 if(a<0||a>=Count||!valid(b))return false;
 int old=buttons[a];for(int i=0;i<Count;++i)if(i!=a&&buttons[i]==b){buttons[i]=old;break;}
 buttons[a]=b;return true;
}
bool Controls::load(const std::string& p){std::ifstream f(p);std::array<int,Count> next;std::set<int> used;for(auto& b:next)if(!(f>>b)||!valid(b)||!used.insert(b).second)return false;buttons=next;return true;}
bool Controls::save(const std::string& p)const{
 auto temp=p+".tmp";{std::ofstream f(temp);for(int b:buttons)f<<b<<'\n';if(!f)return false;}
 std::error_code ec;std::filesystem::rename(temp,p,ec);return !ec;
}
Controls& controls(){return current;}
void load_controls(){current.load(path);}
void request_capture(int a){if(a>=0&&a<Count)request=a;}
int take_capture_request(){int a=request;request=-1;return a;}
bool save_controls(){std::filesystem::create_directories("menu-profile");return current.save(path);}
bool reset_controls(){current.defaults();return save_controls();}
const char* button_name(int b){static const char* names[]={"Xbox A","Xbox B","Xbox X","Xbox Y","Back","Guide (reservado)","Start","Stick L","Stick R","LB","RB","Cruceta Arriba","Cruceta Abajo","Cruceta Izquierda","Cruceta Derecha","LT","RT"};return b>=0&&b<=16?names[b]:"Sin asignar";}
const char* control_label(int a){if(a<0||a>=Count)return "";std::snprintf(labels[a],sizeof(labels[a]),"%s: %s",actions[a],button_name(current.buttons[a]));return labels[a];}
}
