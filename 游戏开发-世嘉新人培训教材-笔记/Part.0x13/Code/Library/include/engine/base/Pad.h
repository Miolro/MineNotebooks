#pragma once
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "GameLib/Input/Mouse.h"
namespace engine
{
    namespace base
    {
        class Pad
        {

        public:
            enum KEY
            {
                KEY_FORWARD = 1,
                KEY_COMEBACK,
                KEY_LEFT,
                KEY_RIGHT,
                KEY_UP,
                KEY_DOWN,
                KEY_TURNRIGHT,
                KEY_TURNLEFT,
                KEY_AIM,
                KEY_FIRE,
            };
            Pad();
            bool keyno(KEY keyType);
            bool triggered(KEY keyType);
        private:
            GameLib::Input::Manager mManager;
            GameLib::Input::Keyboard mKeyboard;
            GameLib::Input::Mouse mMouse;
        };
    }
}

