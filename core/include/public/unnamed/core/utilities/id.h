#ifndef CORE_ID_H_
#define CORE_ID_H_

#pragma once

#include "config.h"

namespace CONFIG_NAMESPACE
{
    struct id
    {
        enum id_e
        {
            UNDEFINED = -1,
            SERVER,
            CLIENT,
        };

        static id_e id_g();
        static void set_id(id_e id);
    };
}

#endif /* CORE_ID_H_ */
