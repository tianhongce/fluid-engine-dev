// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_CUSTOM_VECTOR_FIELD2_H_
#define INCLUDE_JET_CUSTOM_VECTOR_FIELD2_H_

#include <jet/vector_field2.h>

namespace jet {

//! 2-D vector field with custom field function.
class CustomVectorField2 final : public VectorField2 {
 public:
    //!
    //! \brief Constructs a field with given function.
    //!
    //! This constructor creates a field with user-provided function object.
    //! To compute derivatives, such as gradient and Laplacian, finite
    //! differencing is used. Thus, the differencing resolution also can be
    //! provided as the last parameter.
    //!
    CustomVectorField2(
        const std::function<Vector2D(const Vector2D&)>& customFunction,
        double derivativeResolution = 1e-3);

    //!
    //! \brief Constructs a field with given field and gradient function.
    //!
    //! This constructor creates a field with user-provided field and gradient
    //! function objects. To compute Laplacian, finite differencing is used.
    //! Thus, the differencing resolution also can be provided as the last
    //! parameter.
    //!
    CustomVectorField2(
        const std::function<Vector2D(const Vector2D&)>& customFunction,
        const std::function<double(const Vector2D&)>& customDivergenceFunction,
        double derivativeResolution = 1e-3);

    //! Constructs a field with given field, gradient, and Laplacian function.
    CustomVectorField2(
        const std::function<Vector2D(const Vector2D&)>& customFunction,
        const std::function<double(const Vector2D&)>& customDivergenceFunction,
        const std::function<double(const Vector2D&)>& customCurlFunction);

    //! Returns the sampled value at given position \p x.
    Vector2D sample(const Vector2D& x) const override;

    //! Returns the divergence at given position \p x.
    double divergence(const Vector2D& x) const override;

    //! Returns the curl at given position \p x.
    double curl(const Vector2D& x) const override;

    //! Returns the sampler function.
    std::function<Vector2D(const Vector2D&)> sampler() const override;

 private:
    std::function<Vector2D(const Vector2D&)> _customFunction;
    std::function<double(const Vector2D&)> _customDivergenceFunction;
    std::function<double(const Vector2D&)> _customCurlFunction;
    double _resolution = 1e-3;
};

}  // namespace jet

#endif  // INCLUDE_JET_CUSTOM_VECTOR_FIELD2_H_
