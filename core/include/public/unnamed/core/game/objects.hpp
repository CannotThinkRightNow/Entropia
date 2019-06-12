#ifndef CORE_OBJECTS_HPP_
#define CORE_OBJECTS_HPP_

#pragma once

#include "config.h"

#include <vector>

namespace CONFIG_NAMESPACE
{
    namespace game
    {
        namespace objects
        {
            class object
            {

            };

            class world_object : public object
            {

            };

            class world : public object
            {
                virtual const std::vector<world_object> objects() const noexcept;
            };
        }
    }
}

#endif /* CORE_OBJECTS_HPP_ */
