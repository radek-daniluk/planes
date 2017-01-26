//common.h
#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

//using std::cout;
//using std::endl;

enum AppState { quit=0, intro, menu, preRun, running, stopped, paused, hidden };

class Application;
class Controls;
class GraphicsSdl;
class Game;
class TimeCount;

#endif
