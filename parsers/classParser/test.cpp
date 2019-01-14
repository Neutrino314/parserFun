#include <string> 
class test 

{

private: 

    float rotation;

public:

    const int life{42};

    short int baz = 31;

    test()
    {



    }
    ~test()
    {


    }

    void stuff();

    void returnNothing() {return;}

    std::string removeChar(std::string line, char toRemove)
    {

    std::string finalString;

    for (const char character : line)
    {

        if (character == toRemove)
        {

            continue;

        }
        else
        {

            finalString += character;

        }

    }

    int i = 0;
    i++;

    return finalString;

    }

};