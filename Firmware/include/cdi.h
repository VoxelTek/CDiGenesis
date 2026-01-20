#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

enum CDiModes{
	RELATIVE = 0b11001101, //'M' Relative Input Devices (Mouse, etc)
	MANEUVER = 0b11001010, //'J' Maneuvering Devices (Joystick, Joypad, etc)
	ABSOLUTE = 0b11010100, //'T' Absolute Coordinate Devices (Graphics Tablet, etc)
	SCREEN   = 0b11010011, //'S' Absolute Screen Devices (Touch-screens, etc)
	KEYBOARD = 0b11001011, //'K' Keyboard
	EXT_KEYB = 0b11011000  //'X' Extended Keyboard
};
