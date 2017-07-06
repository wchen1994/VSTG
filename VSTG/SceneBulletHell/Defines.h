#pragma once

#include <climits>

/*
Determine the type of usage for objects' ID
*/
typedef unsigned int OBJID;
#define OBJID_MAX (UINT32_MAX)

/*
Determine how many times of FixedUpdate() occured in gameobjects 
in a second
*/
#define FIXEDUPDATE_RATE 30

/* 
Force FixedUpdate() to occur every $(FIXEDUPDATE_RATE) per second
[1] Enable it if the fixedupdate rate is high
[2] Disable it if the game is slow and the update loop can never 
[2] be finished 
*/
//#define __FORCED_FIXEDUPDATE