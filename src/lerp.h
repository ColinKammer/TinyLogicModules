#pragma once

#include <algorithm>
#include <array>

namespace cjk::lerp {

template <typename InT, typename OutT>
struct Point {
    InT x;
    OutT y;
};

template <typename InT, typename OutT = InT>
class LERP {
    using Promoted = decltype(InT {} + OutT {});
    Promoted m_d;
    Promoted m_m;

    // (x - x1) / x2 = (y - y1) / y2
    // y = (x - x1) * (y2/x2) + y1
    //   = (y1*x2/y2 - x1 + x) * (y2/x2)
    // y = (d + x) * m; d = x2*y1/y2; m = y2/x2
public:
    constexpr LERP()
        : m_d(0)
        , m_m(1)
    {
    }

    constexpr LERP(
        const InT& x1, const OutT& y1,
        const InT& x2, const OutT& y2)
        : m_d(x2 * y1 / y2)
        , m_m(y2 / x2)
    {
    }
    constexpr LERP(
        const Point<InT, OutT>& p1,
        const Point<InT, OutT>& p2)
        : m_d(p2.x * p1.y / p2.y)
        , m_m(p2.y / p2.x)
    {
    }

    [[nodiscard]] Promoted constexpr operator()(const InT& x) const
    {
        return (m_d + x) * m_m;
    }

    [[nodiscard]] LERP<OutT, InT> GetInverse() const
    {
        // y = (d + x) * m
        // x = y / m - d
        //   = (-d*m + y) * 1/m
        LERP<OutT, InT> ret;
        ret.m_d = -m_d * m_m;
        ret.m_m = 1 / m_m;
    }
};

template <typename InT, typename OutT = InT, unsigned NumPoints = 2>
class PicewiseLERP {
    using Promoted = decltype(InT {} + OutT {});
    using PointList = std::array<Point<InT, OutT>, NumPoints>;

    PointList m_points;

public:
    constexpr PicewiseLERP(const PointList& points_sorted)
        : m_points(points_sorted)
    {
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

    [[nodiscard]] PicewiseLERP<OutT, InT, NumPoints> GetInverse() const
    {
        PicewiseLERP<OutT, InT, NumPoints> ret;
        for (size_t i = 0; i < NumPoints; i++) {
            ret.m_points[i].x = m_points[i].y;
            ret.m_points[i].y = m_points[i].x;
        }
        // sort is required for non monotonic functions
        std::sort(ret.m_points.begin(), ret.m_points.end());
        return ret;
    }
};

}
