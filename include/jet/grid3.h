// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_GRID3_H_
#define INCLUDE_JET_GRID3_H_

#include <jet/size3.h>
#include <jet/bounding_box3.h>
#include <functional>
#include <utility>  // just make cpplint happy..

namespace jet {

//!
//! \brief Abstract base class for 3-D cartesian grid structure.
//!
//! This class represents 3-D cartesian grid structure. This class is an
//! abstract base class and does not store any data. The class only stores the
//! shape of the grid. The grid structure is axis-aligned and can have different
//! grid spacing per axis.
//!
class Grid3 {
 public:
    //! Function type for mapping data index to actual position.
    typedef std::function<Vector3D(size_t, size_t, size_t)> DataPositionFunc;

    //! Constructs an empty grid.
    Grid3();

    //! Default destructor.
    virtual ~Grid3();

    //! Returns the grid resolution.
    const Size3& resolution() const;

    //! Returns the grid origin.
    const Vector3D& origin() const;

    //! Returns the grid spacing.
    const Vector3D& gridSpacing() const;

    //! Returns the bounding box of the grid.
    const BoundingBox3D& boundingBox() const;

    //! Returns the function that maps grid index to the cell-center position.
    DataPositionFunc cellCenterPosition() const;

    //!
    //! \brief Invokes the given function \p func for each grid cell.
    //!
    //! This function invokes the given function object \p func for each grid
    //! cell in serial manner. The input parameters are i and j indices of a
    //! grid cell. The order of execution is i-first, j-next, k-last.
    //!
    void forEachCellIndex(
        const std::function<void(size_t, size_t, size_t)>& func) const;

    //!
    //! \brief Invokes the given function \p func for each grid cell parallelly.
    //!
    //! This function invokes the given function object \p func for each grid
    //! cell in parallel manner. The input parameters are i and j indices of a
    //! grid cell. The order of execution can be arbitrary since it's
    //! multi-threaded.
    //!
    void parallelForEachCellIndex(
        const std::function<void(size_t, size_t, size_t)>& func) const;

    //! Serializes the grid instance to the output stream \p strm.
    virtual void serialize(std::ostream* strm) const = 0;

    //! Deserializes the input stream \p strm to the grid instance.
    virtual void deserialize(std::istream* strm) = 0;

    //! Returns true if resolution, grid-spacing and origin are same.
    bool hasSameShape(const Grid3& other) const;

    //! Swaps the data with other grid.
    virtual void swap(Grid3* other) = 0;

 protected:
    //! Sets the size parameters including the resolution, grid spacing, and
    //! origin.
    void setSizeParameters(
        const Size3& resolution,
        const Vector3D& gridSpacing,
        const Vector3D& origin);

    //! Swaps the size parameters with given grid \p other.
    void swapGrid(Grid3* other);

    //! Sets the size parameters with given grid \p other.
    void setGrid(const Grid3& other);

    //! Serializes the size parameters to given output stream \p strm.
    void serializeGrid(std::ostream* strm) const;

    //! Deserializes the size parameters from given input stream \p strm.
    void deserializeGrid(std::istream* strm);

 private:
    Size3 _resolution;
    Vector3D _gridSpacing = Vector3D(1, 1, 1);
    Vector3D _origin;
    BoundingBox3D _boundingBox = BoundingBox3D(Vector3D(), Vector3D());
};

}  // namespace jet

#endif  // INCLUDE_JET_GRID3_H_
