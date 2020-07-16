#ifndef ROUTER_H
#define ROUTER_H

#include <functional>
#include "link.h"

namespace Models {
struct Router {
    Link link;
    std::function<void (QByteArray)> handler;
};
}

#endif // ROUTER_H
