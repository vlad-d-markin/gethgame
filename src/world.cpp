#include "world.h"
#include "map.h"
#include "entities/zombie.h"
#include "banana.h"
#include <iostream>



World::World(GameScreen *gs)
{
    spZombie zombie;

    map = new Map();
    gamescreen = gs;

    std::vector<Position> zombie_pos=map->getPosZombie();
    std::cout<<"size = "<<zombie_pos.size();
    for (int i=0; i<(zombie_pos.size()); i++)
    {
        std::cout<<"x = "<< zombie_pos[i].x<<" y="<<zombie_pos[i].y<<std::endl;
        zombie = new Zombie(Vector2(zombie_pos[i].x,zombie_pos[i].y));
        zombie->setName("zomb");
        addMob(zombie);
    }
	gamescreen->setBananasOnMap(map->getPosBananas().size());
}

void World::reset()
{
    //reseting hero
    player->resetPlayer();
    //reseting zombie
    for(auto it = m_mobs.begin(); it != m_mobs.end(); it++)
    {
        (*it).second->detach();
    }
    m_mobs.clear();
    spZombie zombie;
    std::vector<Position> zombie_pos=map->getPosZombie();
    for (int i=0; i<(zombie_pos.size()); i++)
    {
        std::cout<<"x = "<< zombie_pos[i].x<<" y="<<zombie_pos[i].y<<std::endl;
        zombie = new Zombie(Vector2(zombie_pos[i].x,zombie_pos[i].y));
        zombie->setName("zomb");
        addMob(zombie);
    }

    //reseting bananas
    for(int i=0; i < m_bananas.size(); i++) {
        m_bananas[i].deleteBanana();
    }
    std::vector<Vector2> pos_bananas = map->getPosBananas();
    for(int i=0; i < pos_bananas.size(); i++) {
        Banana banana(pos_bananas[i], gamescreen);
        m_bananas.push_back(banana);
    }
}

void World::addMob(spMob mob)
{
    mob->attachTo(this);
    mob->addEventListener(MobCorpseDecayedEvent::EVENT, CLOSURE(this, &World::corpseDecayed));
    mob->addEventListener(ZombiePunchEvent::EVENT, CLOSURE(this, &World::zombieAttacks));
    m_mobs.insert(std::pair<int, spMob>(mob->getObjectID(), mob));
}

void World::draw()
{
    map->drawGround(gamescreen);

    std::vector<Vector2> pos_bananas = map->getPosBananas();
    for(int i=0; i < pos_bananas.size(); i++) {
        Banana banana(pos_bananas[i], gamescreen);
        m_bananas.push_back(banana);
    }


    player = new Player(gamescreen);
    player->setAnchor(0.5, 0.5);
    player->attachTo(gamescreen);
    player->setMapSize(map->getMapSize());
    player->addEventListener(PlayerPunchEvent::EVENT, CLOSURE(this, &World::onPlayerPunch));

    map->drawTop(gamescreen);

    // TODO: Somebody remove it, pls

}

void World::doUpdate(const UpdateState &us)
{

    Actor::doUpdate(us);

    checkBanana();

    // TEST
/*
    if(dt_zombie < 2000) {
        dt_zombie += us.dt;
    }
    else {
        for(auto it = m_mobs.begin(); it != m_mobs.end(); it++)
        {
            spMob m = *it;
            zombie->punch(right);
        }
        dt_zombie = 0;
    }

    static bool o = true;
    if(us.time > 5000 && o)
    {
        o = false;
        for(auto it = m_mobs.begin(); it != m_mobs.end(); it++)
        {
            //(*it)->getHit(100);
        }
    }
    // END OF TEST
    */


    if( player->getDirection() == Vector2(0,0) )
    {
        player->setMoving(false);
        return;
    }

    int num_steps = 10;
    float step_speed_x = (player->getDirection().x) / num_steps;
    float step_speed_y = (player->getDirection().y) / num_steps;
    bool playerMoved = false;

    for(int i = 0; i < num_steps; i++)
    {
        if(step_speed_x != 0)
        {
            RectT<Vector2> new_rect_player_x(player->getPosition()+Vector2(step_speed_x, 0), player->getSize());
            if(map->isObstacle(new_rect_player_x) == false) {
                player->moveX(step_speed_x);
                playerMoved = true;
            }
        }

        if(step_speed_y != 0)
        {
            RectT<Vector2> new_rect_player_y(player->getPosition()+Vector2(0, step_speed_y), player->getSize());
            if(map->isObstacle(new_rect_player_y) == false) {
                player->moveY(step_speed_y);
                playerMoved = true;
            }
        }
    }
    player->setMoving(playerMoved);

    for(auto it = m_mobs.begin(); it != m_mobs.end(); it++) {
         (*it).second->setPosPlayer(player->getPosition());
        std::cout << "SIZE=" << m_mobs.size() << std::endl;
    }

}


void World::corpseDecayed(Event *event)
{
    log::messageln("Corpse decayed");
    MobCorpseDecayedEvent * ev = reinterpret_cast<MobCorpseDecayedEvent *>(event);

    removeChild(ev->mob);

    m_mobs.erase(ev->mob->getObjectID());
//    ev->mob->detach();
//    delete ev->mob;
}



void World::zombieAttacks(Event *event)
{
    std::cout << "ZOMBIE ATTACK!!!" << std::endl;

    ZombiePunchEvent * ev = reinterpret_cast<ZombiePunchEvent *>(event);

    RectT<Vector2> attack_box;
    attack_box = ev->attack_area;

/*
    spColorRectSprite rect = new ColorRectSprite();
    rect->setPosition(attack_box.getLeftTop());
    rect->setSize(attack_box.getSize());
    rect->attachTo(this);
*/

    RectT<Vector2> player_box = player->getRectPlayer();

	if (player_box.isIntersecting(attack_box))
	{
		player->takeDamage(ev->damage);
		gamescreen->setHp(gamescreen->getHp() - ev->damage);
	}
        
}


void World::onPlayerPunch(Event * event)
{
    std::cout << "PLAYER ATTACK!!!" << std::endl;
    PlayerPunchEvent * ev = reinterpret_cast<PlayerPunchEvent *>(event);


    RectT<Vector2> attack_box;
    attack_box = ev->attack_area;

/*
    spColorRectSprite rect = new ColorRectSprite();
    rect->setPosition((ev->attack_area).getLeftTop());
    rect->setSize((ev->attack_area).getSize());
    rect->attachTo(this);
*/

    for(auto it = m_mobs.begin(); it != m_mobs.end(); it++)
    {
        /*
        spColorRectSprite rect = new ColorRectSprite();
        rect->setPosition((*it)->getMobBox().getLeftTop());
        rect->setSize((*it)->getMobBox().getSize());
        rect->attachTo(this);
        */

        if(attack_box.isIntersecting((*it).second->getMobBox())) {
            (*it).second->getHit(ev->damage);
        }
    }
}


void World::checkBanana()
{
   RectT<Vector2> player_box = player->getCollisionBox();

   for(std::vector<Banana>::iterator i = m_bananas.begin(); i!=m_bananas.end(); i++){
       if(player_box.isIntersecting((*i).getCollisionBox()) == true) {
           player->addBanana();
           (*i).deleteBanana();
           m_bananas.erase(i);
           break;
       }
   }

}
