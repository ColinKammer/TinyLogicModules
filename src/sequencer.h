#pragma once

namespace cjk {

template <typename SequenceContainerT>
class Sequencer {
    SequenceContainerT m_sequence;
    size_t m_currentIndex;

public:
    Sequencer(SequenceContainerT&& seq)
        : m_sequence(std::move(seq))
        , m_currentIndex(0)
    {
    }

    template <typename... Ts>
    Sequencer(Ts... ts)
        : m_sequence { ts... }
        , m_currentIndex(0)
    {
    }

    auto Next()
    {
        m_currentIndex++;
        if (m_currentIndex >= m_sequence.size())
            m_currentIndex = 0;
        return GetCurrentSequenceElement();
    }

    [[nodiscard]] auto GetCurrentSequenceElement() const
    {
        return m_sequence[m_currentIndex];
    }
};

}