#include "core/utilities/id.h"

#include <string>

#include <stdexcept>

namespace
{
    static id::id_e id_ = id::UNDEFINED;
}

id::id_e id::id_g() {
    if (id_ == id::UNDEFINED) throw std::runtime_error("ID is not set yet.");
    return id_;
}
void id::set_id(id::id_e id) {
    if (id == id::UNDEFINED) throw std::runtime_error("Cannot set ID to undefined.");
    id_ = id;
}
