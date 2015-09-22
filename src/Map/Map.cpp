#include "Map.h"

using namespace rapidjson;


void Map::LoadMap(GameEngine* game)
{

	//this->tilesImage =  Load_image( "Data\\Tiles\\tiles.bmp" );
	this->readMapData(game);
	this->calculateLightPoints();


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

    /*    if(!document.HasMember("tile_count"))
        {
            cout << "failed to load map! member: tile_count not found\n";
            return;
        }
        else if(!document["tile_count"].IsInt())
        {
            cout << "failed to load map! member: tile_count is not an integer\n";
            return;
        }*/

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
        this->tile_size = document["tile_size"].GetInt();
        this->tiles_width_count = document["tile_width_count"].GetInt();
        this->tiles_heigth_count = document["tile_height_count"].GetInt();
        this->tilesImage[0] = Load_image(tile_set, game);

        const Value& a = document["grid"];
       // assert(a.IsArray());


        mapTilePosition = new Tile*[this->tiles_width_count];

        for (SizeType i = 0; i < a.Size(); i++)
        {
            mapTilePosition[i] = new Tile[this->tiles_heigth_count];

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
                    mapTilePosition[i][j] = tile;
                    //count++;
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

    //Calculate where the camera is in the matrice
    int num_t_x = floor((game->screenWidth/this->tile_size)/game->camera.getZoomLevel());
	int num_t_y = floor((game->screenHeigth/this->tile_size)/game->camera.getZoomLevel());

	//get Y start postion
	int render_y_start = floor(game->camera.getYPosition()*-1/this->tile_size);
	render_y_start = (render_y_start < 0) ? 0 : render_y_start;
	render_y_start = (render_y_start > this->tiles_heigth_count) ? this->tiles_heigth_count : render_y_start;

	//get Y start postion
	int render_y_end = floor(game->camera.getYPosition()*-1/this->tile_size) + num_t_y+(3/game->camera.getZoomLevel());
	render_y_end = (render_y_end < 0) ? 0: render_y_end;
	render_y_end = (render_y_end > this->tiles_heigth_count) ? this->tiles_heigth_count: render_y_end;

	//get X start postion
	int render_x_start = floor(game->camera.getXPosition()*-1/this->tile_size);
	render_x_start = (render_x_start < 0) ? 0 : render_x_start;
	render_x_start = (render_x_start > this->tiles_width_count) ? this->tiles_width_count : render_x_start;

	//get X end postion
	int render_x_end = floor(game->camera.getXPosition()*-1/this->tile_size) + num_t_x+(3/game->camera.getZoomLevel());
	render_x_end = (render_x_end < 0) ? 0 : render_x_end;
	render_x_end = (render_x_end > this->tiles_width_count) ? this->tiles_width_count: render_x_end;

	//Render all tiles on screen
    for(int y = render_y_start; y < render_y_end; y++)
    {
        for(int x = render_x_start; x < render_x_end; x++)
        {
            rect.x = this->mapTilePosition[y][x].worldPosition.x*game->camera.getZoomLevel() + game->camera.getXPosition();

            rect.y = this->mapTilePosition[y][x].worldPosition.y*game->camera.getZoomLevel() + game->camera.getYPosition();

            rect.w = this->tile_size*game->camera.getZoomLevel();

            rect.h = this->tile_size*game->camera.getZoomLevel();



            rect2.x = mapTilePosition[y][x].imagePosition.x;

            rect2.y = mapTilePosition[y][x].imagePosition.y;

            rect2.w = this->tile_size;

            rect2.h = this->tile_size;

            SDL_RenderCopy(game->renderer, this->tilesImage[mapTilePosition[y][x].type], &rect2, &rect);
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

int Map::getTileSize()
{
    return this->tile_size;
}

int Map::getTilesHeightCount()
{
    return this->tiles_heigth_count;
}

int Map::getTilesWidthCount()
{
    return this->tiles_width_count;
}

bool Map::isWall(Tile tile)
{
    if(tile.blockid == 5 || tile.blockid == 6)
        return true;

    return false;
}

void Map::calculateLightPoints()
{
	for(int y = 0; y < this->getTilesHeightCount(); y++)
	{
		for(int x = 0; x < this->getTilesWidthCount(); x++)
		{
			if(this->isWall(this->mapTilePosition[y][x]))
			{
				bool n, e, s, w;

				n = this->isWall(this->mapTilePosition[y-1][x]);
				e = this->isWall(this->mapTilePosition[y][x+1]);
				s = this->isWall(this->mapTilePosition[y+1][x]);
				w = this->isWall(this->mapTilePosition[y][x-1]);

				//#
				if((!n && !e && !s && !w) || (n && e && s && w))
				{
					addLightPointToCorner(this->mapTilePosition[y][x], 0);
					addLightPointToCorner(this->mapTilePosition[y][x], 1);
					addLightPointToCorner(this->mapTilePosition[y][x], 2);
					addLightPointToCorner(this->mapTilePosition[y][x], 3);
				}
				//|  	-#-
				//#   	 |
				else if((n && !e && !s && !w) || (!n && e && s && w))
				{
					addLightPointToCorner(this->mapTilePosition[y][x], 2);
					addLightPointToCorner(this->mapTilePosition[y][x], 3);
				}
				//		 |
				//#-	-#
				//		 |
				else if((!n && e && !s && !w) || (n && !e && s && w))
				{
					addLightPointToCorner(this->mapTilePosition[y][x], 0);
					addLightPointToCorner(this->mapTilePosition[y][x], 2);
				}
				//#		 |
				//|		-#-
				else if((!n && !e && s && !w) || (!n && e && s && w))
				{
					addLightPointToCorner(this->mapTilePosition[y][x], 0);
					addLightPointToCorner(this->mapTilePosition[y][x], 1);
				}
				//		|
				//-#	#-
				//		|
				else if((!n && !e && !s && w) || (n && e && s && !w))
				{
					addLightPointToCorner(this->mapTilePosition[y][x], 1);
					addLightPointToCorner(this->mapTilePosition[y][x], 3);
				}

				//|		-#
				//#-	 |
				else if((n && e && !s && !w) || (!n && !e && s && w))
				{
					addLightPointToCorner(this->mapTilePosition[y][x], 1);
					addLightPointToCorner(this->mapTilePosition[y][x], 2);
				}
				//#-	 |
				//|		-#
				else if((!n && e && s && !w) ||(n && !e && !s && w))
				{
					addLightPointToCorner(this->mapTilePosition[y][x], 0);
					addLightPointToCorner(this->mapTilePosition[y][x], 3);
				}
			}
		}
	}
}


//0 = top-left
//1 = top-right
//2 = bottom-left
//3 = bottom-right
void Map::addLightPointToCorner(Tile tile, int corner)
{
	if(corner == 0)
		addLightPoint(tile.worldPosition.x-1, tile.worldPosition.y-1);

	else if(corner == 1)
		addLightPoint(tile.worldPosition.x+this->getTileSize()+1, tile.worldPosition.y-1);

	else if(corner == 2)
		addLightPoint(tile.worldPosition.x-1, tile.worldPosition.y+this->getTileSize()+1);

	else if(corner == 3)
		addLightPoint(tile.worldPosition.x+this->getTileSize()+1, tile.worldPosition.y+this->getTileSize()+1);
}

void Map::addLightPoint(int x, int y)
{
	Position pos;
	pos.x = x;
	pos.y =	y;
	this->lightPoints.push_back(pos);
}
