#include "ShipFactory.h"

IEntity* ShipFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("ship") == 0) {
    std::cout << "Ship Created" << std::endl;
    return new Ship(entity);
  }
  return nullptr;
}

