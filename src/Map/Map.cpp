#include "Map.h"
#include <iostream>
#include "rapidjson/document.h"
using namespace rapidjson;


void Map::LoadMap(GameEngine* game)
{

	//this->tilesImage =  Load_image( "Data\\Tiles\\tiles.bmp" );
	this->readMapData(game);


}


void Map::readMapData(GameEngine* game)
{
    //Read map file
    ifstream ifs;
    string map_path = "Data/Tiles/map.json";
    ifs.open ( map_path.c_str() );

    std::filebuf* pbuf = ifs.rdbuf();

    std::size_t size = pbuf->pubseekoff (0,ifs.end,ifs.in);
    pbuf->pubseekpos (0,ifs.in);


    char* buffer=new char[size];

    pbuf->sgetn (buffer,size);

    ifs.close();

    //Parse map
    Document document;
    document.Parse(buffer);

    //clean up buffer
    delete[] buffer;

    if(document.IsObject())
    {
        Tile tile;
        int count = 0;



        //Check json objects
        if(!document.HasMember("tile_set"))
        {
            cout << "failed to load map! member: tile_set not found\n";
            return;
        }
        else if(!document["tile_set"].IsString())
        {
            cout << "failed to load map! member: tile_set is not a string\n";
            return;
        }

        if(!document.HasMember("tile_size"))
        {
            cout << "failed to load map! member: tile_size not found\n";
            return;
        }
        else if(!document["tile_size"].IsInt())
        {
            cout << "failed to load map! member: tile_size is not an integer\n";
            return;
        }

        if(!document.HasMember("tile_count"))
        {
            cout << "failed to load map! member: tile_count not found\n";
            return;
        }
        else if(!document["tile_count"].IsInt())
        {
            cout << "failed to load map! member: tile_count is not an integer\n";
            return;
        }

        if(!document.HasMember("grid"))
        {
            cout << "failed to load map! member: grid not found\n";
            return;
        }
        else if(!document["grid"].IsArray())
        {
            cout << "failed to load map! member: grid is not an array\n";
            return;
        }

        //load json objects
        string tile_set = document["tile_set"].GetString();
        int tile_size = document["tile_size"].GetInt();
        this->tilesCount = document["tile_count"].GetInt();
        this->tilesImage[0] = Load_image(tile_set, game);

        const Value& a = document["grid"];
       // assert(a.IsArray());


        mapTilePosition = new Tile[this->tilesCount];

        for (SizeType i = 0; i < a.Size(); i++)
        {
            if(a[i].IsArray())
            {
                for (SizeType j = 0; j < a[i].Size(); j++)
                {
                    if(!a[i][j].HasMember("type"))
                    {
                        cout << "failed to load map! tile misses members\n";
                        return;
                    }
                    else if(!a[i][j]["type"].IsInt())
                    {
                        cout << "failed to load map! tiles members is not correct format\n";
                        return;
                    }

                    int type_id = a[i][j]["type"].GetInt();

                    if(!document["type_legend"][type_id].HasMember("image_x") || !document["type_legend"][type_id].HasMember("image_y"))
                    {
                        cout << "failed to load map! tile misses members\n";
                        return;
                    }
                    else if(!document["type_legend"][type_id]["image_x"].IsInt() || !document["type_legend"][type_id]["image_y"].IsInt())
                    {
                        cout << "failed to load map! tiles members is not correct format\n";
                        return;
                    }

                    tile.worldPosition.x = j*tile_size;
                    tile.worldPosition.y = i*tile_size;
                    tile.imagePosition.x = document["type_legend"][type_id]["image_x"].GetInt();
                    tile.imagePosition.y = document["type_legend"][type_id]["image_y"].GetInt();
                    tile.type = 0;
                    tile.blockid = type_id;
                    tile.layer = 0;
                    tile.boundingBoxType = 0;
                    tile.t_size = tile_size;
                    mapTilePosition[count] = tile;
                    count++;
                }
            }
            else
            {
                cout << "failed to load map! could not read tile list\n";
                return;
            }
        }

    }
    else
    {
        cout << "failed to load map: not a correct json file\n";
    }

}
void Map::Draw(GameEngine* game)
{
	SDL_Rect rect;
	SDL_Rect rect2;

	for(int i = 0; i < this->tilesCount; i++)
	{
        //Make sure that we only draw what is on the screen
        if(this->mapTilePosition[i].worldPosition.x*game->camera.getZoomLevel() > (game->camera.getXPosition()+400)*-1 && this->mapTilePosition[i].worldPosition.x*game->camera.getZoomLevel() < (game->camera.getXPosition()-(game->screenWidth))*-1
        && this->mapTilePosition[i].worldPosition.y*game->camera.getZoomLevel() > (game->camera.getYPosition()+400)*-1 && this->mapTilePosition[i].worldPosition.y*game->camera.getZoomLevel() < (game->camera.getYPosition()-(game->screenHeigth))*-1)
        {
            rect.x = this->mapTilePosition[i].worldPosition.x*game->camera.getZoomLevel() + game->camera.getXPosition();
            rect.y = this->mapTilePosition[i].worldPosition.y*game->camera.getZoomLevel() + game->camera.getYPosition();
            rect.w = this->mapTilePosition[i].t_size*game->camera.getZoomLevel();
            rect.h = this->mapTilePosition[i].t_size*game->camera.getZoomLevel();

            rect2.x = mapTilePosition[i].imagePosition.x;
            rect2.y = mapTilePosition[i].imagePosition.y;
            rect2.w = this->mapTilePosition[i].t_size;
            rect2.h = this->mapTilePosition[i].t_size;


            SDL_RenderCopy(game->renderer, this->tilesImage[mapTilePosition[i].type], &rect2, &rect);
            //SDL_RenderCopyEx(game->renderer, this->tilesImage[mapTilePosition[i].type], &rect2, &rect, 45, NULL, SDL_FLIP_NONE);
        }
	}
}

SDL_Texture *Map::Load_image( string filename, GameEngine* game )
{
	SDL_Surface* loaded_image = NULL;

	if(filename.c_str() == NULL)
	{
		return NULL;
	}

	loaded_image = SDL_LoadBMP( filename.c_str() );

	if( loaded_image == NULL )
	{
		return NULL;
	}

	Uint32 colorkey = SDL_MapRGB( loaded_image->format, 255, 0, 255);

	SDL_SetColorKey( loaded_image, SDL_RLEACCEL | SDL_TRUE, colorkey);


	SDL_Texture *bitmapTex = SDL_CreateTextureFromSurface(game->renderer, loaded_image);

	SDL_FreeSurface(loaded_image);
	return bitmapTex;
}
