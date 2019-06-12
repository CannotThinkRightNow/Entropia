#include "config.h"
#include STR(CONFIG_NAMESPACE/core/game/objects.hpp)

namespace CONFIG_NAMESPACE
{
    namespace game
    {
        namespace objects
        {
            //////////////////////////////////////////////////
            // class world
            //////////////////////////////////////////////////

            const std::vector<world_object> world::objects() const noexcept
            {
                return std::vector<world_object>();
            }
        }
    }
}
