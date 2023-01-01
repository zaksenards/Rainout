#include <rainout/engine.h>
#include <cstdio>
#include <vector>

using rainout::AssetManager;
using rainout::Keyboard;
using rainout::Texture;
using rainout::Entity;
using rainout::Scene;
using rainout::Vec2f;
using rainout::Vec3f;

class Tile
{
    public:
        Tile(Vec2f position, const char* text)
        {
            _texture = AssetManager::loadTexture(text);
            _entity = Scene::createEntity(_texture);
            _entity->translate(position);
        }

        ~Tile()
        {
            delete _entity;
        }

        void move(Vec2f translation)
        {
            _entity->translate(translation);
        }


        Vec2f getPosition()
        {
            return _entity->getTransform().position;
        }

        void scale(Vec2f scale)
        {
            _entity->scale(scale);
        }

        Entity* getEntity()
        {
            return _entity;
        }

    private:
        Texture* _texture;
        Entity* _entity;
};
Tile* player;
std::vector<Tile*> shoots;
const float shootColldown = 4.0f;
static float elapsed = 0.0f;

void onInit(GameSettings* settings)
{
    settings->title = (char*)"Aircraft";
    settings->height = 600;
    settings->width = 800;
    settings->backColor = Vec3f(0.1f, 0.1f, 0.1f);
}

void onStart()
{
    player = new Tile(Vec2f(0.0f, 0.0f), "assets/aircraft.bmp");
}

void onUpdate(float dt)
{
    Vec2f motion;
    motion.x = (float) (Keyboard::isKeyDown(VKCODE_D) - Keyboard::isKeyDown(VKCODE_A))*dt*0.5f;
    motion.y = (float) (Keyboard::isKeyDown(VKCODE_W) - Keyboard::isKeyDown(VKCODE_S))*dt*0.5f;

    if(Keyboard::isKeyDown(VKCODE_F) && elapsed >= shootColldown)
    {
        Vec2f position = player->getPosition();
        Tile* shoot = new Tile(position, "assets/shoot.bmp");
        shoot->scale(Vec2f(0.015f, 0.015f));
        shoots.push_back(shoot);
        elapsed = 0;
    }
    elapsed+=0.5f;
    
    for(size_t i = 0; i < shoots.size(); i++)
    {
        Tile* shoot = shoots.at(i);
        shoot->move(Vec2f(0.0f, 1.0f*dt));
        if(shoot->getPosition().y > 1.2f)
        {
            Scene::removeEntity(shoot->getEntity());
            shoots.erase(shoots.begin()+i);
            delete shoot;
        }
    }

    player->move(motion);
}

void onStop()
{
    for(size_t i = 0; i < shoots.size(); i++)
    {
        Tile* shoot = shoots.at(i);
        shoots.erase(shoots.begin()+i);
        delete shoot;
    }
    delete player;
}
