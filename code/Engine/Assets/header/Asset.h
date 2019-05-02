#ifndef ASSET_HH
#define ASSET_HH

#include "../../EngineObject.h"

class Asset : public EngineObject {
  public:
    virtual ~Asset();
    virtual bool canBeRemoved() const = 0;
};

#endif // ASSET_HH
