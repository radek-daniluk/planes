//controls.cpp

#include<SDL2/SDL_events.h>
#include<thread>
#include<chrono>
#include "controls.h"
#include "game.h"
#include "application.h"

Controls::Controls() {
	keys = SDL_GetKeyboardState(NULL);
	set_event_states();
}

Controls::~Controls() {}

void Controls::gameEventLoop( Application & app, Game & game ) {

	while( SDL_PollEvent( &event ) ) {
		DPR( print_event(event) );

		basic_events( event, app );
		if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ) {
				app.state( paused );
		}
		if( event.type == SDL_WINDOWEVENT )
			switch( event.window.event ) {
			case SDL_WINDOWEVENT_HIDDEN: app.state( hidden ); break;
			case SDL_WINDOWEVENT_SHOWN: app.state( paused ); break;
		}
	}
	game_controls( game );
}

bool Controls::pauseEventLoop( Application & app, int sleep_time ) {
	std::this_thread::sleep_for( std::chrono::milliseconds( sleep_time ) );

	bool redraw = false;

	while( SDL_PollEvent( &event ) ) {
		DPR( print_event(event) );
		basic_events( event, app );
		redraw = pause_events( event, app );
	}
	return redraw;
}

void Controls::hiddenEventLoop( Application & app, int sleep_time ) {
	std::this_thread::sleep_for( std::chrono::milliseconds( sleep_time ) );

	while( SDL_PollEvent( &event ) ) {
		basic_events( event, app );
		hidden_events( event, app );
	}
}

void Controls::basic_events( SDL_Event & event, Application & app ) {

	if( event.type == SDL_QUIT )
		app.state( quit );
	// TODO add OS events
}

void Controls::hidden_events( SDL_Event & event, Application & app ) {
	if( event.type == SDL_WINDOWEVENT )
		if( event.window.event == SDL_WINDOWEVENT_SHOWN )
			app.state( paused );
}

bool Controls::pause_events( SDL_Event & event, Application & app ) {
	bool toRedraw = false;
	if( event.type == SDL_WINDOWEVENT ) {
		if( event.window.event == SDL_WINDOWEVENT_HIDDEN ) {
			app.state( hidden ); }
		else if( event.window.event == SDL_WINDOWEVENT_EXPOSED ) {
			toRedraw = true; }
	}
	else if( event.type == SDL_KEYDOWN ) {
		if( event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_n ) {
			app.state( running ); }
		else if( event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_t ||
				event.key.keysym.sym == SDLK_y ) {
			app.state( quit ); }
	}
	return toRedraw;
}

void Controls::game_controls( Game & game ) {
	auto & p = game.nonConstPlane();

	// manage x axis movement
	if( keys[ SDL_GetScancodeFromKey( SDLK_LEFT ) ] ) {
		game.accelPlane( -1000, 0 );
	}else if( keys[ SDL_GetScancodeFromKey( SDLK_RIGHT ) ] ) {
		game.accelPlane( 1000, 0 );
	}else { // gradually increase or decrease speed to 0
		if( p.speedX() < -1000 )
			game.accelPlane( 1000, 0 );
		else if( p.speedX() > 1000 )
			game.accelPlane( -1000 ,0 );
		else
			p.stopX();
	}

	// manage y axis movement
	if( keys[ SDL_GetScancodeFromKey( SDLK_UP ) ] ) {
		game.accelPlane( 0, 700 );
	}else if( keys[ SDL_GetScancodeFromKey( SDLK_DOWN ) ] ) {
		game.accelPlane( 0, -500 );
	}

	if( keys[ SDL_GetScancodeFromKey( SDLK_SPACE ) ] )
		game.addBullet();
}

void Controls::set_event_states() {
	//SDL 2.0.4 events
//							SDL_EventType			enable=1,ignore=0      default state

//	SDL_EventState(	SDL_QUIT,							0  );//			1
//	SDL_EventState(	SDL_APP_TERMINATING,				0  );//			1
//	SDL_EventState(	SDL_APP_LOWMEMORY,				0  );//			1
//	SDL_EventState(	SDL_APP_WILLENTERBACKGROUND,	0  );//			1
//	SDL_EventState(	SDL_APP_DIDENTERBACKGROUND,	0  );//			1
//	SDL_EventState(	SDL_APP_WILLENTERFOREGROUND,	0  );//			1
//	SDL_EventState(	SDL_APP_DIDENTERFOREGROUND,	0  );//			1
//	SDL_EventState(	SDL_WINDOWEVENT,					0  );//			1
//	SDL_EventState(	SDL_SYSWMEVENT,					0  );//			0
//	SDL_EventState(	SDL_KEYDOWN,						0  );//			1
	SDL_EventState(	SDL_KEYUP,							0  );//			1
	SDL_EventState(	SDL_TEXTEDITING,					0  );//			1
	SDL_EventState(	SDL_TEXTINPUT,						0  );//			1
	SDL_EventState(	SDL_KEYMAPCHANGED,				0  );//			1
	SDL_EventState(	SDL_MOUSEMOTION,					0  );//			1
	SDL_EventState(	SDL_MOUSEBUTTONDOWN,				0  );//			1
	SDL_EventState(	SDL_MOUSEBUTTONUP,				0  );//			1
	SDL_EventState(	SDL_MOUSEWHEEL,					0  );//			1
	SDL_EventState(	SDL_JOYAXISMOTION,				0  );//			1
	SDL_EventState(	SDL_JOYBALLMOTION,				0  );//			1
	SDL_EventState(	SDL_JOYHATMOTION,					0  );//			1
	SDL_EventState(	SDL_JOYBUTTONDOWN,				0  );//			1
	SDL_EventState(	SDL_JOYBUTTONUP,					0  );//			1
	SDL_EventState(	SDL_JOYDEVICEADDED,				0  );//			1
	SDL_EventState(	SDL_JOYDEVICEREMOVED,			0  );//			1
	SDL_EventState(	SDL_CONTROLLERAXISMOTION,		0  );//			1
	SDL_EventState(	SDL_CONTROLLERBUTTONDOWN,		0  );//			1
	SDL_EventState(	SDL_CONTROLLERBUTTONUP,			0  );//			1
	SDL_EventState(	SDL_CONTROLLERDEVICEADDED,		0  );//			1
	SDL_EventState(	SDL_CONTROLLERDEVICEREMOVED,	0  );//			1
	SDL_EventState(	SDL_CONTROLLERDEVICEREMAPPED,	0  );//			1
	SDL_EventState(	SDL_FINGERDOWN,					0  );//			1
	SDL_EventState(	SDL_FINGERUP,						0  );//			1
	SDL_EventState(	SDL_FINGERMOTION,					0  );//			1
	SDL_EventState(	SDL_DOLLARGESTURE,				0  );//			1
	SDL_EventState(	SDL_DOLLARRECORD,					0  );//			1
	SDL_EventState(	SDL_MULTIGESTURE,					0  );//			1
	SDL_EventState(	SDL_CLIPBOARDUPDATE,				0  );//			1
	SDL_EventState(	SDL_DROPFILE,						0  );//			1
//	SDL_EventState(	SDL_AUDIODEVICEADDED,			0  );//			1
//	SDL_EventState(	SDL_AUDIODEVICEREMOVED,			0  );//			1
//	SDL_EventState(	SDL_RENDER_TARGETS_RESET,		0  );//			1
//	SDL_EventState(	SDL_RENDER_DEVICE_RESET,		0  );//			1
}

string Controls::print_event( const SDL_Event& e ) {
	std::stringstream s;
	//SDL_Event* = nullptr;
	switch( e.type ) {
	case SDL_QUIT: s<<"SDL_QUIT"; break;
	case SDL_APP_TERMINATING: s<<"SDL_APP_TERMINATING"; break;
	case SDL_APP_LOWMEMORY: s<<"SDL_APP_LOWMEMORY"; break;
	case SDL_APP_WILLENTERBACKGROUND: s<<"SDL_APP_WILLENTERBACKGROUND"; break;
	case SDL_APP_DIDENTERBACKGROUND: s<<"SDL_APP_DIDENTERBACKGROUND"; break;
	case SDL_APP_WILLENTERFOREGROUND: s<<"SDL_APP_WILLENTERFOREGROUND"; break;
	case SDL_APP_DIDENTERFOREGROUND: s<<"SDL_APP_DIDENTERFOREGROUND"; break;
	case SDL_WINDOWEVENT: s<< print_win_event(e); break;
	case SDL_SYSWMEVENT: s<<"SDL_SYSWMEVENT"; break;
	case SDL_KEYDOWN: s<< print_key_event(e); break;
	case SDL_KEYUP: s<<"SDL_KEYUP:"; print_key_event(e); break;
	case SDL_TEXTEDITING: s<<"SDL_TEXTEDITING"; break;
	case SDL_TEXTINPUT: s<<"SDL_TEXTINPUT"; break;
	case SDL_KEYMAPCHANGED: s<<"SDL_KEYMAPCHANGED"; break;
	case SDL_MOUSEMOTION: s<<"SDL_MOUSEMOTION"; break;
	case SDL_MOUSEBUTTONDOWN: s<<"SDL_MOUSEBUTTONDOWN"; break;
	case SDL_MOUSEBUTTONUP: s<<"SDL_MOUSEBUTTONUP"; break;
	case SDL_MOUSEWHEEL: s<<"SDL_MOUSEWHEEL"; break;
	case SDL_JOYAXISMOTION: s<<"SDL_JOYAXISMOTION"; break;
	case SDL_JOYBALLMOTION: s<<"SDL_JOYBALLMOTION"; break;
	case SDL_JOYHATMOTION: s<<"SDL_JOYHATMOTION"; break;
	case SDL_JOYBUTTONDOWN: s<<"SDL_JOYBUTTONDOWN"; break;
	case SDL_JOYBUTTONUP: s<<"SDL_JOYBUTTONUP"; break;
	case SDL_JOYDEVICEADDED: s<<"SDL_JOYDEVICEADDED"; break;
	case SDL_JOYDEVICEREMOVED: s<<"SDL_JOYDEVICEREMOVED"; break;
	case SDL_CONTROLLERAXISMOTION: s<<"SDL_CONTROLLERAXISMOTION"; break;
	case SDL_CONTROLLERBUTTONDOWN: s<<"SDL_CONTROLLERBUTTONDOWN"; break;
	case SDL_CONTROLLERBUTTONUP: s<<"SDL_CONTROLLERBUTTONUP"; break;
	case SDL_CONTROLLERDEVICEADDED: s<<"SDL_CONTROLLERDEVICEADDED"; break;
	case SDL_CONTROLLERDEVICEREMOVED: s<<"SDL_CONTROLLERDEVICEREMOVED"; break;
	case SDL_CONTROLLERDEVICEREMAPPED: s<<"SDL_CONTROLLERDEVICEREMAPPED"; break;
	case SDL_FINGERDOWN: s<<"SDL_FINGERDOWN"; break;
	case SDL_FINGERUP: s<<"SDL_FINGERUP"; break;
	case SDL_FINGERMOTION: s<<"SDL_FINGERMOTION"; break;
	case SDL_DOLLARGESTURE: s<<"SDL_DOLLARGESTURE"; break;
	case SDL_DOLLARRECORD: s<<"SDL_DOLLARRECORD"; break;
	case SDL_MULTIGESTURE: s<<"SDL_MULTIGESTURE"; break;
	case SDL_CLIPBOARDUPDATE: s<<"SDL_CLIPBOARDUPDATE"; break;
	case SDL_DROPFILE: s<<"SDL_DROPFILE"; break;
	case SDL_AUDIODEVICEADDED: s<<"SDL_AUDIODEVICEADDED"; break;
	case SDL_AUDIODEVICEREMOVED: s<<"SDL_AUDIODEVICEREMOVED"; break;
	case SDL_RENDER_TARGETS_RESET: s<<"SDL_RENDER_TARGETS_RESET"; break;
	case SDL_RENDER_DEVICE_RESET: s<<"SDL_RENDER_DEVICE_RESET"; break;
	default: s<<"not known SDL2.0.4 event type";
	}
	return s.str();
}

string Controls::print_win_event( const SDL_Event& e ) {
	switch( e.window.event ) {
	case SDL_WINDOWEVENT_SHOWN: return "SDL_WINDOWEVENT_SHOWN";
	case SDL_WINDOWEVENT_HIDDEN: return "SDL_WINDOWEVENT_HIDDEN";
	case SDL_WINDOWEVENT_EXPOSED: return "SDL_WINDOWEVENT_EXPOSED";
	case SDL_WINDOWEVENT_MOVED: return "SDL_WINDOWEVENT_MOVED";
	case SDL_WINDOWEVENT_RESIZED: return "SDL_WINDOWEVENT_RESIZED";
	case SDL_WINDOWEVENT_SIZE_CHANGED: return "SDL_WINDOWEVENT_SIZE_CHANGED";
	case SDL_WINDOWEVENT_MINIMIZED: return "SDL_WINDOWEVENT_MINIMIZED";
	case SDL_WINDOWEVENT_MAXIMIZED: return "SDL_WINDOWEVENT_MAXIMIZED";
	case SDL_WINDOWEVENT_RESTORED: return "SDL_WINDOWEVENT_RESTORED";
	case SDL_WINDOWEVENT_ENTER: return "SDL_WINDOWEVENT_ENTER";
	case SDL_WINDOWEVENT_LEAVE: return "SDL_WINDOWEVENT_LEAVE";
	case SDL_WINDOWEVENT_FOCUS_GAINED: return "SDL_WINDOWEVENT_FOCUS_GAINED";
	case SDL_WINDOWEVENT_FOCUS_LOST: return "SDL_WINDOWEVENT_FOCUS_LOST";
	case SDL_WINDOWEVENT_CLOSE: return "SDL_WINDOWEVENT_CLOSE";
	default: return "not known SDL2.0.4 window event";
	}
	ASSERT(true);
	return "";
}

string Controls::print_key_event( const SDL_Event& e ) {
	std::stringstream s;
	s<<"scan:"<<print_key_scancode(e)<<"\tsym:"<<print_key_sym(e)<<"\trpt:"
		<<(int)e.key.repeat;
	return s.str();
}

string Controls::print_key_scancode( const SDL_Event& e ) {
	switch( e.key.keysym.scancode ) {
	case 0x000: return "UNKNOWN";
	case 0x004: return "A";
	case 0x005: return "B";
	case 0x006: return "C";
	case 0x007: return "D";
	case 0x008: return "E";
	case 0x009: return "F";
	case 0x00A: return "G";
	case 0x00B: return "H";
	case 0x00C: return "I";
	case 0x00D: return "J";
	case 0x00E: return "K";
	case 0x00F: return "L";
	case 0x010: return "M";
	case 0x011: return "N";
	case 0x012: return "O";
	case 0x013: return "P";
	case 0x014: return "Q";
	case 0x015: return "R";
	case 0x016: return "S";
	case 0x017: return "T";
	case 0x018: return "U";
	case 0x019: return "V";
	case 0x01A: return "W";
	case 0x01B: return "X";
	case 0x01C: return "Y";
	case 0x01D: return "Z";
	case 0x01E: return "1";
	case 0x01F: return "2";
	case 0x020: return "3";
	case 0x021: return "4";
	case 0x022: return "5";
	case 0x023: return "6";
	case 0x024: return "7";
	case 0x025: return "8";
	case 0x026: return "9";
	case 0x027: return "0";
	case 0x028: return "RETURN";
	case 0x029: return "ESCAPE";
	case 0x02A: return "BACKSPACE";
	case 0x02B: return "TAB";
	case 0x02C: return "SPACE";
	case 0x02D: return "MINUS";
	case 0x02E: return "EQUALS";
	case 0x02F: return "LEFTBRACKET";
	case 0x030: return "RIGHTBRACKET";
	case 0x031: return "BACKSLASH";
	case 0x032: return "NONUSHASH";
	case 0x033: return "SEMICOLON";
	case 0x034: return "APOSTROPHE";
	case 0x035: return "GRAVE";
	case 0x036: return "COMMA";
	case 0x037: return "PERIOD";
	case 0x038: return "SLASH";
	case 0x039: return "CAPSLOCK";
	case 0x03A: return "F1";
	case 0x03B: return "F2";
	case 0x03C: return "F3";
	case 0x03D: return "F4";
	case 0x03E: return "F5";
	case 0x03F: return "F6";
	case 0x040: return "F7";
	case 0x041: return "F8";
	case 0x042: return "F9";
	case 0x043: return "F10";
	case 0x044: return "F11";
	case 0x045: return "F12";
	case 0x046: return "PRINTSCREEN";
	case 0x047: return "SCROLLLOCK";
	case 0x048: return "PAUSE";
	case 0x049: return "INSERT";
	case 0x04A: return "HOME";
	case 0x04B: return "PAGEUP";
	case 0x04C: return "DELETE";
	case 0x04D: return "END";
	case 0x04E: return "PAGEDOWN";
	case 0x04F: return "RIGHT";
	case 0x050: return "LEFT";
	case 0x051: return "DOWN";
	case 0x052: return "UP";
	case 0x053: return "NUMLOCKCLEAR";
	case 0x054: return "KP_DIVIDE";
	case 0x055: return "KP_MULTIPLY";
	case 0x056: return "KP_MINUS";
	case 0x057: return "KP_PLUS";
	case 0x058: return "KP_ENTER";
	case 0x059: return "KP_1";
	case 0x05A: return "KP_2";
	case 0x05B: return "KP_3";
	case 0x05C: return "KP_4";
	case 0x05D: return "KP_5";
	case 0x05E: return "KP_6";
	case 0x05F: return "KP_7";
	case 0x060: return "KP_8";
	case 0x061: return "KP_9";
	case 0x062: return "KP_0";
	case 0x063: return "KP_PERIOD";
	case 0x064: return "NONUSBACKSLASH";
	case 0x065: return "APPLICATION";
	case 0x066: return "POWER";
	case 0x067: return "KP_EQUALS";
	case 0x068: return "F13";
	case 0x069: return "F14";
	case 0x06A: return "F15";
	case 0x06B: return "F16";
	case 0x06C: return "F17";
	case 0x06D: return "F18";
	case 0x06E: return "F19";
	case 0x06F: return "F20";
	case 0x070: return "F21";
	case 0x071: return "F22";
	case 0x072: return "F23";
	case 0x073: return "F24";
	case 0x074: return "EXECUTE";
	case 0x075: return "HELP";
	case 0x076: return "MENU";
	case 0x077: return "SELECT";
	case 0x078: return "STOP";
	case 0x079: return "AGAIN";
	case 0x07A: return "UNDO";
	case 0x07B: return "CUT";
	case 0x07C: return "COPY";
	case 0x07D: return "PASTE";
	case 0x07E: return "FIND";
	case 0x07F: return "MUTE";
	case 0x080: return "VOLUMEUP";
	case 0x081: return "VOLUMEDOWN";
	case 0x085: return "KP_COMMA";
	case 0x086: return "KP_EQUALSAS400";
	case 0x087: return "INTERNATIONAL1";
	case 0x088: return "INTERNATIONAL2";
	case 0x089: return "INTERNATIONAL3";
	case 0x08A: return "INTERNATIONAL4";
	case 0x08B: return "INTERNATIONAL5";
	case 0x08C: return "INTERNATIONAL6";
	case 0x08D: return "INTERNATIONAL7";
	case 0x08E: return "INTERNATIONAL8";
	case 0x08F: return "INTERNATIONAL9";
	case 0x090: return "LANG1";
	case 0x091: return "LANG2";
	case 0x092: return "LANG3";
	case 0x093: return "LANG4";
	case 0x094: return "LANG5";
	case 0x095: return "LANG6";
	case 0x096: return "LANG7";
	case 0x097: return "LANG8";
	case 0x098: return "LANG9";
	case 0x099: return "ALTERASE";
	case 0x09A: return "SYSREQ";
	case 0x09B: return "CANCEL";
	case 0x09C: return "CLEAR";
	case 0x09D: return "PRIOR";
	case 0x09E: return "RETURN2";
	case 0x09F: return "SEPARATOR";
	case 0x0A0: return "OUT";
	case 0x0A1: return "OPER";
	case 0x0A2: return "CLEARAGAIN";
	case 0x0A3: return "CRSEL";
	case 0x0A4: return "EXSEL";
	case 0x0B0: return "KP_00";
	case 0x0B1: return "KP_000";
	case 0x0B2: return "THOUSANDSSEPARATOR";
	case 0x0B3: return "DECIMALSEPARATOR";
	case 0x0B4: return "CURRENCYUNIT";
	case 0x0B5: return "CURRENCYSUBUNIT";
	case 0x0B6: return "KP_LEFTPAREN";
	case 0x0B7: return "KP_RIGHTPAREN";
	case 0x0B8: return "KP_LEFTBRACE";
	case 0x0B9: return "KP_RIGHTBRACE";
	case 0x0BA: return "KP_TAB";
	case 0x0BB: return "KP_BACKSPACE";
	case 0x0BC: return "KP_A";
	case 0x0BD: return "KP_B";
	case 0x0BE: return "KP_C";
	case 0x0BF: return "KP_D";
	case 0x0C0: return "KP_E";
	case 0x0C1: return "KP_F";
	case 0x0C2: return "KP_XOR";
	case 0x0C3: return "KP_POWER";
	case 0x0C4: return "KP_PERCENT";
	case 0x0C5: return "KP_LESS";
	case 0x0C6: return "KP_GREATER";
	case 0x0C7: return "KP_AMPERSAND";
	case 0x0C8: return "KP_DBLAMPERSAND";
	case 0x0C9: return "KP_VERTICALBAR";
	case 0x0CA: return "KP_DBLVERTICALBAR";
	case 0x0CB: return "KP_COLON";
	case 0x0CC: return "KP_HASH";
	case 0x0CD: return "KP_SPACE";
	case 0x0CE: return "KP_AT";
	case 0x0CF: return "KP_EXCLAM";
	case 0x0D0: return "KP_MEMSTORE";
	case 0x0D1: return "KP_MEMRECALL";
	case 0x0D2: return "KP_MEMCLEAR";
	case 0x0D3: return "KP_MEMADD";
	case 0x0D4: return "KP_MEMSUBTRACT";
	case 0x0D5: return "KP_MEMMULTIPLY";
	case 0x0D6: return "KP_MEMDIVIDE";
	case 0x0D7: return "KP_PLUSMINUS";
	case 0x0D8: return "KP_CLEAR";
	case 0x0D9: return "KP_CLEARENTRY";
	case 0x0DA: return "KP_BINARY";
	case 0x0DB: return "KP_OCTAL";
	case 0x0DC: return "KP_DECIMAL";
	case 0x0DD: return "KP_HEXADECIMAL";
	case 0x0E0: return "LCTRL";
	case 0x0E1: return "LSHIFT";
	case 0x0E2: return "LALT";
	case 0x0E3: return "LGUI";
	case 0x0E4: return "RCTRL";
	case 0x0E5: return "RSHIFT";
	case 0x0E6: return "RALT";
	case 0x0E7: return "RGUI";
	case 0x101: return "MODE";
	case 0x102: return "AUDIONEXT";
	case 0x103: return "AUDIOPREV";
	case 0x104: return "AUDIOSTOP";
	case 0x105: return "AUDIOPLAY";
	case 0x106: return "AUDIOMUTE";
	case 0x107: return "MEDIASELECT";
	case 0x108: return "WWW";
	case 0x109: return "MAIL";
	case 0x10A: return "CALCULATOR";
	case 0x10B: return "COMPUTER";
	case 0x10C: return "AC_SEARCH";
	case 0x10D: return "AC_HOME";
	case 0x10E: return "AC_BACK";
	case 0x10F: return "AC_FORWARD";
	case 0x110: return "AC_STOP";
	case 0x111: return "AC_REFRESH";
	case 0x112: return "AC_BOOKMARKS";
	case 0x113: return "BRIGHTNESSDOWN";
	case 0x114: return "BRIGHTNESSUP";
	case 0x115: return "DISPLAYSWITCH";
	case 0x116: return "KBDILLUMTOGGLE";
	case 0x117: return "KBDILLUMDOWN";
	case 0x118: return "KBDILLUMUP";
	case 0x119: return "EJECT";
	case 0x11A: return "SLEEP";
	case 0x11B: return "APP1";
	case 0x11C: return "APP2";
	default: return "not known SDL2.0.5 scancode!";
	}
}


string Controls::print_key_sym( const SDL_Event& e ) {
	switch( e.key.keysym.sym ) {
	case 0x00: return "SDLK_UNKNOWN('\\0')";
	case 0x08: return "SDLK_BACKSPACE";
	case 0x09: return "SDLK_TAB";
	case 0x0D: return "SDLK_RETURN";
	case 0x1B: return "SDLK_ESCAPE";
	case 0x20: return "SDLK_SPACE (' ')";
	case 0x21: return "SDLK_EXCLAIM ('!')";
	case 0x22: return "SDLK_QUOTEDBL ('\"')";
	case 0x23: return "SDLK_HASH ('#')";
	case 0x24: return "SDLK_DOLLAR ('$')";
	case 0x25: return "SDLK_PERCENT ('%')";
	case 0x26: return "SDLK_AMPERSAND ('&')";
	case 0x27: return "SDLK_QUOTE(''')";
	case 0x28: return "SDLK_LEFTPAREN ('(')";
	case 0x29: return "SDLK_RIGHTPAREN (')')";
	case 0x2A: return "SDLK_ASTERISK ('*')";
	case 0x2B: return "SDLK_PLUS ('+')";
	case 0x2C: return "SDLK_COMMA (',')";
	case 0x2D: return "SDLK_MINUS ('-')";
	case 0x2E: return "SDLK_PERIOD ('.')";
	case 0x2F: return "SDLK_SLASH ('/')";
	case 0x30: return "SDLK_0 ('0')";
	case 0x31: return "SDLK_1 ('1')";
	case 0x32: return "SDLK_2 ('2')";
	case 0x33: return "SDLK_3 ('3')";
	case 0x34: return "SDLK_4 ('4')";
	case 0x35: return "SDLK_5 ('5')";
	case 0x36: return "SDLK_6 ('6')";
	case 0x37: return "SDLK_7 ('7')";
	case 0x38: return "SDLK_8 ('8')";
	case 0x39: return "SDLK_9 ('9')";
	case 0x3A: return "SDLK_COLON (':')";
	case 0x3B: return "SDLK_SEMICOLON (';')";
	case 0x3C: return "SDLK_LESS ('<')";
	case 0x3D: return "SDLK_EQUALS ('=')";
	case 0x3E: return "SDLK_GREATER ('>')";
	case 0x3F: return "SDLK_QUESTION ('?')";
	case 0x40: return "SDLK_AT ('@')";
	case 0x5B: return "SDLK_LEFTBRACKET ('[')";
	case 0x5C: return "SDLK_BACKSLASH('\\')";
	case 0x5D: return "SDLK_RIGHTBRACKET (']')";
	case 0x5E: return "SDLK_CARET ('^')";
	case 0x5F: return "SDLK_UNDERSCORE ('_')";
	case 0x60: return "SDLK_BACKQUOTE ('`')";
	case 0x61: return "SDLK_a ('a')";
	case 0x62: return "SDLK_b ('b')";
	case 0x63: return "SDLK_c ('c')";
	case 0x64: return "SDLK_d ('d')";
	case 0x65: return "SDLK_e ('e')";
	case 0x66: return "SDLK_f ('f')";
	case 0x67: return "SDLK_g ('g')";
	case 0x68: return "SDLK_h ('h')";
	case 0x69: return "SDLK_i ('i')";
	case 0x6A: return "SDLK_j ('j')";
	case 0x6B: return "SDLK_k ('k')";
	case 0x6C: return "SDLK_l ('l')";
	case 0x6D: return "SDLK_m ('m')";
	case 0x6E: return "SDLK_n ('n')";
	case 0x6F: return "SDLK_o ('o')";
	case 0x70: return "SDLK_p ('p')";
	case 0x71: return "SDLK_q ('q')";
	case 0x72: return "SDLK_r ('r')";
	case 0x73: return "SDLK_s ('s')";
	case 0x74: return "SDLK_t ('t')";
	case 0x75: return "SDLK_u ('u')";
	case 0x76: return "SDLK_v ('v')";
	case 0x77: return "SDLK_w ('w')";
	case 0x78: return "SDLK_x ('x')";
	case 0x79: return "SDLK_y ('y')";
	case 0x7A: return "SDLK_z ('z')";
	case 0x7F: return "SDLK_DELETE";
	case 0x40000039: return "SDLK_CAPSLOCK";
	case 0x4000003A: return "SDLK_F1";
	case 0x4000003B: return "SDLK_F2";
	case 0x4000003C: return "SDLK_F3";
	case 0x4000003D: return "SDLK_F4";
	case 0x4000003E: return "SDLK_F5";
	case 0x4000003F: return "SDLK_F6";
	case 0x40000040: return "SDLK_F7";
	case 0x40000041: return "SDLK_F8";
	case 0x40000042: return "SDLK_F9";
	case 0x40000043: return "SDLK_F10";
	case 0x40000044: return "SDLK_F11";
	case 0x40000045: return "SDLK_F12";
	case 0x40000046: return "SDLK_PRINTSCREEN";
	case 0x40000047: return "SDLK_SCROLLLOCK";
	case 0x40000048: return "SDLK_PAUSE";
	case 0x40000049: return "SDLK_INSERT";
	case 0x4000004A: return "SDLK_HOME";
	case 0x4000004B: return "SDLK_PAGEUP";
	case 0x4000004D: return "SDLK_END";
	case 0x4000004E: return "SDLK_PAGEDOWN";
	case 0x4000004F: return "SDLK_RIGHT";
	case 0x40000050: return "SDLK_LEFT";
	case 0x40000051: return "SDLK_DOWN";
	case 0x40000052: return "SDLK_UP";
	case 0x40000053: return "SDLK_NUMLOCKCLEAR";
	case 0x40000054: return "SDLK_KP_DIVIDE";
	case 0x40000055: return "SDLK_KP_MULTIPLY";
	case 0x40000056: return "SDLK_KP_MINUS";
	case 0x40000057: return "SDLK_KP_PLUS";
	case 0x40000058: return "SDLK_KP_ENTER";
	case 0x40000059: return "SDLK_KP_1";
	case 0x4000005A: return "SDLK_KP_2";
	case 0x4000005B: return "SDLK_KP_3";
	case 0x4000005C: return "SDLK_KP_4";
	case 0x4000005D: return "SDLK_KP_5";
	case 0x4000005E: return "SDLK_KP_6";
	case 0x4000005F: return "SDLK_KP_7";
	case 0x40000060: return "SDLK_KP_8";
	case 0x40000061: return "SDLK_KP_9";
	case 0x40000062: return "SDLK_KP_0";
	case 0x40000063: return "SDLK_KP_PERIOD";
	case 0x40000065: return "SDLK_APPLICATION";
	case 0x40000066: return "SDLK_POWER";
	case 0x40000067: return "SDLK_KP_EQUALS";
	case 0x40000068: return "SDLK_F13";
	case 0x40000069: return "SDLK_F14";
	case 0x4000006A: return "SDLK_F15";
	case 0x4000006B: return "SDLK_F16";
	case 0x4000006C: return "SDLK_F17";
	case 0x4000006D: return "SDLK_F18";
	case 0x4000006E: return "SDLK_F19";
	case 0x4000006F: return "SDLK_F20";
	case 0x40000070: return "SDLK_F21";
	case 0x40000071: return "SDLK_F22";
	case 0x40000072: return "SDLK_F23";
	case 0x40000073: return "SDLK_F24";
	case 0x40000074: return "SDLK_EXECUTE";
	case 0x40000075: return "SDLK_HELP";
	case 0x40000076: return "SDLK_MENU";
	case 0x40000077: return "SDLK_SELECT";
	case 0x40000078: return "SDLK_STOP";
	case 0x40000079: return "SDLK_AGAIN";
	case 0x4000007A: return "SDLK_UNDO";
	case 0x4000007B: return "SDLK_CUT";
	case 0x4000007C: return "SDLK_COPY";
	case 0x4000007D: return "SDLK_PASTE";
	case 0x4000007E: return "SDLK_FIND";
	case 0x4000007F: return "SDLK_MUTE";
	case 0x40000080: return "SDLK_VOLUMEUP";
	case 0x40000081: return "SDLK_VOLUMEDOWN";
	case 0x40000085: return "SDLK_KP_COMMA";
	case 0x40000086: return "SDLK_KP_EQUALSAS400";
	case 0x40000099: return "SDLK_ALTERASE";
	case 0x4000009A: return "SDLK_SYSREQ";
	case 0x4000009B: return "SDLK_CANCEL";
	case 0x4000009C: return "SDLK_CLEAR";
	case 0x4000009D: return "SDLK_PRIOR";
	case 0x4000009E: return "SDLK_RETURN2";
	case 0x4000009F: return "SDLK_SEPARATOR";
	case 0x400000A0: return "SDLK_OUT";
	case 0x400000A1: return "SDLK_OPER";
	case 0x400000A2: return "SDLK_CLEARAGAIN";
	case 0x400000A3: return "SDLK_CRSEL";
	case 0x400000A4: return "SDLK_EXSEL";
	case 0x400000B0: return "SDLK_KP_00";
	case 0x400000B1: return "SDLK_KP_000";
	case 0x400000B2: return "SDLK_THOUSANDSSEPARATOR";
	case 0x400000B3: return "SDLK_DECIMALSEPARATOR";
	case 0x400000B4: return "SDLK_CURRENCYUNIT";
	case 0x400000B5: return "SDLK_CURRENCYSUBUNIT";
	case 0x400000B6: return "SDLK_KP_LEFTPAREN";
	case 0x400000B7: return "SDLK_KP_RIGHTPAREN";
	case 0x400000B8: return "SDLK_KP_LEFTBRACE";
	case 0x400000B9: return "SDLK_KP_RIGHTBRACE";
	case 0x400000BA: return "SDLK_KP_TAB";
	case 0x400000BB: return "SDLK_KP_BACKSPACE";
	case 0x400000BC: return "SDLK_KP_A";
	case 0x400000BD: return "SDLK_KP_B";
	case 0x400000BE: return "SDLK_KP_C";
	case 0x400000BF: return "SDLK_KP_D";
	case 0x400000C0: return "SDLK_KP_E";
	case 0x400000C1: return "SDLK_KP_F";
	case 0x400000C2: return "SDLK_KP_XOR";
	case 0x400000C3: return "SDLK_KP_POWER";
	case 0x400000C4: return "SDLK_KP_PERCENT";
	case 0x400000C5: return "SDLK_KP_LESS";
	case 0x400000C6: return "SDLK_KP_GREATER";
	case 0x400000C7: return "SDLK_KP_AMPERSAND";
	case 0x400000C8: return "SDLK_KP_DBLAMPERSAND";
	case 0x400000C9: return "SDLK_KP_VERTICALBAR";
	case 0x400000CA: return "SDLK_KP_DBLVERTICALBAR";
	case 0x400000CB: return "SDLK_KP_COLON";
	case 0x400000CC: return "SDLK_KP_HASH";
	case 0x400000CD: return "SDLK_KP_SPACE";
	case 0x400000CE: return "SDLK_KP_AT";
	case 0x400000CF: return "SDLK_KP_EXCLAM";
	case 0x400000D0: return "SDLK_KP_MEMSTORE";
	case 0x400000D1: return "SDLK_KP_MEMRECALL";
	case 0x400000D2: return "SDLK_KP_MEMCLEAR";
	case 0x400000D3: return "SDLK_KP_MEMADD";
	case 0x400000D4: return "SDLK_KP_MEMSUBTRACT";
	case 0x400000D5: return "SDLK_KP_MEMMULTIPLY";
	case 0x400000D6: return "SDLK_KP_MEMDIVIDE";
	case 0x400000D7: return "SDLK_KP_PLUSMINUS";
	case 0x400000D8: return "SDLK_KP_CLEAR";
	case 0x400000D9: return "SDLK_KP_CLEARENTRY";
	case 0x400000DA: return "SDLK_KP_BINARY";
	case 0x400000DB: return "SDLK_KP_OCTAL";
	case 0x400000DC: return "SDLK_KP_DECIMAL";
	case 0x400000DD: return "SDLK_KP_HEXADECIMAL";
	case 0x400000E0: return "SDLK_LCTRL";
	case 0x400000E1: return "SDLK_LSHIFT";
	case 0x400000E2: return "SDLK_LALT";
	case 0x400000E3: return "SDLK_LGUI";
	case 0x400000E4: return "SDLK_RCTRL";
	case 0x400000E5: return "SDLK_RSHIFT";
	case 0x400000E6: return "SDLK_RALT";
	case 0x400000E7: return "SDLK_RGUI";
	case 0x40000101: return "SDLK_MODE";
	case 0x40000102: return "SDLK_AUDIONEXT";
	case 0x40000103: return "SDLK_AUDIOPREV";
	case 0x40000104: return "SDLK_AUDIOSTOP";
	case 0x40000105: return "SDLK_AUDIOPLAY";
	case 0x40000106: return "SDLK_AUDIOMUTE";
	case 0x40000107: return "SDLK_MEDIASELECT";
	case 0x40000108: return "SDLK_WWW";
	case 0x40000109: return "SDLK_MAIL";
	case 0x4000010A: return "SDLK_CALCULATOR";
	case 0x4000010B: return "SDLK_COMPUTER";
	case 0x4000010C: return "SDLK_AC_SEARCH";
	case 0x4000010D: return "SDLK_AC_HOME";
	case 0x4000010E: return "SDLK_AC_BACK";
	case 0x4000010F: return "SDLK_AC_FORWARD";
	case 0x40000110: return "SDLK_AC_STOP";
	case 0x40000111: return "SDLK_AC_REFRESH";
	case 0x40000112: return "SDLK_AC_BOOKMARKS";
	case 0x40000113: return "SDLK_BRIGHTNESSDOWN";
	case 0x40000114: return "SDLK_BRIGHTNESSUP";
	case 0x40000115: return "SDLK_DISPLAYSWITCH";
	case 0x40000116: return "SDLK_KBDILLUMTOGGLE";
	case 0x40000117: return "SDLK_KBDILLUMDOWN";
	case 0x40000118: return "SDLK_KBDILLUMUP";
	case 0x40000119: return "SDLK_EJECT";
	case 0x4000011A: return "SDLK_SLEEP";
	default: return "not known SDL2.0.5 sym!";
	}
}

