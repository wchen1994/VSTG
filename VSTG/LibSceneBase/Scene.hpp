#pragma once

#include "Essential.hpp"

class __declspec(dllexport) Scene{
public:
	Scene();
	virtual ~Scene();
	virtual CommResMeth::GameState Run() = 0;
};
