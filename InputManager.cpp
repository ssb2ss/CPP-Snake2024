#include "InputManager.h"

int InputManager::pressedKey = 0;

InputManager& InputManager::GetInstance()
{
    static InputManager instance;
    return instance;
}

int InputManager::GetPressedKey()
{
    return InputManager::GetInstance().pressedKey;
}