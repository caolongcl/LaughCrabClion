#pragma once

#include "Runtime.hpp"
#include "UnCopyable.hpp"
#include "URef.hpp"
#include "Life/Life.hpp"

namespace LaughCrab {
    // game must inherit this

    class Application : public UnCopyable {
    public:
        Application();

        Application(void *);

        ~Application();

        Integer Run(Char **cmd);

    private:
        Life m_life;
    };

}
