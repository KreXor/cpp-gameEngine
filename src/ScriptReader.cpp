#include "ScriptReader.h"

ScriptReader::ScriptReader(string path)
{
	ofstream animationScriptFile;
	animationScriptFile.open ("Data/animation.data");

}

 void ScriptReader::LoadAnimations()
{
/*	string tempType;

	tempType = "Type()";
	type = tempType.insert(5, type);
	
	char frames[100];
	char tempReader[100];

	while(!animationScriptFile.eof()) 
    {
		animationScriptFile.getline(tempReader,100);
		if(type.compare(tempReader) == 0)
		{
			for(int i = 0; i < 11; i++)
			{
				animationScriptFile.getline(tempReader,100);
				parseAnimationLine(tempReader, uaf);
			}
			break;
		}
    }*/
}


