#pragma once
#include "Include.h"

class Scene
{
public:
	virtual void Initialize() abstract;
	virtual int Update() abstract;
	virtual void Render() abstract;
	virtual void Release() abstract;

public:
	Scene();
	virtual ~Scene();
};

