#include "publisher.h"
#include "observer.h"

void Publisher::subscribe(const std::shared_ptr<Observer> &obs)
{
    m_subs.emplace_back(obs);
}

void Publisher::notify(const CommandsPack &pack)
{
    for (const auto &item: m_subs) {
        const auto sub = item.lock();
        if (sub) {
            sub->update(pack);
        }
    }
}
