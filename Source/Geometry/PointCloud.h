#pragma once

#include "Point.h"

#include <string>
#include <vector>

namespace GDSA::Geometry
{
class PointCloud
{
protected:
    std::vector<Point> _points;

public:
    /**
     *  @brief Default constructor. Creates an empty point cloud.
     */
    PointCloud();

    /**
     *  @brief Constructor of a point cloud of random form giving the total number of points and the maximum range of those points ((-max_x, max_x), or (-max_y, max_y)).
     */
    PointCloud(int size, double max_x, double max_y);

    /**
     *  @brief Construct the point cloud from a vector of points
     */
    PointCloud(const std::vector<Point>& points);

    /**
     *  @brief Constructor of a point cloud from the coordinates of points stored in file.
     */
    PointCloud(const std::string& filename);

    /**
     *  @brief Destructor.
     */
    ~PointCloud();

    /**
     *  @brief Adds a point to the point cloud.
     */
    void addPoint(const Point& p);

    /**
     *  @brief Returns the points that minimizes the distance to any point from the cloud.
     */
    Point centralPoint();

    /**
     *  @brief Deletes a point identified by its index.
     */
    void deletePoint(int index);

    /**
     *  @brief Returns the points that defines the edges of the point cloud (min x, max x, min y and max y).
     */
    void getEdges(Point& minPoint_x, Point& minPoint_y, Point& maxPoint_x, Point& maxPoint_y);

    /**
     *  @brief Returns the point in an specific index.
     */
    Point getPoint(size_t position);

    /**
     *  @brief Returns all the available points as a vector.
     */
    std::vector<Point> getPoints() { return _points; }

    /**
     *  @brief Assignment operator.
     */
    PointCloud& operator=(const PointCloud& pointCloud);

    /**
     *  @brief Saves the cloud of points in file with the same format used by the constructor.
     */
    void save(const std::string& filename);

    /**
     *  @brief Returns the size of the point cloud.
     */
    size_t size() const { return _points.size(); }
};
}    // namespace GDSA::Geometry