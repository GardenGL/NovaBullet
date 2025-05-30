#ifndef COLLIDER_H
#define COLLIDER_H

//  Created by Igor Kroitor on 29/12/15.

#include <stdio.h>

#include <cmath>

//-----------------------------------------------------------------------------
// Gilbert-Johnson-Keerthi (GJK) collision detection algorithm in 2D
// http://www.dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi/
// http://mollyrocket.com/849
// https://github.com/kroitor/gjk.c/tree/master
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Basic vector arithmetic operations

Math::vec2 subtract(Math::vec2 a, Math::vec2 b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}
Math::vec2 negateF(Math::vec2 v)
{
    v.x = -v.x;
    v.y = -v.y;
    return v;
}
Math::vec2 perpendicular(Math::vec2 v)
{
    Math::vec2 p = {v.y, -v.x};
    return p;
}
float dotProduct(Math::vec2 a, Math::vec2 b) { return a.x * b.x + a.y * b.y; }
float lengthSquared(Math::vec2 v) { return v.x * v.x + v.y * v.y; }

//-----------------------------------------------------------------------------
// Triple product expansion is used to calculate perpendicular normal vectors
// which kinda 'prefer' pointing towards the Origin in Minkowski space

Math::vec2 tripleProduct(Math::vec2 a, Math::vec2 b, Math::vec2 c)
{
    Math::vec2 r;

    float ac = a.x * c.x + a.y * c.y; // perform a.dot(c)
    float bc = b.x * c.x + b.y * c.y; // perform b.dot(c)

    // perform b * a.dot(c) - a * b.dot(c)
    r.x = b.x * ac - a.x * bc;
    r.y = b.y * ac - a.y * bc;
    return r;
}

//-----------------------------------------------------------------------------
// This is to compute average center (roughly). It might be different from
// Center of Gravity, especially for bodies with nonuniform density,
// but this is ok as initial direction of simplex search in GJK.

Math::vec2 averagePoint(const Math::vec2 *vertices, size_t count)
{
    Math::vec2 avg = {0.f, 0.f};
    for (size_t i = 0; i < count; i++)
    {
        avg.x += vertices[i].x;
        avg.y += vertices[i].y;
    }
    avg.x /= count;
    avg.y /= count;
    return avg;
}

//-----------------------------------------------------------------------------
// Get furthest vertex along a certain direction

size_t indexOfFurthestPoint(const Math::vec2 *vertices, size_t count, Math::vec2 d)
{
    float maxProduct = dotProduct(d, vertices[0]);
    size_t index = 0;
    for (size_t i = 1; i < count; i++)
    {
        float product = dotProduct(d, vertices[i]);
        if (product > maxProduct)
        {
            maxProduct = product;
            index = i;
        }
    }
    return index;
}

//-----------------------------------------------------------------------------
// Minkowski sum support function for GJK

Math::vec2 support(const Math::vec2 *vertices1, size_t count1,
                  const Math::vec2 *vertices2, size_t count2, Math::vec2 d)
{
    // get furthest point of first body along an arbitrary direction
    size_t i = indexOfFurthestPoint(vertices1, count1, d);

    // get furthest point of second body along the opposite direction
    size_t j = indexOfFurthestPoint(vertices2, count2, negateF(d));

    // subtract (Minkowski sum) the two points to see if bodies 'overlap'
    return subtract(vertices1[i], vertices2[j]);
}

//-----------------------------------------------------------------------------
// The GJK yes/no test

int iter_count = 0;

int gjk(const Math::vec2 *vertices1, size_t count1,
        const Math::vec2 *vertices2, size_t count2)
{
    size_t index = 0; // index of current vertex of simplex
    Math::vec2 a, b, c, d, ao, ab, ac, abperp, acperp, simplex[3];

    Math::vec2 position1 = averagePoint(vertices1, count1); // not a CoG but
    Math::vec2 position2 = averagePoint(vertices2, count2); // it's ok for GJK )

    // initial direction from the center of 1st body to the center of 2nd body
    d = subtract(position1, position2);

    // if initial direction is zero - set it to any arbitrary axis (we choose X)
    if ((d.x == 0) && (d.y == 0))
        d.x = 1.f;

    // set the first support as initial point of the new simplex
    a = simplex[0] = support(vertices1, count1, vertices2, count2, d);

    if (dotProduct(a, d) <= 0)
        return 0; // no collision

    d = negateF(a); // The next search direction is always towards the origin, so the next search direction is negate(a)

    while (1)
    {
        iter_count++;

        a = simplex[++index] = support(vertices1, count1, vertices2, count2, d);

        if (dotProduct(a, d) <= 0)
            return 0; // no collision

        ao = negateF(a); // from point A to Origin is just negative A

        // simplex has 2 points (a line segment, not a triangle yet)
        if (index < 2)
        {
            b = simplex[0];
            ab = subtract(b, a);           // from point A to B
            d = tripleProduct(ab, ao, ab); // normal to AB towards Origin
            if (lengthSquared(d) == 0)
                d = perpendicular(ab);
            continue; // skip to next iteration
        }

        b = simplex[1];
        c = simplex[0];
        ab = subtract(b, a); // from point A to B
        ac = subtract(c, a); // from point A to C

        acperp = tripleProduct(ab, ac, ac);

        if (dotProduct(acperp, ao) >= 0)
        {
            d = acperp; // new direction is normal to AC towards Origin
        }
        else
        {
            abperp = tripleProduct(ac, ab, ab);

            if (dotProduct(abperp, ao) < 0)
                return 1; // collision

            simplex[0] = simplex[1]; // swap first element (point C)

            d = abperp; // new direction is normal to AB towards Origin
        }

        simplex[1] = simplex[2]; // swap element in the middle (point B)
        --index;
    }

    return 0;
}

//-----------------------------------------------------------------------------
#include <Engine.hpp>

#include <stdlib.h>
#include <float.h>

// Helper function to rotate a point around a center
Math::vec2 rotatePoint(Math::vec2 point, Math::vec2 center, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    // translate point back to origin
    point.x -= center.x;
    point.y -= center.y;

    // rotate point
    float xnew = point.x * c - point.y * s;
    float ynew = point.x * s + point.y * c;

    // translate point back
    return Math::vec2(xnew + center.x, ynew + center.y);
}

int CheckCollision(Rect rec1, Rect rec2, float rotation1 = 0.0f, float rotation2 = 0.0f)
{
    rec1.width /= 2;
    rec1.height /= 2;

    rec2.width /= 2;
    rec2.height /= 2;
    
    Math::vec2 center1 = {rec1.x, rec1.y};
    Math::vec2 center2 = {rec2.x, rec2.y};

    // Create vertices for first rectangle
    Math::vec2 vertices1[] = {
        {-rec1.width, -rec1.height},
        {-rec1.width, rec1.height},
        {rec1.width, -rec1.height},
        {rec1.width, rec1.height},
    };

    // Create vertices for second rectangle
    Math::vec2 vertices2[] = {
        {-rec2.width, -rec2.height},
        {-rec2.width, rec2.height},
        {rec2.width, -rec2.height},
        {rec2.width, rec2.height},
    };

    // Rotate and translate vertices
    for (int i = 0; i < 4; i++)
    {
        vertices1[i] = rotatePoint(vertices1[i], Math::vec2(0, 0), rotation1);
        vertices1[i] += center1;
        
        vertices2[i] = rotatePoint(vertices2[i], Math::vec2(0, 0), rotation2);
        vertices2[i] += center2;
    }

    size_t count1 = sizeof(vertices1) / sizeof(Math::vec2);
    size_t count2 = sizeof(vertices2) / sizeof(Math::vec2);

    int collisionDetected = gjk(vertices1, count1, vertices2, count2);
    return collisionDetected;
}

void DrawCollieder(Math::mat4x4 view, Rect rect, float rotation = 0.0f, Math::vec4 color = Color::green)
{
    // Получаем половины ширины и высоты для удобства
    float halfW = rect.width / 2;
    float halfH = rect.height / 2;
    
    // Угловые точки прямоугольника (до вращения)
    Math::vec2 vertices[] = {
        {-halfW, -halfH}, // левый нижний
        {-halfW,  halfH}, // левый верхний
        { halfW,  halfH}, // правый верхний
        { halfW, -halfH}  // правый нижний
    };
    
    // Центр прямоугольника
    Math::vec2 center = {rect.x, rect.y};
    
    // Вращаем и смещаем точки
    for (auto& v : vertices)
    {
        v = rotatePoint(v, Math::vec2(0, 0), rotation);
        v += center;
    }
    
    // Рисуем линии между вершинами
    for (int i = 0; i < 4; i++)
    {
        int next = (i + 1) % 4; // Следующая вершина (с замыканием на первую)
        Draw2D::Line(vertices[i], vertices[next], color);
    }
    
    Draw2D::Line_Render();
}

#endif