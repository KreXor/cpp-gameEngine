#include "SDL2/SDL.h"
#include "../GameEngine.h"
//#include "state.h"
#include "IntroState.h"
#include "MenuState.h"
#include "PlayingState.h"


MenuState MenuState::m_MenuState;
int SelectedItem;

void MenuState::Init(GameEngine* game)
{


}

void MenuState::Cleanup()
{

}

void MenuState::Pause()
{
}

void MenuState::Resume()
{

}

void MenuState::HandleEvents(GameEngine* game)
{
	game->ChangeState( PlayingState::Instance());
}

void MenuState::Update(GameEngine* game)
{




}

void MenuState::Draw(GameEngine* game)
{

}

