#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "SDL_keyboard.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include <iostream>

using namespace oxygine;

class Player : public Sprite
{
private: 
	Vector2 mapSize;
    Resources * my_resources;
    ResAnim* resAnim;
    Vector2 pos;
    Vector2 dir;
    int healthPoints;
    int stamina;
    int healthRegenerationSpeed;
    int staminaRegenerationSpeed;
    int movementSpeed;
    int criticalHit;
    int accuracy;
    int hitResistance;
    int shotResistance;
    int hitEvasion;
    int shotEvasion;
    int weaponHandlingSpeed;
    int Vnorm;
protected:
	void doUpdate(const UpdateState &us);
public:
    Player();
	void setMapSize(Vector2 _mapSize) { mapSize = _mapSize; }
	Vector2 getMapSize() const { return mapSize; }
};

typedef ::oxygine::intrusive_ptr<Player> spPlayer;

#endif // PLAYER_H
