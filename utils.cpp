#include <fstream>
#include <iostream>
#include "utils.h"

//!
//! \brief printAndClearCommands - print command bloc content and clear block
//! \param startTime - incoming time of first command in seconds from epoch
//! \param pack - block of command, will be cleared after printing
//!

void printAndClearCommands(const size_t &startTime, CommandsPack &pack)
{
    if (pack.size() > 0) {
        auto packToString = [pack](const std::string &delim) -> std::string
        {
            auto it = pack.cbegin();
            auto result = *it;
            for (++it;it != pack.cend();++it)
                result += (delim + *it);
            return result;
        };

        // печать в консоль
        std::cout << "bulk: " << packToString(", ") << std::endl;

        // печать в файл
        static const auto fmt = "./bulk%.10zu.log";
        static const int sz = std::snprintf(nullptr, 0, fmt, startTime);
        std::string fileName(sz, '\0');
        std::sprintf(fileName.data(), fmt, startTime);

        std::ofstream file;
        file.open(fileName);
        const auto data = packToString("\n");
        file.write(data.c_str(), data.length());
        file.close();

        // очистка буфера
        pack.clear();
    }
}
