#pragma once
#include "UnorderdMap.h"

class windowDef
{
public:
	static windowDef& get(); //provide static member function to access the unique instance.

	float windowSizeX;
	float windowSizeY;
	int windowStyle;

private:
	windowDef() {}; //prevent construction from outside this class' methods
	windowDef& operator=(const windowDef&); //prevent assignment
	windowDef(const windowDef&); //prevent copy construction

};

class keyDef
{
public:
	static keyDef& get(); //provide static member function to access the unique instance.

	UnorderdMap<string, Keyboard::Key> keyCode;

private:
	keyDef()
	{
		keyCode.push("A", Keyboard::A);
		keyCode.push("B", Keyboard::B);
		keyCode.push("C", Keyboard::C);
		keyCode.push("D", Keyboard::D);
		keyCode.push("E", Keyboard::E);
		keyCode.push("F", Keyboard::F);
		keyCode.push("G", Keyboard::G);
		keyCode.push("H", Keyboard::H);
		keyCode.push("I", Keyboard::I);
		keyCode.push("J", Keyboard::J);
		keyCode.push("K", Keyboard::K);
		keyCode.push("L", Keyboard::L);
		keyCode.push("M", Keyboard::M);
		keyCode.push("N", Keyboard::N);
		keyCode.push("O", Keyboard::O);
		keyCode.push("P", Keyboard::P);
		keyCode.push("Q", Keyboard::Q);
		keyCode.push("R", Keyboard::R);
		keyCode.push("S", Keyboard::S);
		keyCode.push("T", Keyboard::T);
		keyCode.push("U", Keyboard::U);
		keyCode.push("V", Keyboard::V);
		keyCode.push("W", Keyboard::W);
		keyCode.push("X", Keyboard::X);
		keyCode.push("Y", Keyboard::Y);
		keyCode.push("Z", Keyboard::Z);
		keyCode.push("0", Keyboard::Num0);
		keyCode.push("1", Keyboard::Num1);
		keyCode.push("2", Keyboard::Num2);
		keyCode.push("3", Keyboard::Num3);
		keyCode.push("4", Keyboard::Num4);
		keyCode.push("5", Keyboard::Num5);
		keyCode.push("6", Keyboard::Num6);
		keyCode.push("7", Keyboard::Num7);
		keyCode.push("8", Keyboard::Num8);
		keyCode.push("9", Keyboard::Num9);
		keyCode.push("Escape", Keyboard::Escape);
		keyCode.push("LControl", Keyboard::LControl);
		keyCode.push("LShift", Keyboard::LShift);
		keyCode.push("LAlt", Keyboard::LAlt);
		keyCode.push("LSystem", Keyboard::LSystem);
		keyCode.push("RControl", Keyboard::RControl);
		keyCode.push("RShift", Keyboard::RShift);
		keyCode.push("RAlt", Keyboard::RAlt);
		keyCode.push("RSystem", Keyboard::RSystem);
		keyCode.push("Menu", Keyboard::Menu);
		keyCode.push("LBracket", Keyboard::LBracket);
		keyCode.push("RBracket", Keyboard::RBracket);
		keyCode.push("SemiColon", Keyboard::SemiColon);
		keyCode.push("Comma", Keyboard::Comma);
		keyCode.push("Period", Keyboard::Period);
		keyCode.push("Quote", Keyboard::Quote);
		keyCode.push("Slash", Keyboard::Slash);
		keyCode.push("BackSlash", Keyboard::BackSlash);
		keyCode.push("Tilde", Keyboard::Tilde);
		keyCode.push("Equal", Keyboard::Equal);
		keyCode.push("Dash", Keyboard::Dash);
		keyCode.push("Space", Keyboard::Space);
		keyCode.push("Return", Keyboard::Return);
		keyCode.push("BackSpace", Keyboard::BackSpace);
		keyCode.push("Tab", Keyboard::Tab);
		keyCode.push("PageUp", Keyboard::PageUp);
		keyCode.push("PageDown", Keyboard::PageDown);
		keyCode.push("End", Keyboard::End);
		keyCode.push("Home", Keyboard::Home);
		keyCode.push("Insert", Keyboard::Insert);
		keyCode.push("Delete", Keyboard::Delete);
		keyCode.push("Add", Keyboard::Add);
		keyCode.push("Subtract", Keyboard::Subtract);
		keyCode.push("Multiply", Keyboard::Multiply);
		keyCode.push("Divide", Keyboard::Divide);
		keyCode.push("Left", Keyboard::Left);
		keyCode.push("Right", Keyboard::Right);
		keyCode.push("Up", Keyboard::Up);
		keyCode.push("Down", Keyboard::Down);
		keyCode.push("Num0", Keyboard::Numpad0);
		keyCode.push("Num1", Keyboard::Numpad1);
		keyCode.push("Num2", Keyboard::Numpad2);
		keyCode.push("Num3", Keyboard::Numpad3);
		keyCode.push("Num4", Keyboard::Numpad4);
		keyCode.push("Num5", Keyboard::Numpad5);
		keyCode.push("Num6", Keyboard::Numpad6);
		keyCode.push("Num7", Keyboard::Numpad7);
		keyCode.push("Num8", Keyboard::Numpad8);
		keyCode.push("Num9", Keyboard::Numpad9);
		keyCode.push("F1", Keyboard::F1);
		keyCode.push("F2", Keyboard::F2);
		keyCode.push("F3", Keyboard::F3);
		keyCode.push("F4", Keyboard::F4);
		keyCode.push("F5", Keyboard::F5);
		keyCode.push("F6", Keyboard::F6);
		keyCode.push("F7", Keyboard::F7);
		keyCode.push("F8", Keyboard::F8);
		keyCode.push("F9", Keyboard::F9);
		keyCode.push("F10", Keyboard::F10);
		keyCode.push("F11", Keyboard::F11);
		keyCode.push("F12", Keyboard::F12);
		keyCode.push("F13", Keyboard::F13);
		keyCode.push("F14", Keyboard::F14);
		keyCode.push("F15", Keyboard::F15);
		keyCode.push("Pause", Keyboard::Pause);
	}; //prevent construction from outside this class' methods
	keyDef& operator=(const keyDef&); //prevent assignment
	keyDef(const keyDef&); //prevent copy construction

};

