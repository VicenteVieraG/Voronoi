Parabola's Ecuations Review
======================================================================
Quick parabola review. This will help to understand better how to implement fortune's algorithm because, this method is based in the use of the parabola's geometry to compute the Voronoi's diagrams.

## Definition
It can be geometricaly defined by the expression:
$$d(P, F) = d(P, D)$$

Where
- $d$ is a distance between two points function that takes two points as parameters.
- $P$ can be any point.
- $F$ is the focal point.
- $D$ is a a point belonging to the directrix.

In other words, it can be defined as the set of points whose distance to a point called *Focus* is the same as its distance to a rect called *Directrix*.

## Parabola's Ecuation Structure
### General/Cuadratic
The most common way for representing a parabola:
$$y = ax^2 + bx + c$$
### Canonic
Where $(h, k)$ is the vertex of the parabola and $P$ is the distance between the *Vertext* and *Focus*:
#### Vertical
It is vertical when the symmetry axis is parallel to the Y axis in the plane.
$$(y - k)^2 = 4p(x - h)$$
__When__:
- $p > 0$: Parabola opens upwards $\uparrow$
- $p < 0$: Parabola opens downwards $\downarrow$
#### Horizontal
It is horizontal when the symmetry axis is parallel to the X axis in the plane.
$$(x - h)^2 = 4p(y - k)$$
__When__:
- $p > 0$: Parabola opens to the right $\rightarrow$
- $p < 0$: Parabola opens to the left $\leftarrow$

![Parabola_directions](../assets/parabola_directions.png)

## Parabola's Components
### Vertex
It is the lowest point of the parabola. Is the point where the curve changes its direction. Also it is the middle point between the directrix and the focus.
### Focus
It is a fixed point inside the parabola. The parabola is defined such as that any parabola's point is at the same distance from the focus than from the directrix.
### Directrix
It is a straight line outside the parabola and it is perpendicular to the symmetry axis.
### Symmetry axis
It is a straight line that passes through the vertex and focus, dividing the parabola in two symmetryc parts.
### Latus rectum
A straight line segment perpendicular to the symmetry axis and that passes through the focus. Its lenght is defined as $4p$, where $p$ is the distance from the vertex to the focus.
### Radius vector
The distance from any given parabola's point to the focus.

![Parabola_components](../assets/parabola_components.png)