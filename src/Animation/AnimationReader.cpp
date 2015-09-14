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

    //Cleanup!
    delete[] buffer;

    if(document.IsObject())
    {
        if(!document.HasMember("sprite_set"))
        {
            cout << "failed to animation (" << filename << ")! has no member tile_set\n";
            return this->sprite;
        }
        else if(!document["sprite_set"].IsString())
        {
            cout << "failed to animation (" << filename << ")! member tile_set is not a string\n";
            return this->sprite;
        }

         if(!document.HasMember("animations"))
        {
            cout << "failed to animation (" << filename << ")! has no member animations\n";
            return this->sprite;
        }
        else if(!document["animations"].IsArray())
        {
            cout << "failed to animation (" << filename << ")! member animations is not an array\n";
            return this->sprite;
        }

        string path = document["sprite_set"].GetString();

        const Value& a = document["animations"];



        for (SizeType i = 0; i < a.Size(); i++)
        {
            if(!a[i].HasMember("framerate"))
            {
                cout << "failed to animation (" << filename << ")! has no member framerate\n";
                return this->sprite;
            }
            else if(!a[i]["framerate"].IsInt())
            {
                cout << "failed to animation (" << filename << ")! member framerate is not an int\n";
                return this->sprite;
            }

            if(!a[i].HasMember("framecount"))
            {
                cout << "failed to animation (" << filename << ")! has no member framecount\n";
                return this->sprite;
            }
            else if(!a[i]["framecount"].IsInt())
            {
                cout << "failed to animation (" << filename << ")! member framecount is not an int\n";
                return this->sprite;
            }

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


    }
    else
    {
        cout << "failed to animation (" << filename << ")! not a correct json file\n";
    }
	return this->sprite;
}



