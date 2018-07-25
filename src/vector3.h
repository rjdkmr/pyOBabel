#ifndef VECTOR3_H
#define VECTOR3_H

const char* vector3Doc = R"f(Represents a vector in 3-dimensional real space.

The vector3 class was designed to simplify operations with floating
point coordinates. To this end many of the common operations have been
overloaded for simplicity. Vector addition, subtraction, scalar
multiplication, dot product, cross product, magnitude and a number of
other utility functions are built in to the vector class. For a full
description of the class member functions please consult the
documentation. The following code demonstrates several of the
functions of the vector class:

Example
-------

::

    v1, v2, v3 = vector3(), vector3(), vector3()
    v1.Set([1, 2, 3])
    v2.Set([4 ,5, 6])
    v3 = cross(v1,v2)
    v3 *= 2.5
    v3.normalize()

)f";

const char* Set1Doc = R"f(Set x,y and z-component of a vector
Parameters
----------
inX : float
    Input X-coordinate
inY : float
    Input Y-coordinate
inZ : float
    Input Z-coordinate

Returns
-------
None
)f";

const char* Set2Doc = R"f(Set x,y and z-component of a vector using a list
Parameters
----------
list : list
    Input X, Y and Z coordinates as list

Returns
-------
None
)f";

const char* SetXDoc = R"f(To set the x-coordinate of the vector
Parameters
----------
inX : float
    Input X-coordinate

Returns
-------
None
)f";

const char* SetYDoc = R"f(To set the y-coordinate of the vector
Parameters
----------
inX : float
    Input Y-coordinate

Returns
-------
None
)f";

const char* SetZDoc = R"f(To set the z-coordinate of the vector
Parameters
----------
inX : float
    Input Z-coordinate

Returns
-------
None
)f";

const char* GetXDoc = R"f(to Get the x-coordinate of the vector

Returns
-------
outX : float
    x-coordinate of the vector

)f";

const char* GetYDoc = R"f(to Get the y-coordinate of the vector

Returns
-------
outY : float
    y-coordinate of the vector

)f";

const char* GetZDoc = R"f(to Get the z-coordinate of the vector

Returns
-------
outZ : float
    z-coordinate of the vector

)f";

const char* GetDoc = R"f(To Get coordinates as a list

Returns
-------
list : list
    coordinates as a list

)f";

const char* copyDoc = R"f(To copy this vector

Parameters
----------
inpVector : vector3
    Vector to copy

Returns
-------
None
)f";

const char* randomUnitVectorDoc = R"f(
Create a random unit vector

Returns
-------
random : vector3
    Random unit vector

)f";

const char* normalizeDoc = R"f(Normalize the vector

Scales a vector to give it length one.

Returns
-------
normalized : vector3
    The normalized vector

)f";

const char* CanBeNormalizedDoc = R"f(Whether a vector can be normalized

Returns
-------
CanBeNormalize : bool
    True or False

)f";

const char* IsApproxDoc = R"f(Safe comparison for floating-point vector3

True if this vector is approximately equal to the other vector to the 
input precision. More specifically, this method works exactly like the 
pyOBabel.IsApprox() function, replacing the absolute value for 
doubles by the norm for vectors.

Parameters
----------
other : vector3
    The vector for comparison
precision : float
    This parameter plays the same role as in pyOBabel.IsApprox()

Returns
-------
IsApprox : bool
    True or False

)f";

const char* length2Doc = R"f(The length of the vector squared

Returns
-------
length2 : float
    The squared length of the vector

)f";

const char* lengthDoc = R"f(The length of the vector

Returns
-------
length : float
    The length of the vector

)f";

const char* distSqDoc = R"f(Square of distance between self and input vector.

square of the distance between self and vv.
equivalent to length_2(self-vv)

Parameters
----------
v : vector3
    Vector to copy

Returns
-------
length : float
    The square of distance between self and input vector

)f";

const char* createOrthoVectorDoc = R"f(Creates a vector of length one, orthogonal to this

Create a unit orthogonal vector

Returns
-------
v : vector3
    Unit orthogonal vector or `None` if not successfull 

)f";

const char* dotDoc = R"f(Dot product of two vectors

Parameters
----------
v1 : vector3
    First vector

v2 : vector3
    Second vector

Returns
-------
product : float
    Dot product of two vectors

)f";

const char* crossDoc = R"f(Cross product of two vectors

Parameters
----------
v1 : vector3
    First vector

v2 : vector3
    Second vector

Returns
-------
cross : vector3
    Cross product of two vectors

)f";

const char* vectorAngleDoc = R"f(Calculate the angle between vectors (in degrees)

Parameters
----------
v1 : vector3
    First vector

v2 : vector3
    Second vector

Returns
-------
angle : float
    Angle between vectors (in degrees)

)f";

const char* CalcTorsionAngleDoc = R"f(Calculate the torsion angle between vectors (in degrees)

Parameters
----------
a : vector3
    First vector

b : vector3
    Second vector

c : vector3
    Third vector

d : vector3
    fourth vector

Returns
-------
angle : float
    Torsion angle between vectors (in degrees)

)f";

const char* Point2PlaneSignedDoc = R"f(Calculate the signed distance of point a to the plane determined by b,c,d

Parameters
----------
a : vector3
    First vector

b : vector3
    Second vector

c : vector3
    Third vector

d : vector3
    fourth vector

Returns
-------
distance : float
    Signed distance between point to a plane

)f";

const char* Point2PlaneDoc = R"f(Calculate the distance of point a to the plane determined by b,c,d

Parameters
----------
a : vector3
    First vector

b : vector3
    Second vector

c : vector3
    Third vector

d : vector3
    fourth vector

Returns
-------
distance : float
    Distance between point to a plane

)f";

const char* Point2PlaneAngleDoc = R"f(Calculate the angle between point a and the plane determined by b,c,d

Parameters
----------
a : vector3
    First vector

b : vector3
    Second vector

c : vector3
    Third vector

d : vector3
    fourth vector

Returns
-------
angle : float
    angle between a point and plane

)f";

const char* Point2LineDoc = R"f(Calculate the distance of a point a to a line determined by b and c

Parameters
----------
a : vector3
    First vector

b : vector3
    Second vector

c : vector3
    Third vector

Returns
-------
distance : float
    Distance between a point and a line

)f";


#endif // VECTOR3_H
