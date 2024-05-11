****************************
General Overview:

This project is a drone delivery simulation, specifically one that occurs within a model of the University of Minnesota Twin Cities campus. 
Various entities such as humans, a helicopter, and pirates will wander about the simulation, but the main functionality of the simulation is observed when
a user schedules a delivery. Once scheduled, a drone will 'spawn' and head towards the selected pick up point and retrieve a newly spawned package. After which
the drone will head to the drop off point where a new robot entity has spawned nearby. If a pirate is close enough, it will race the robot to the package in hopes 
of stealing it. 
****************************
How to run: 

Git: After cloning the repository, user must run `make -j` at top of directory, then can run `make run` The simulation will be hosted locally on port 8081
so after connecting to localhost:8081 the simulation will automatically load and start running.

Docker: After pulling the docker image, user must run `docker run --rm -it -p 8081:8081 greshbasic/final-project` As with git, user will then need to connect to localhost:8081
and the simulation will automatically load and start running from there.
****************************
Detailed Overview:

As mentioned, the simulation simulates a drone delivery service within the UMN Twin Cities campus. Within the simulation there are various entities with different
behaviors. To list them: humans that will walk around the simulation, alterting the user upon walking near Keller. A helicopter flies around the map alerting the user
every mile it travels. Drones will fulfill deliveries with the strategy, package pick-up location, package drop-off location, and package name all being decided by the user, after 
dropping off the package the drone will dance and or spin depending on the strategy used. Robots will spawn in with each delivery to act as the reciever, having to walk to the pick-up
site in order to get their package, at which point the robot will dance. Pirates will roam the map, randomly patrolling in order to detect in-range packages, and if they are close enough
the pirate(s) will run to the package in hopes to arrive before the reciever robot to steal it. After succesfully stealing the package the pirate will return to their pirate ship
and drop off the package.
****************************
Extension Overview:

New Feature
- Elected to incoporate 'porch pirates' as the new feature.

What does it do?
-  As mentioned in the overviews, this feature simulations porch pirates, entities with the intent of
stealing packages from people before they arrive home. The pirates will return the package to their pirate ship if succesfull in their pirating, regardless if the pirate fails
or succeeds, it will go back to patrolling, waiting for another package to attempt to steal.

Why is it significantly interesting?
- The original simulation does not have much "interaction" between entities. The most interaction comes from drones delivering packages to robots but the robots themselves
don't actually participate in the delivery, they just stand, doing nothing until the package arrives. The addition of porch pirates adds not only further interactions between entities,
but competition. This competition makes the simulation less predictable and more interesting.

Which design pattern(s) did you choose to use in your implementation, and why?
- The factory design pattern was used in order to seamlessly incorporate the pirates and their pirate ship, but the main design pattern used was the observer pattern.
This pattern allows the simulation to 'notify' the pirates and robots of package delivery, initiating their race to the package.

Instructions to use this new feature. if the new feature is not user interactable, please mention this as well
- The new feature automatically occurs whenever a package is scheduled for delivery. However, if the user wants the pirate to be more likely to win said user should
place the drop off location as near to the pirate as possible.
****************************
UML Diagram:
<object data="https://github.umn.edu/umn-csci-3081-s24/team-010-13-finalproject/blob/dev_branch/PDFs/3081WPorchPirateUML.pdf" type="application/pdf" width="700px" height="700px">
    <embed src="https://github.umn.edu/umn-csci-3081-s24/team-010-13-finalproject/blob/dev_branch/PDFs/3081WPorchPirateUML.pdf">
        <p>This browser does not support PDFs. Please download the PDF to view it: <a href="https://github.umn.edu/umn-csci-3081-s24/team-010-13-finalproject/blob/dev_branch/PDFs/3081WPorchPirateUML.pdf">Download PDF</a>.</p>
    </embed>
</object>
****************************
