#pragma once

namespace cjk {

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
    constexpr LERP(
        const InT& x1, const OutT& y1,
        const InT& x2, const OutT& y2)
        : m_d(x2 * y1 / y2)
        , m_m(y2 / x2)
    {
    }

    [[nodiscard]] Promoted constexpr operator()(const InT& x) const
    {
        return (m_d + x) * m_m;
    }
};

}
