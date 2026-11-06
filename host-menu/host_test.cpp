#include "host_window.h"
#include "recomp_runtime_ui.h"
#include "sma3_controls.h"
#include <SDL.h>
#include <cassert>
#include <filesystem>
#include <iostream>
void key(gbarecomp::HostWindow& win,SDL_Keycode code){SDL_Event e{};e.type=SDL_KEYDOWN;e.key.keysym.sym=code;e.key.keysym.scancode=SDL_GetScancodeFromKey(code);SDL_PushEvent(&e);win.pump();e.type=SDL_KEYUP;SDL_PushEvent(&e);win.pump();}
int main(){
 auto dir=std::filesystem::current_path()/"host-fixture";std::filesystem::create_directories(dir);std::filesystem::current_path(dir);
 gbarecomp::HostWindow win;assert(win.open());
 assert(win.audio_enabled());win.set_menu_paused(true);assert(win.audio_enabled());
 win.set_audio_enabled(false);win.set_menu_paused(false);assert(!win.audio_enabled());
 int16_t samples[64]={};win.push_audio_block(samples,64,65536);assert(!win.audio_enabled());
 win.set_audio_enabled(true);assert(win.audio_enabled());
 RecompRuntimeUiStandardConfig cfg{};cfg.menu.title="Test";cfg.features=RECOMP_RUNTIME_UI_STANDARD_RESUME;auto* ui=recomp_runtime_ui_create_standard(&cfg);assert(ui);win.set_runtime_ui(ui);
 int index=SDL_JoystickAttachVirtual(SDL_JOYSTICK_TYPE_GAMECONTROLLER,6,15,0);assert(index>=0);SDL_Joystick* pad=SDL_JoystickOpen(index);assert(pad);SDL_JoystickUpdate();win.pump();
 key(win,SDLK_ESCAPE);assert(recomp_runtime_ui_is_open(ui));assert(win.pump().keyinput==0x03FF);
 sma3::request_capture(0);win.pump();
 SDL_JoystickSetVirtualButton(pad,SDL_CONTROLLER_BUTTON_X,1);SDL_JoystickUpdate();auto event=win.pump();
 assert(sma3::controls().buttons[0]==SDL_CONTROLLER_BUTTON_X);assert(event.keyinput==0x03FF);
 SDL_JoystickSetVirtualButton(pad,SDL_CONTROLLER_BUTTON_X,0);SDL_JoystickUpdate();win.pump();
 key(win,SDLK_ESCAPE);assert(!recomp_runtime_ui_is_open(ui));win.pump();
 SDL_JoystickSetVirtualButton(pad,SDL_CONTROLLER_BUTTON_X,1);SDL_JoystickUpdate();assert(win.pump().keyinput==0x03FE);
 SDL_JoystickSetVirtualButton(pad,SDL_CONTROLLER_BUTTON_X,0);SDL_JoystickUpdate();assert(win.pump().keyinput==0x03FF);
 // Reserved chord works regardless of gameplay bindings.
 SDL_JoystickSetVirtualButton(pad,SDL_CONTROLLER_BUTTON_BACK,1);SDL_JoystickSetVirtualButton(pad,SDL_CONTROLLER_BUTTON_START,1);SDL_JoystickUpdate();assert(win.pump().keyinput==0x03FF);assert(recomp_runtime_ui_is_open(ui));
 SDL_JoystickSetVirtualButton(pad,SDL_CONTROLLER_BUTTON_BACK,0);SDL_JoystickSetVirtualButton(pad,SDL_CONTROLLER_BUTTON_START,0);SDL_JoystickUpdate();win.pump();
 key(win,SDLK_ESCAPE);assert(!recomp_runtime_ui_is_open(ui));assert(win.pump().keyinput==0x03FF);
 sma3::Controls fresh;assert(fresh.load("menu-profile/controller.ini"));assert(fresh.buttons[0]==SDL_CONTROLLER_BUTTON_X);
 win.set_runtime_ui(nullptr);recomp_runtime_ui_destroy(ui);SDL_JoystickClose(pad);SDL_JoystickDetachVirtual(index);win.close();
 std::cout<<"PASS: SDL virtual capture, menu neutrality, release/resume, X mapping, reserved chord, reload\n";
}
