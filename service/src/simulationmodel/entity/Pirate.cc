#define _USE_MATH_DEFINES
#include "Pirate.h"
#include "Human.h"

#include <cmath>
#include <limits>

#include "BeelineStrategy.h"
#include "AstarStrategy.h"
#include "SimulationModel.h"
#include "Package.h"

Pirate::Pirate(const JsonObject& obj) : Human(obj) {}

Pirate::~Pirate() {
  if (movement) delete movement;
  if (package) delete package;
}

void Pirate::getNextTarget() {
    if (model && model->newestDelivery) {
        package = model->newestDelivery;
        model->newestDelivery = nullptr;
        if (package && package->canBeStolen) {
            lookingForPackage = true;
            available = false;
        }
    }
}

void Pirate::update(double dt) {
    if (available) {
        // pirate has no particular task at the moment be it
        // no packages to steal or pirate just dropped off a package
        if (!movement || (movement && movement->isCompleted())) {
            Vector3 dest;
            int random_x = static_cast<int>(rand()) % 301;
            int plus_or_minus_x = static_cast<int>(rand()) % 2;
            if (plus_or_minus_x == 1) {
                dest.x = position.x + random_x;
            } else {
                dest.x = position.x - random_x;
            }

            dest.y = position.y;

            int random_z = static_cast<int>(rand()) % 301;
            int plus_or_minus_z = static_cast<int>(rand()) % 2;
            if (plus_or_minus_z == 1) {
                dest.z = position.z + random_z;
            } else {
                dest.z = position.z - random_z;
            }


            if (model) {
                const routing::Graph* g = model->getGraph();
                movement = new AstarStrategy(position, dest, g);
            }
        } else if (movement) {
            movement->move(this, dt);
        }
    }

    if (headingToShip == true) {
        // pirate is heading to the ship
        package->setPosition(position);
        package->setDirection(direction);
        if (movement && !movement->isCompleted()) {
            movement->move(this, dt);
        }
        if (position.dist(shipPosition) <= 16) {
            delete movement;
            headingToShip = false;
            lacksPackage = true;
            movement = nullptr;
            available = true;
        }
    } else if (lookingForPackage == true) {
        // pirate is looking for a package
        if (!package->canBeStolen) {
            // package has been picked up by robot first
            delete movement;
            // starts to head to ship just as buffer
            const routing::Graph* g = model->getGraph();
            movement = new AstarStrategy(position, shipPosition, g);
            lookingForPackage = false;
            available = true;
        } else {
            double dist_to_package = position.dist(package->getPosition());
            // pirate is in range to detect package
            // and will now attempt to steal it
            bool under_1000 = dist_to_package <= 1000;
            bool over_15 = dist_to_package > 15;
            if (under_1000 && over_15 && lacksPackage) {
                Vector3 dest = package->getPosition();
                movement = new BeelineStrategy(position, dest);
                lacksPackage = false;
                movement->move(this, dt);
            } else if (dist_to_package <= 15) {
                // pirate is in range to steal package
                delete movement;
                model->pirates_can_steal = false;
                packages_stolen += 1;
                package->stolen = true;
                std::string message;
                message = (getName() + " has stolen: " +
                package->getName()
                + "!!!\n They have now stolen " +
                std::to_string(packages_stolen));
                if (packages_stolen <= 1) {
                    message += " package!";
                } else {
                    message += " packages!";
                }
                notifyObservers(message);
                lookingForPackage = false;
                const routing::Graph* g = model->getGraph();
                movement = new AstarStrategy(position, shipPosition, g);
                headingToShip = true;
                package->setPosition(position);
                package->setDirection(direction);
            } else {
                // pirate is not in range to detect package,
                // move around randomly in the meantime
                if (movement && movement->isCompleted()) {
                    delete movement;
                    Vector3 dest;
                    dest.x = ((static_cast<double>(rand())) / RAND_MAX)
                     * (2900) - 1400;
                    dest.y = position.y;
                    dest.z = ((static_cast<double>(rand())) / RAND_MAX)
                     * (1600) - 800;
                    if (model) {
                        const routing::Graph* g = model->getGraph();
                        movement = new AstarStrategy(position, dest, g);
                    }
                } else if (movement) {
                    movement->move(this, dt);
                }
            }
        }
    }
}
