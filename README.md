# 2DPhysicsProgram
 
A physics simulation program made in OpenGL.


## Environment

The environment I created is essentially a vacuum with only the effect of gravity impacting the objects.
This was done to keep the environment as simple as possible, though there is also code to add air to 
the environment, where air density and shape area is taken into account to calculate the terminal
velocity of objects - though the constraint code for this was left very simple. 
Moments of shapes are calculated on construction, then ambient forces and their impacts are calculated 60
times per second.

![](https://github.com/DragonKJM/2DPhysicsProgram/Media/2DPhysicsProgram_82Z6m3j9nP.gif)


## Colliders

Colliders are created separately to the shape itself, as the code is set up so that they can be custom
to each object. For example, when creating a new object, a box object may be made, but this box can 
then be given a circle collider, and the idea would be that a collider would be estimated based on it's
size. Currently, the code is only capable of creating box colliders, as well as box objects, but the 
concept works through the use of a factory and an enum. The user declares what collider type they want
a shape to have, this is then passed to the factory which will then attach the requested collider to
a pointer. 

![](https://github.com/DragonKJM/2DPhysicsProgram/Media/Screenshot1.jpg)

![](https://github.com/DragonKJM/2DPhysicsProgram/Media/Screenshot2.jpg)


## Collisions - Broad Phase

The broad phase of the collision detection uses a Sort and Sweep algorithm, so that all of the
objects are ordered relevantly. I went for the commonly-used x-axis ordering, where my objects are 
ordered from left to right. The program then sweeps across this x-axis, checking if the rightmost
point of the object is further than the leftmost point of the next object, and if so, adding the
current and next object to a list of 'active' objects. The program then checks for any shapes 
that were duplicated and removes the duplicate from the list.

![](https://github.com/DragonKJM/2DPhysicsProgram/Media/Screenshot3.jpg)


## Collisions - Narrow Phase

The narrow phase consists of comparing, from left to right, each active shape to the adjacent active 
shape. First, a flag is added to tell the collider that the shape is in a narrow phase check. This 
converts the collider in most cases to a more accurate version of itself, for example AABBs become 
OBBs, and more advanced shapes would become convex. The outlier to this would be circles.
Following this, a simple check is performed to determine what types of colliders are being compared,
with the idea in my program that, when possible, more basic calculations will be performed. 
Upon determining this, a SAT algorithm is used in order to determine if there are any gaps in-between
the two shapes - if not, then a collision has occurred. 

![](https://github.com/DragonKJM/2DPhysicsProgram/Media/Screenshot4.jpg)


## Collisions - Resolution

This is as far as I have gotten with this project so far, but I hope to revisit it in the future
when I have more time available and continue from here.
