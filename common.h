//common.h
#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "debug.h"

using std::cout;
using std::endl;
using std::string;

enum AppState { quit=0, intro, menu, preRun, running, stopped, paused, hidden };

class Application;
class Controls;
class GraphicsSdl;
class Game;
class TimeCount;

#endif
