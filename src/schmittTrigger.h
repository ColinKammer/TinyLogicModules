#pragma once

namespace cjk {

template <typename SignalT>
class SchmittTrigger {
    SignalT m_lowerThresh;
    SignalT m_upperThresh;
    bool m_state;

public:
    constexpr SchmittTrigger(
        const SignalT& lowerThresh,
        const SignalT& upperThresh,
        bool initialState = false)
        : m_lowerThresh(lowerThresh)
        , m_upperThresh(upperThresh)
        , m_state(initialState)
    {
    }

    constexpr bool Update(const SignalT& sig)
    {
        if (m_upperThresh < sig)
            m_state = true;
        else if (sig < m_lowerThresh)
            m_state = false;
        else {
            /* Hysteresis section => state stays*/
        }
        return m_state;
    }

    [[nodiscard]] constexpr bool GetState() const noexcept { return m_state; }
};

}