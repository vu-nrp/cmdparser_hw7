#pragma once

#include "types.h"

//!
//! \brief The Observer class - базовый класс для классов наблюдателей
//!
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update(const CommandsPack &pack) const = 0;

protected:
    std::string packToString(const CommandsPack &pack, const std::string &delim) const;

};

