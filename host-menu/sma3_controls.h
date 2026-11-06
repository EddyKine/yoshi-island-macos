#pragma once
#include <array>
#include <cstdint>
#include <string>
namespace sma3 {
constexpr int Count=10, Guide=5;
class Controls {
public:
 std::array<int,Count> buttons{0,1,4,6,14,13,11,12,10,9};
 bool assign(int action,int button);
 uint16_t keyinput(uint32_t pressed) const;
 bool load(const std::string& path);
 bool save(const std::string& path) const;
 void defaults();
};
class Capture {
public:
 int action=-1; bool armed=false;
 void begin(int bit){action=bit;armed=false;}
 void released(){if(action>=0)armed=true;}
 void cancel(){action=-1;armed=false;}
 bool accept(int button,Controls& controls){if(!armed||action<0||!controls.assign(action,button))return false;cancel();return true;}
};
Controls& controls();
void load_controls();
void request_capture(int action);
int take_capture_request();
bool save_controls();
bool reset_controls();
const char* control_label(int action);
const char* button_name(int button);
}
