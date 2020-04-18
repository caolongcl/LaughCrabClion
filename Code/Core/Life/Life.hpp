#pragma once

#include "TypeDef.hpp"

namespace LaughCrab
{
    // main loop

    class Life final
    {
    public:
        Life();

        ~Life();

        //
        void Go();

        // register


        // unregister

    private:
        typedef enum
        {
            eNormalState = 0,
            eReBornState,
            eKillState,
        } LifeState;

        // do some system's init stuff , like service init etc...
        void PreBorn();

        // do some system's de init stuff ,like service deInit etc...
        void Bury();

        // somebody or some error kill you!
        Boolean Kill();

        // somebody give you a chance, life restart
        Boolean Reborn();

        Boolean Start();

        Boolean Cycle();

        Boolean End();

        const LifeState GetState() const ;

        LifeState m_lifeState;
    };
}
