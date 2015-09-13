#include <stdio.h>

#include "SDL2/SDL.h"
#include "../GameEngine.h"
//#include "state.h"
#include "IntroState.h"
#include "MenuState.h"
#include "../Item/Item.h"


IntroState IntroState::m_IntroState;

void IntroState::Init(GameEngine* game)
{
}

void IntroState::Cleanup()
{


}

void IntroState::Pause()
{
}

void IntroState::Resume()
{
}

void IntroState::HandleEvents(GameEngine* game)
{
	game->ChangeState( MenuState::Instance());
}

void IntroState::Update(GameEngine* game)
{

}

void IntroState::Draw(GameEngine* game)
{



}
