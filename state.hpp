#include <string>
#include <vector>

class State{
    private:
        bool state = false;
    public:
        State(bool state) : state(state) {};
        void reverseState(){state = !state;}
        bool getState() const{ return state;}
};

std::ostream &operator<<(std::ostream &os, State const &m)
{
    return os << m.getState(); 
}