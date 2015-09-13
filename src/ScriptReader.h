#ifndef SCRIPTREADER_H
#define SCRIPTREADER_H

#include <SDL2/SDL.h>
#include <string.h>
#include <fstream>
#include <cstdlib>

using namespace std;

class ScriptReader
{
private:

public:
	ifstream animationScriptFile;
	ScriptReader(string path);
	void LoadAnimations();



};
#endif
