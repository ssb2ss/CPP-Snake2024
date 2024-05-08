#ifndef INPUT_MANAGER
#define INPUT_MANAGER

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