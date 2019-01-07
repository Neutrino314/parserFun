#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <algorithm>

std::vector<std::string> split(std::string toSplit, const char delimiter)
{

    std::stringstream ss(toSplit);

    std::string token;

    std::vector<std::string> splitString;

    while (std::getline(ss, token, delimiter))
    {

        splitString.emplace_back(token);

    }

    return splitString;

}

std::vector<std::string> splitFirst(std::string Line, const char delimiter)
{

    bool found{false};

    std::vector<std::string> splitString;

    std::string key;

    std::string value;

    for (char symbol : Line)
    {

        if (symbol == delimiter && !found)
        {

            found = true;

        }
        else if (symbol != delimiter && !found)
        {

            key += symbol;

        } 
        else if (symbol != delimiter && found)
        {

            value += symbol;

        }

    }

    splitString.emplace_back(key);
    splitString.emplace_back(value);

    return splitString;

}

bool valIsInt(std::string value)
{

    return false;

}

bool valIsFloat(std::string value)
{



    return false;

}


template <typename K, typename V>
struct keyPair
{

    K key;
    V value;

};

struct List
{

    std::vector<std::string> elements;

};

template <typename K, typename V>
struct Dictionary
{

    std::vector<keyPair<K, V>> elements;

};

class duoParser
{

private:

    std::ifstream file;
    int curObjectID{0};
    std::string curObjectName;

    keyPair<std::string, std::string> curPair{"", " "};

public:

    duoParser(std::string path)
    {

        file = std::ifstream(path);

        if (!file)
        {

            std::cerr << path << " could not be opened\n";
            exit(1);

        }        

    }

    ~duoParser()
    {

        file.close();

    }

    bool isNewDoc(std::string line)
    {

        if (line == "---")
        {

            std::cout << "new document\n";
            curObjectID++;
            return true;

        }

        return false;

    }

    bool containsInfo(std::string line)
    {

        if (line != "")
            return true;

        return false;

    }

    void printPair(std::string line)
    {

        std::vector<std::string> tempVect = splitFirst(line, ':');

        curPair.key = tempVect[0];
        curPair.value = tempVect[1];

        std::cout << curPair.key << ", " << curPair.value << std::endl;

    }

    void parse()
    {

        std::string curLine;
        while (std::getline(file, curLine))
        {

            if (!containsInfo(curLine))
                continue;

            if (isNewDoc(curLine))
                continue;

            printPair(curLine);

        }

    }

};

int main(int argc, char const *argv[])
{

    duoParser parser("test.yaml");
    parser.parse();

    float test(0.0f);

    return 0;
}
