#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

//InputManager::GetInstance().GetPressedKey();
class InputManager
{
    InputManager(){}
    ~InputManager(){}
public:
    static int pressedKey;
    static InputManager& GetInstance();
    static int GetPressedKey();
};

#endif