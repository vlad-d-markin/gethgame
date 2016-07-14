#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "SDL_keyboard.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include "screens/gamescreen.h"
#include <iostream>

using namespace oxygine;

class Player : public Sprite
{
private: 
	Vector2 mapSize;
    Resources * my_resources;
    ResAnim* resAnim;
    Vector2 pos;
    float dirX;
    float dirY;
    float dirXOld;
    float dirYOld;
    bool movingOld;
    int animationDuration;
    RectT<Vector2> * rectangle;
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
    GameScreen *gamescreen;
    ResAnim* persAnimUp;
    ResAnim* persAnimDown;
    ResAnim* persAnimRight;
    ResAnim* persStandsUp;
    ResAnim* persStandsDown;
    ResAnim* persStandsRight;
    ResAnim* persAnimCurrent;
    void rotate();
    bool moving;
    int getSign(const float number);
    spTween tween;
    bool left;
protected:
	void doUpdate(const UpdateState &us);
public:
    Player();
    Player(GameScreen *gs);
	void setMapSize(Vector2 _mapSize) { mapSize = _mapSize; }
	Vector2 getMapSize() const { return mapSize; }
    Vector2 getDirection();
    //void setDirection(const float dir_x, const float dir_y);
    void moveX(const float distance);
    void moveY(const float distance);
    void setMoving(const bool isMoving);
};

typedef ::oxygine::intrusive_ptr<Player> spPlayer;

#endif // PLAYER_H
