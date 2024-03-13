#pragma once

#include "Point.h"
#include "SegmentLine.h"

#include <ostream>

class Polygon;    // Forward declaration due to circular reference betwen both classes

class Vertex : public Point
{
protected:
    const static int INVALID_POSITION = -1;

protected:
    Polygon* _polygon;     //!< Polygon where the vertex belongs to
    int      _position;    //!< Position of the vertex in the polygon

public:
    /**
     *  @brief Constructor of a vertex no associated to any polygon (position = -1).
     */
    Vertex();

    /**
     *  @brief Constructor of a vertex no associated to any polygon (position = -1). The point is valid tho.
     */
    Vertex(const Point& point);

    /**
     *  @brief Constructor of a valid point associated to a polygon.
     */
    Vertex(const Point& point, Polygon* polygon, int pos = -1);

    /**
     *  @brief Destructor.
     */
    virtual ~Vertex();

    /**
     *  @brief Determines if the vertex is in a concave position of the polygon.
     */
    bool concave();

    /**
     *  @brief Determines if the vertex is in a convex position of the polygon.
     */
    bool convex();

    /**
     *  @brief Returns the point value.
     */
    Point getPoint() { return Point(_x, _y); }

    /**
     *  @brief Returns the polygon associated to this vertex.
     */
    Polygon* getPolygon() { return _polygon; }

    /**
     *  @brief Returns the position of the current vertex in the polygon, if any.
     */
    int getPositionInPolygon() { return _position; }

    /**
     *  @brief Next vertex in counterclockwise order.
     */
    Vertex next();

    /**
     *  @brief Next edge in counterclockwise order.
     */
    SegmentLine nextEdge();

    /**
     *  @brief Assignment operator.
     */
    Vertex& operator=(const Vertex& vertex);

    /**
     *  @brief Overriding cout call.
     */
    friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);

    /**
     *  @brief Next vertex in clockwise order.
     */
    Vertex previous();

    /**
     *  @brief Next edge in clockwise order.
     */
    SegmentLine previousEdge();

    /**
     *  @brief Modifies the coordinates of the vertex.
     */
    void setPoint(Point& point)
    {
        _x = point.getX();
        _y = point.getY();
    }

    /**
     *  @brief Modifies the polygon associated to this vertex.
     */
    void setPolygon(Polygon* polygon) { _polygon = polygon; }

    /**
     *  @brief Modifies the position of the vertex in the polygon, if any.
     */
    void setPosition(int pos) { _position = pos; }
};
