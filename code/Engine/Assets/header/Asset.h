#ifndef ASSET_HH
#define ASSET_HH

#include "../../header/EngineObject.h"

class Asset : public EngineObject {
public:
    virtual bool canBeRemoved() const = 0;
};

#endif // ASSET_HH
