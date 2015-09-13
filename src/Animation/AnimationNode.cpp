#include "AnimationNode.h"

AnimationNode::AnimationNode(Animation* pAnim, int behaviour_number)
{
	Last = NULL;
	Next = NULL;
	anim = pAnim;
	ID = behaviour_number;
}

AnimationNode::~AnimationNode()
{
	delete anim;
}

void AnimationNode::AddAnimation(Animation* pAnim, int behaviour_number)
{
	AnimationNode* tmp = new AnimationNode( pAnim, behaviour_number );
	AnimationNode* walk = NULL;
	walk = this;
	while(walk->Next != NULL)
	{
		walk = walk->Next;
	}
	walk->Next = tmp;
	tmp->Last = walk;
	tmp->Next = NULL;

}

Animation* AnimationNode::GetAnimation(int animationID)
{
	AnimationNode* walk;
	walk = this;

	while(walk->Next != NULL)
	{
		if(walk->ID == animationID)
		{

			return walk->anim;
		}
		walk = walk->Next;
	}
	return walk->anim;
}

AnimationNode* AnimationNode::GetNext(void)
{
	return Next;
}
