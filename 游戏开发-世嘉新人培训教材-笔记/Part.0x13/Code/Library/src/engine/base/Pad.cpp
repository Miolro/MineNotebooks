#include "engine/base/Pad.h"
using namespace GameLib;
namespace engine
{
    namespace base
    {
        char typeToChar(Pad::KEY keyType)
        {
            char key = 0;
            switch (keyType)
            {
            case Pad::KEY_FORWARD:
                key = 'w';
                break;
            case Pad::KEY_COMEBACK:
                key = 's';
                break;
            case Pad::KEY_LEFT:
                key = 'a';
                break;
            case Pad::KEY_RIGHT:
                key = 'd';
                break;
            case Pad::KEY_UP:
                key = ' ';
                break;
            case Pad::KEY_DOWN:
                key = 'c';
                break;
            case Pad::KEY_TURNRIGHT:
                key = 'q';
                break;
            case Pad::KEY_TURNLEFT:
                key = 'e';
                break;
            case Pad::KEY_AIM:
                key = 'r';
                break;
            case Pad::KEY_FIRE:
                key = 'f';
                break;
            }
            return key;
        }

        Pad::Pad()
        {
            mManager = Input::Manager::instance();
            mKeyboard = mManager.keyboard();
            mMouse = mManager.mouse();
        }

        bool Pad::keyno(KEY keyType)
        {
            char key = typeToChar(keyType);
            if (key)
            {
                return mKeyboard.isOn(key);
            }
            else {
                return false;
            }
        }

        bool Pad::triggered(KEY keyType)
        {
            char key = typeToChar(keyType);
            if (key)
            {
                return mKeyboard.isTriggered(key);
            }
            else {
                return false;
            }
        }

    }
}
