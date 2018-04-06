#include "standardInclude.h"



windowDef& windowDef::get() {
	static windowDef get; //create as a static object, i.e. will only be created once.
	return get;
};
