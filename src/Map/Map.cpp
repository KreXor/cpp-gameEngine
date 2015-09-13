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



    Tile tile;
	int count = 0;

	this->tilesCount = 6259;

    string tile_set = document["tile_set"].GetString();
    int tile_size = document["tile_size"].GetInt();
    this->tilesCount = document["tile_count"].GetInt();
    this->tilesImage[0] = Load_image(tile_set, game);

    const Value& a = document["grid"];
   // assert(a.IsArray());


    mapTilePosition = new Tile[this->tilesCount];

    for (SizeType i = 0; i < a.Size(); i++)
    {
       // assert(a[i].IsArray());
        for (SizeType j = 0; j < a[i].Size(); j++)
        {
            int type_id = a[i][j]["type"].GetInt();
            tile.worldPosition.x = j*tile_size;
            tile.worldPosition.y = i*tile_size;
            tile.imagePosition.x = document["type_legend"][type_id]["image_x"].GetInt();
            tile.imagePosition.y = document["type_legend"][type_id]["image_y"].GetInt();
            tile.type = 0;
            tile.layer = 0;
            tile.boundingBoxType = 0;
            tile.t_size = tile_size;
            mapTilePosition[count] = tile;
            count++;
        }
    }

    //Cleanup!
    delete[] buffer;

}
void Map::Draw(GameEngine* game, float x_offset, float y_offset)
{
	SDL_Rect rect;
	SDL_Rect rect2;

	for(int i = 0; i < this->tilesCount; i++)
	{
		rect.x = this->mapTilePosition[i].worldPosition.x*game->camera.getZoomLevel() + x_offset;
		rect.y = this->mapTilePosition[i].worldPosition.y*game->camera.getZoomLevel() + y_offset;
		rect.w = this->mapTilePosition[i].t_size*game->camera.getZoomLevel();
		rect.h = this->mapTilePosition[i].t_size*game->camera.getZoomLevel();

		rect2.x = mapTilePosition[i].imagePosition.x;
		rect2.y = mapTilePosition[i].imagePosition.y;
		rect2.w = this->mapTilePosition[i].t_size;
		rect2.h = this->mapTilePosition[i].t_size;

		SDL_RenderCopy(game->renderer, this->tilesImage[mapTilePosition[i].type], &rect2, &rect);

		//SDL_BlitSurface( this->tilesImage[mapTilePosition[i].type], &rect2, game->screen, &rect);
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
