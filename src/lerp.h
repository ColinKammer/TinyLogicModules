#pragma once

#include <algorithm>
#include <array>
#include <stdexcept>

namespace cjk::lerp {

template <typename InT, typename OutT>
struct Point {
    InT x;
    OutT y;
};

template <typename InT, typename OutT = InT>
class LERP {
    using Promoted = decltype(InT {} + OutT {});
    Promoted m_m;
    Promoted m_b;

public:
    constexpr LERP()
        : m_m(1)
        , m_b(0)
    {
    }

    constexpr LERP(
        const Point<InT, OutT>& p1,
        const Point<InT, OutT>& p2)
        : m_m((p1.y - p2.y) / (p1.x - p2.x))
        , m_b(p1.y - p1.x * m_m)
    {
        if (p1.x == p2.x)
            throw std::invalid_argument("Conflicting Points");
    }

    [[nodiscard]] Promoted constexpr operator()(const InT& x) const
    {
        return m_m * x + m_b;
    }

    [[nodiscard]] LERP<OutT, InT> constexpr GetInverse() const
    {
        if (m_m == 0)
            throw std::runtime_error("No inverse Function possible - it would not be a function");
        LERP<OutT, InT> ret;
        ret.m_m = 1 / m_m;
        ret.m_b = (-1) * (m_b / m_m);
        return ret;
    }
};

template <typename InT, typename OutT = InT, unsigned NumPoints = 2>
class PicewiseLERP {
    using Promoted = decltype(InT {} + OutT {});
    using PointList = std::array<Point<InT, OutT>, NumPoints>;

    static_assert(NumPoints >= 2, "Can't inter-/extrapolate using less than 2 Points");

    PointList m_points;

public:
    constexpr PicewiseLERP()
    {
        m_points[0] = { 0, 0 };
        m_points[1] = { 1, 1 };
    }

    constexpr PicewiseLERP(const PointList& points_sorted)
        : m_points(points_sorted)
    {
        InT lastX = m_points[0].x;
        for (size_t i = 1; i < NumPoints; i++) {
            if (m_points[i].x < lastX)
                throw std::runtime_error("Points are not sorted");
            lastX = m_points[i].x;
        }
    }

    [[nodiscard]] Promoted constexpr operator()(const InT& x) const
    {
        if (x < m_points[0].x) {
            LERP<InT, OutT> lerp(m_points[0], m_points[1]);
            return lerp(x);
        }

        for (size_t i = 1; i < NumPoints; i++) {
            if (m_points[i - 1].x <= x && x <= m_points[i].x) {
                LERP<InT, OutT> lerp(m_points[i - 1], m_points[i]);
                return lerp(x);
            }
        }

        LERP<InT, OutT> lerp(m_points[NumPoints - 2], m_points[NumPoints - 1]);
        return lerp(x);
    }

    [[nodiscard]] PicewiseLERP<OutT, InT, NumPoints> constexpr GetInverse() const
    {
        {
            OutT lastY = m_points[0].y;
            for (size_t i = 1; i < NumPoints; i++) {
                if (m_points[i].y <= lastY)
                    throw std::runtime_error("No inverse Function possible - it would not be a function");
                lastY = m_points[i].y;
            }
        }

        PicewiseLERP<OutT, InT, NumPoints> ret;
        for (size_t i = 0; i < NumPoints; i++) {
            ret.m_points[i].x = m_points[i].y;
            ret.m_points[i].y = m_points[i].x;
        }
        return ret;
    }
};

}
