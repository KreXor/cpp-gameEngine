#ifndef ANIMATIONNODE_H
#define ANIMATIONNODE_H
#include "Animation.h"


class AnimationNode	{
	Animation* anim;
	AnimationNode* Last;
	AnimationNode* Next;
	int ID;
public:
	AnimationNode(Animation* pAnim, int behaviour_number);
	~AnimationNode();
	void AddAnimation(Animation* pAnim, int behaviour_number);
	Animation* GetAnimation(int animationID);
	AnimationNode* GetNext(void);
};

#endif