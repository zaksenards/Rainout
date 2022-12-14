#ifndef rainout_scene_h
#define rainout_scene_h
#include <rainout/assetManager.h>
#include <rainout/rainout.h>
#include <rainout/entity.h>
#include <vector>

namespace rainout
{
    struct RAINOUT Scene
    {
        static Entity* createEntity(Texture* texture);
        static Entity* createEntity();
        static void removeEntity(Entity* entity);
        static void render();
        static void destroy();
    };
}

#endif//rainout_scene_h
