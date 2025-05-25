#include <fstream>
#include <iostream>
#include "observer.h"
#include "publisher.h"
#include "commandparser.h"

//!
//! \brief The FileObserver class - класс подписчик сохраняющий данные в файл
//!
class FileObserver : public Observer
{
public:
    FileObserver(const std::shared_ptr<CommandParser> &pub) :
        Observer(),
        m_pub(pub)
    {
    }

    void update(const CommandsPack &pack) const override
    {
        const auto pub = m_pub.lock();
        if (pub) {
            const auto &startTime = pub->packStartTime();
            // печать в файл
            static const auto fmt = "./bulk%.10zu.log";
            static const int sz = std::snprintf(nullptr, 0, fmt, startTime);
            std::string fileName(sz, '\0');
            std::sprintf(fileName.data(), fmt, startTime);

            std::ofstream file;
            file.open(fileName);
            const auto data = packToString(pack, "\n");
            file.write(data.c_str(), data.length());
            file.close();
        }
    }

private:
    std::weak_ptr<CommandParser> m_pub;

};

//!
//! \brief The ConsoleObserver class - класс подписчик выводящий данные в консоль
//!
class ConsoleObserver : public Observer
{
public:
    void update(const CommandsPack &pack) const override
    {
        // печать в консоль
        std::cout << "bulk: " << packToString(pack, ", ") << std::endl;
    }

};

//!
//! \brief main - функция точка входа в программу
//! \return
//!
int main(int argc, char **argv)
{
    std::cout << "Home Work #7" << std::endl;

    if (argc != 2) {
        std::cout << "one param required, it is a count of commands in block" << std::endl;
        return 1;
    }

    const std::string param(argv[1]);

    try {
        const size_t N = std::stol(param);

        if (N == 0) {
            std::cout << "invalid block size, block size must be more then 0" << std::endl;
            return 2;
        }

        // publisher <-> observer pattern
        std::shared_ptr<CommandParser> bulk(new CommandParser(N));
        std::shared_ptr<FileObserver> fileObserver(new FileObserver(bulk));
        std::shared_ptr<ConsoleObserver> consoleObserver(new ConsoleObserver());

        // subscribe
        bulk->subscribe(fileObserver);
        bulk->subscribe(consoleObserver);

        for (std::string line; std::getline(std::cin, line);) {
            bulk->pushLine(line);

//            // testing
//            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // конец ввода команд и это не динамический блок
        bulk->handleData();
    } catch (std::invalid_argument const& ex) {
        std::cout << "invalid parameter: " << param << std::endl;
        return 3;
    } catch (std::out_of_range const& ex) {
        std::cout << "invalid parameter: " << param << std::endl;
        return 4;
    }

    return 0;
}
