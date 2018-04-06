#pragma once
class windowDef
{
public:
	static windowDef& get(); //provide static member function to access the unique instance.

	int windowSizeX;
	int windowSizeY;
	int windowStyle;

private:
	windowDef() {}; //prevent construction from outside this class' methods
	windowDef& operator=(const windowDef&); //prevent assignment
	windowDef(const windowDef&); //prevent copy construction

};

