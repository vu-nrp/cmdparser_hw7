#pragma once

#include <ctime>
#include "publisher.h"

//!
//! \brief The CommandParser class - класс для анализа ввода и извещения подписчиков
//!
class CommandParser : public Publisher
{
public:
    static const std::string DynBlockBeg;
    static const std::string DynBlockEnd;

    CommandParser(const size_t &n);

    void pushLine(const std::string &line);
    void handleData();
    void notifyAndClear();
    const std::time_t &packStartTime() const;

private:
    size_t m_packLen {0};
    CommandsPack m_commands;
    std::time_t m_packStartTime {0};
    size_t m_isDynActivated {0};

};
