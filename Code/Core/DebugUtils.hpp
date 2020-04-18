#pragma once

#include <string>
#include <cassert>

namespace LaughCrab {
#define Assert(Exp) assert((Exp))

    class Log {
    public:
        template<typename ...Args>
        static void Error(const std::string tag, const std::string &format, Args &&... args) {
            std::string info = "{Error::" + tag + "} " + format + "\n";
            Print(info, std::forward<Args>(args)...);
        }

        template<typename ...Args>
        static void Debug(const std::string tag, const std::string &format, Args &&... args) {
            std::string info = "{Debug::" + tag + "} " + format + "\n";
            Print(info, std::forward<Args>(args)...);
        }

    private:
        template<typename ...Args>
        static void Print(const std::string &format, Args &&... args) {
            fprintf(stdout, format.c_str(), std::forward<Args>(args)...);
        }
    };
}
