#pragma once

namespace cjk
{

    class EdgeDetector
    {
        bool m_state;
        bool m_initialized;

    public:
        template <typename RisingFuncT, typename FallingFuncT>
        void OnEdge(bool signal, const RisingFuncT &risingFunc, const FallingFuncT &fallingFunc)
        {
            if (!m_initialized)
            {
                m_initialized = true;
                m_state = signal;
                return;
            }

            const bool lastState = m_state;
            m_state = signal;
            if (lastState && !signal)
                fallingFunc();
            if (!lastState && signal)
                risingFunc();
        }

        template <typename FuncT>
        void OnRisingEdge(bool signal, const FuncT &func)
        {
            OnEdge(
                signal, func, []() {});
        }

        template <typename FuncT>
        void OnFallingEdge(bool signal, const FuncT &func)
        {
            OnEdge(
                signal, []() {}, func);
        }
    };

}