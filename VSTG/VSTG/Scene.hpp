#pragma once

#include "Essential.hpp"

class Scene{
public:
	Scene();
	virtual ~Scene();
	virtual Essential::GameState Run() = 0;
};
