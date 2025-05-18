#include <ctime>
#include <iostream>
#include "utils.h"

//!
//! \brief main - main app function
//! \return
//!

int main(int argc, char **argv)
{
    static const std::string DynBlockBeg("{");
    static const std::string DynBlockEnd("}");

    std::cout << "Home Work #7" << std::endl;

    if (argc != 2) {
        std::cout << "one param required, it is a count of commands in block" << std::endl;
        return 1;
    }

    const std::string param(argv[1]);

    try {
        size_t isDynActivated = 0;
        const size_t N = std::stol(param);

        if (N == 0) {
            std::cout << "invalid block size, block size must be more then 0" << std::endl;
            return 2;
        }

        std::time_t startTime;

        CommandsPack commands;
        commands.reserve(N);

        for (std::string line; std::getline(std::cin, line);) {
            if (line == DynBlockBeg) {
                // вложенный динамический блок { (начало) - пропускаем '{' и продолжаем накапливать команды
                if (isDynActivated != 0) {
                    isDynActivated++;
                    continue;
                }

                // старт динамического блока, печатаем уже накопленное и начинаем накапливать с начала
                isDynActivated++;
                printAndClearCommands(startTime, commands);
            } else if (line == DynBlockEnd) {
                if (isDynActivated != 0) {
                    isDynActivated--;

                    if (isDynActivated != 0) {
                        // вложенный динамический блок } (конец) - пропускаем '}' и продолжаем накапливать команды
                        continue;
                    }

                    // печатаем уже накопленное и начинаем накапливать с начала
                    printAndClearCommands(startTime, commands);
                } else {
                    std::cout << "unexpected dynamic block ending '}' - skip" << std::endl;
                    continue;
                }
            } else {
                if (commands.empty()) {
                    // time of first command in block
                    startTime = std::time(nullptr);
                }

                commands.push_back(line);
                if (commands.size() == N) {
                    // накопили N команд, печатаем и начинаем накапливать с начала
                    printAndClearCommands(startTime, commands);
                }
            }
        }

        // конец ввода команд
        if (isDynActivated != 0) {
            // динамический блок так и не закончился - пропускаем
        } else {
            printAndClearCommands(startTime, commands);
        }
    } catch (std::invalid_argument const& ex) {
        std::cout << "invalid parameter: " << param << std::endl;
        return 3;
    } catch (std::out_of_range const& ex) {
        std::cout << "invalid parameter: " << param << std::endl;
        return 4;
    }

    return 0;
}
