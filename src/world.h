#ifndef WORLD_H
#define WORLD_H
#include "oxygine-framework.h"
#include "map.h"
#include "player.h"
#include <set>
#include "entities/mob.h"


using namespace oxygine;

class World : public Actor
{
    Map* map;
    Player* player;
    GameScreen* gamescreen;

    std::set<spMob> m_mobs;
    float dt_zombie;

public:
    World(GameScreen* gs);
    void draw();

    void addMob(spMob mob);
    void corpseDecayed(Event * event);

protected:
    void doUpdate(const UpdateState &us);
    void zombieAttacks(Event * event);

    void onPlayerPunch(Event * event);

};

#endif // WORLD_H
