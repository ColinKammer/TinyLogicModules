#pragma once
#include <bitset>

namespace cjk
{

    template <size_t NumConsideredSamples = 8, size_t Hysteresis = NumConsideredSamples / 3>
    class Debouncer
    {
        std::bitset<NumConsideredSamples> m_buffer;
        bool m_initialized = false;
        bool m_state;

        void handleFirstSample(bool firstSample) noexcept
        {
            if (firstSample)
                m_buffer.set();
            else
                m_buffer.reset();
            m_initialized = true;
        }

    public:
        bool Process(bool newSample) noexcept
        {
            if (!m_initialized)
                handleFirstSample(newSample);

            m_buffer <<= 1;
            m_buffer[0] = newSample;

            if (m_buffer.count() <= NumConsideredSamples / 2 - Hysteresis / 2)
                m_state = false;
            if (m_buffer.count() > NumConsideredSamples / 2 + Hysteresis / 2)
                m_state = true;
            return m_state;
        }
    };

}
