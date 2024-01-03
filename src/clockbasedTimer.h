#pragma once

namespace cjk
{
    template <typename TimepointT, typename DurationT, bool ProduceIntegralConsistency = false>
    class ClockbasedTimer
    {
        const DurationT m_period;
        TimepointT m_lastExpiration;
        bool m_initialized = false;

    public:
        ClockbasedTimer(const DurationT &period) noexcept
            : m_period(period)
        {
        }

        [[nodiscard]] bool CheckPeriodExpired(const TimepointT &now) noexcept
        {   
            if(!m_initialized){
                m_lastExpiration = now;
                m_initialized = true;
                return true;
            }

            if (now < m_lastExpiration + m_period)
                return false;
            if constexpr (ProduceIntegralConsistency)
                m_lastExpiration += m_period;
            else
                m_lastExpiration = now;
            return true;
        }
    };

}
