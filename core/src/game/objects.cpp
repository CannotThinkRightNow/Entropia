#include "config.h"
#include STR(CONFIG_NAMESPACE/core/game/objects.hpp)

using namespace std;

namespace CONFIG_NAMESPACE
{
    namespace game
    {
        namespace objects
        {
            //////////////////////////////////////////////////
            // class world
            //////////////////////////////////////////////////

            const weak_ptr<vector<world_object>> world::objects() const noexcept
            {
                return weak_ptr<vector<world_object>>(objects_);
            }

            //////////////////////////////////////////////////
            // class world_object
            //////////////////////////////////////////////////

            world_object::world_object(const weak_ptr<world> parent)
            {
                parent_ = parent;
            }

            const weak_ptr<world> world_object::parent() const noexcept
            {
                return parent_;
            }
        }
    }
}
