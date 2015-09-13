#include "Sprite.h"

Sprite::Sprite()
{
	current_behaviour = BEHAVIOUR_DEFAULT;
	pAnimations = NULL;
}

Sprite::~Sprite()
{
	AnimationNode* temp;
	temp = pAnimations->GetNext();
	while(temp  != NULL )	{
		delete pAnimations;
		pAnimations = temp;
		temp = pAnimations->GetNext();
	}
}

void Sprite::Draw(SDL_Rect *position, GameEngine *game, float gameTime, int direction)
{
	Animation* temp;
	temp = pAnimations->GetAnimation( current_behaviour );

	temp->Draw(position, game, gameTime, direction);
}

void Sprite::AddAnimation(Animation* anim, int behaviour_number)
{
	if(pAnimations == NULL)	{
		pAnimations = new AnimationNode(anim, behaviour_number);
	} else {
		pAnimations->AddAnimation(anim, behaviour_number);
	}
}

void Sprite::PlayAnimation()
{
	Animation* temp;
	temp = pAnimations->GetAnimation( current_behaviour );

	temp->PlayAnimation();
}


void Sprite::NextFrame()
{
	Animation* temp;
	temp = pAnimations->GetAnimation( current_behaviour );
	temp->NextFrame();
}

void Sprite::LastFrame()
{
	Animation* temp;
	temp = pAnimations->GetAnimation( current_behaviour );
	temp->LastFrame();
}

void Sprite::SetCurrentBehaviour(int behaviour)
{
	this->current_behaviour = behaviour;
}

int Sprite::GetCurrentBehaviour()
{
	return this->current_behaviour;
}
