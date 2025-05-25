#include "observer.h"

//!
//! \brief Observer::packToString - упаковка в строку для печати
//! \param pack - блок команд
//! \param delim - разделитель
//! \return - строковое представление блока команд
//!
std::string Observer::packToString(const CommandsPack &pack, const std::string &delim) const
{
    auto it = pack.cbegin();
    auto result = *it;
    for (++it;it != pack.cend();++it)
        result += (delim + *it);
    return result;
}

