#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

#include "IStrategy.h"

class Package;

/**
 * @class Robot
 * @brief Represents a robot in a physical system
 *
 * Robots move using euler integration based on a specified
 * velocity and direction.
 */
class Robot : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the robot's information
   */
  Robot(const JsonObject& obj);

  /**
   * @brief Updates the Robot
   *
   * @param dt difference in time since last update
   */
  void update(double dt);

  /**
   * @brief Receives the passed in package
   *
   * @param Package* Package to be received by the robot
   */
  void receive(Package* p);

  bool requestedDelivery = true;
  bool canPickUpPackage = true;
  IStrategy* movement = nullptr;
  Vector3 original_position;


 protected:
  Package* package = nullptr;
};

#endif  // ROBOT_H
