#ifndef CORE_OBJECTS_HPP_
#define CORE_OBJECTS_HPP_

#pragma once

#include "config.h"

#include <vector>
#include <memory>

namespace CONFIG_NAMESPACE
{
    namespace game
    {
        namespace objects
        {
            class object;
            class world;
            class world_object;

            class object
            {
            public:
                virtual ~object() = default;
            };

            class world : public object
            {
            private:
                std::shared_ptr<std::vector<world_object>> objects_ = std::make_shared<std::vector<world_object>>();

            public:
                const std::weak_ptr<std::vector<world_object>> objects() const noexcept;
            };

            class world_object : public object
            {
            private:
                std::weak_ptr<world> parent_;

            public:
                world_object(std::weak_ptr<world> world);

                const std::weak_ptr<world> parent() const noexcept;
            };
        }
    }
}

#endif /* CORE_OBJECTS_HPP_ */
