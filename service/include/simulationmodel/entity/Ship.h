#ifndef SHIP_H_
#define SHIP_H_

#include "IEntity.h"
#include "IStrategy.h"

class Ship : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Ship(const JsonObject& obj);

  ~Ship();

  void update(double dt);
};

#endif
