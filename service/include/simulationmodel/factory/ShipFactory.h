#ifndef SHIP_FACTORY_H_
#define SHIP_FACTORY_H_

#include <vector>

#include "Ship.h"
#include "IEntityFactory.h"

/**
 *@brief Ship Factory to produce Ship class.
 **/
class ShipFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for ShipFactory class.
   **/
  virtual ~ShipFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif
