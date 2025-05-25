#pragma once

#include <list>
#include <memory>
#include "types.h"

//!
//! predeclaration of observer class
//!
class Observer;

//!
//! \brief The Publisher class - базовый клас обработки данных и извешения подписчиков
//!
class Publisher
{
public:
    void subscribe(const std::shared_ptr<Observer> &obs);

protected:
    void notify(const CommandsPack &pack);

private:
    // список подписчиков
    std::list<std::weak_ptr<Observer>> m_subs;

};

