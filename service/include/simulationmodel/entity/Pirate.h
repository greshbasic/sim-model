#ifndef PIRATE_H_
#define PIRATE_H_

#include "IEntity.h"
#include "IStrategy.h"
#include "Human.h"
#include "Package.h"

class Pirate: public Human {
 public:
  /**
   * @brief Pirates are created with a name
   * @param obj JSON object containing the pirate's information
   */
  Pirate(const JsonObject& obj);

  ~Pirate();

  /**
   * @brief If there is one, get the next package to steal
   * setting this->package to said package
   */
  void getNextTarget();


  /**
   * @brief Updates the Pirate
   *
   * @param dt difference in time since last update
   */
  void update(double dt);

 protected:
  IStrategy* movement = nullptr;
  int packages_stolen = 0;
  Package* package = nullptr;
  bool lookingForPackage = false;
  Vector3 shipPosition = Vector3(498.292, 250, -228.623);
  bool headingToShip = false;
  bool available = true;
  bool lacksPackage = true;
};

#endif
