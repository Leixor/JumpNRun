#include "GlobalVariables.h"

windowDef& windowDef::get() 
{
	static windowDef get; //create as a static object, i.e. will only be created once.
	return get;
};

keyDef& keyDef::get()
{
	static keyDef get; //create as a static object, i.e. will only be created once.
	return get;
}
