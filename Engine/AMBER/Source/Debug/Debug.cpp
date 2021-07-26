#include "Debug.hpp"

namespace Ge
{
        bool Debug::initialize()
        {
                Debug::INITSUCCESS("Debug");
                return true;
        }

        void Debug::release()
        {

        }

        void Debug::Log(const char *format, ...)
        {
                char buffer[1000];
                char buffer2[1000];

                va_list argList;
                va_start(argList, format);
#ifdef _WIN32
                vsprintf(buffer, format, argList);
                sprintf_s(buffer2, "[ENGINE][USER] : %s\n", buffer);
#elif __unix__
                vsprintf(buffer, format, argList);
                sprintf(buffer2, "[ENGINE][USER] : %s\n", buffer);
#endif
                va_end(argList);

                std::cout << buffer2;
        }

        void Debug::Error(const char *format, ...)
        {
                char buffer[1000];
                char buffer2[1000];

                va_list argList;
                va_start(argList, format);
#ifdef _WIN32
                vsprintf(buffer, format, argList);
                sprintf_s(buffer2, "[ENGINE][ERROR] : %s\n", buffer);
#elif __unix__
                vsprintf(buffer, format, argList);
                sprintf(buffer2, "[ENGINE][ERROR] : %s\n", buffer);
#endif
                va_end(argList);

                std::cerr << termcolor::red << buffer2 << termcolor::reset;
                std::cin.ignore();
        }

        void Debug::INITSUCCESS(const char *format)
        {
                Debug::Info("Initialisation : %s", format);
        }

        void Debug::RELEASESUCCESS(const char *format)
        {
                Debug::Info("Liberation : %s", format);
        }

        void Debug::INITFAILED(const char *format)
        {
                Debug::Error("Erreur lors de l'initialisation : %s", format);
        }

        void Debug::Warn(const char *format, ...)
        {
                char buffer[1000];
                char buffer2[1000];

                va_list argList;
                va_start(argList, format);
#ifdef _WIN32
                vsprintf(buffer, format, argList);
                sprintf_s(buffer2, "[ENGINE][WARN] : %s\n", buffer);
#elif __unix__
                vsprintf(buffer, format, argList);
                sprintf(buffer2, "[ENGINE][WARN] : %s\n", buffer);
#endif
                va_end(argList);

                std::cout << termcolor::yellow << buffer2 << termcolor::reset;
        }

        void Debug::Info(const char *format, ...)
        {
                char buffer[1000];
                char buffer2[1000];

                va_list argList;
                va_start(argList, format);
#ifdef _WIN32
                vsprintf(buffer, format, argList);
                sprintf_s(buffer2, "[ENGINE][INFO] : %s\n", buffer);
#elif __unix__
                vsprintf(buffer, format, argList);
                sprintf(buffer2, "[ENGINE][INFO] : %s\n", buffer);
#endif
                va_end(argList);

                std::cout << termcolor::cyan << buffer2 << termcolor::reset;
        }

        void Debug::VLayer(const char *format, ...)
        {
                char buffer[1000];
                char buffer2[1000];

                va_list argList;
                va_start(argList, format);
#ifdef _WIN32
                vsprintf(buffer, format, argList);
                sprintf_s(buffer2, "[ENGINE][VLAYER] : %s\n", buffer);
#elif __unix__
                vsprintf(buffer, format, argList);
                sprintf(buffer2, "[ENGINE][VLAYER] : %s\n", buffer);
#endif
                va_end(argList);

                std::cout << termcolor::magenta << buffer2 << termcolor::reset;
        }

        void Debug::log(const char *format, ...)
        {
                char buffer[1000];
                char buffer2[1000];

                va_list argList;
                va_start(argList, format);
#ifdef _WIN32
                vsprintf(buffer, format, argList);
                sprintf_s(buffer2, "[ENGINE][USER] : %s\n", buffer);
#elif __unix__
                vsprintf(buffer, format, argList);
                sprintf(buffer2, "[ENGINE][USER] : %s\n", buffer);
#endif
                va_end(argList);

                std::cout << buffer2;
        }

        void Debug::error(const char *format, ...)
        {
                char buffer[1000];
                char buffer2[1000];

                va_list argList;
                va_start(argList, format);
#ifdef _WIN32
                vsprintf(buffer, format, argList);
                sprintf_s(buffer2, "[ENGINE][ERROR] : %s\n", buffer);
#elif __unix__
                vsprintf(buffer, format, argList);
                sprintf(buffer2, "[ENGINE][ERROR] : %s\n", buffer);
#endif
                va_end(argList);

                std::cerr << termcolor::red << buffer2 << termcolor::reset;
                std::cin.ignore();
        }

        void Debug::warn(const char *format, ...)
        {
                char buffer[1000];
                char buffer2[1000];

                va_list argList;
                va_start(argList, format);
#ifdef _WIN32
                vsprintf(buffer, format, argList);
                sprintf_s(buffer2, "[ENGINE][WARN] : %s\n", buffer);
#elif __unix__
                vsprintf(buffer, format, argList);
                sprintf(buffer2, "[ENGINE][WARN] : %s\n", buffer);
#endif
                va_end(argList);

                std::cout << termcolor::yellow << buffer2 << termcolor::reset;
        }

        void Debug::info(const char *format, ...)
        {
                char buffer[1000];
                char buffer2[1000];

                va_list argList;
                va_start(argList, format);
#ifdef _WIN32
                vsprintf(buffer, format, argList);
                sprintf_s(buffer2, "[ENGINE][INFO] : %s\n", buffer);
#elif __unix__
                vsprintf(buffer, format, argList);
                sprintf(buffer2, "[ENGINE][INFO] : %s\n", buffer);
#endif
                va_end(argList);

                std::cout << termcolor::cyan << buffer2 << termcolor::reset;
        }

}