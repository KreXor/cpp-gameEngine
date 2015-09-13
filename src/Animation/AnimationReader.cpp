#include "AnimationReader.h"
#include "rapidjson/document.h"
using namespace rapidjson;

/*
This class open a txt file (animation.data), "parse" it and get the info for the animations.
*/
AnimationReader::AnimationReader(string path)
{
	//fileReader.OpenFile(path);

}

Sprite* AnimationReader::LoadAnimations(string filename, GameEngine* game)
{
	this->sprite = new Sprite();

	int frameRate;
	int frameCount;

	int x,y,h,w,frame;
	int animationCount = 1;

	Animation *animation;

    //Read map file
    ifstream ifs;
    ifs.open ( filename.c_str() );

    std::filebuf* pbuf = ifs.rdbuf();

    std::size_t size = pbuf->pubseekoff (0,ifs.end,ifs.in);
    pbuf->pubseekpos (0,ifs.in);


    char* buffer=new char[size];

    pbuf->sgetn (buffer,size);

    ifs.close();

    //Parse map
    Document document;
    document.Parse(buffer);

    string path = document["sprite_set"].GetString();

    const Value& a = document["animations"];
    assert(a.IsArray());


    for (SizeType i = 0; i < a.Size(); i++)
    {
        frameRate = a[i]["framerate"].GetInt();
        frameCount = a[i]["framecount"].GetInt();

        animation = new Animation();
        if(animation == NULL)
        {
            delete animation;
        }

        animation->Init(frameCount, frameRate, path, game);

        for (SizeType j = 0; j < a[i]["frames"].Size(); j++)
        {
            frame = a[i]["frames"][j]["frame"].GetInt();
            x = a[i]["frames"][j]["pos_x"].GetInt();
            y = a[i]["frames"][j]["pos_y"].GetInt();
            w = a[i]["frames"][j]["width"].GetInt();
            h = a[i]["frames"][j]["height"].GetInt();

            animation->SetFrame(frame, x, y, w, h);
        }

        this->sprite->AddAnimation(animation, animationCount);
        animationCount++;
    }

    //Cleanup!
    delete[] buffer;

	return this->sprite;
}



