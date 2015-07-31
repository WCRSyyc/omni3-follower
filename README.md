# 3 Omni Wheel line follower

Arduino sketch code for a 3 [Omni Wheel](https://en.wikipedia.org/wiki/Omni_Wheel) (also called Poly Wheel) based line follower robot.

The physical structure for the robot chassis is based on an equalateral triangle base, with a single wheel on each edge
The electronics are mounted on (somewhat smaller) triangular layers above the main base, and a bottom layer is hung
below the main chasis to hold the line follower sensors just above the floor.  The points of the chassis layer are
truncated, turning it into a six sided shape, with 3 long and 3 shorter edges.  Currently the bottom sensor layer is cut
to the same shape and size as the chassis layer, but it really only needs to be large enough to hold the circle of
downward sensors.  The mount points could be moved inside of the sensor circle.

This layout is more robust to variations in the driving surface than the [four omni wheel](https://github.com/WCRSyyc/omni4-follower)
robot.  With only 3 contact points, it can tilt to match surface contours, and maintain contact and traction on all wheels.
