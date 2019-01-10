#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>

std::string getExtension(std::string file)
{

    std::string extension;

    bool stopFound;

    for (char symbol : file)
    {

        if (symbol == '.')
        {

            stopFound = true;

            extension += symbol;

        }
        else if (stopFound)
        {

            extension += symbol;

        }
        else
        {

            continue;

        }

    }

    return extension;

}

std::string trimExtension(std::string file)
{

    std::string sansExt;
    bool stopFound;

    for (const char symbol : file)
    {

        if (symbol != '.')
        {

            sansExt += symbol;

        }
        else
        {

            break;

        }

    }

    return sansExt;

}

bool stringContainsChar(std::string text, char symbol)
{

    for (const char character : text)
    {

        if (character == symbol)
        {

            return true;

        }
        else 
        {

            continue;

        }

    }

    return false;

}

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

    return finalString;

}

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

struct variableValue
{

    std::string varName;
    std::string varVal;

};

struct bracePair
{

    bool firstFound;
    bool secondFound;

};

bool firstNonEmptyChar(std::string line, const char delimiter)
{

    line = removeChar(line, ' ');

    for (const char character : line)
    {

        if (character == delimiter)
        {

            return true;

        }
        else 
        {

            break;

        }

    }

    return false;
}

bool bracePairBegins(std::string line)
{

    if (stringContainsChar(line, '{'))
    {

        return true;

    }

    return false;

}

class classParser
{

private:

    std::string curAccessModifier = "private";
    variableValue curVar;
    std::ifstream file;
    std::string fileName;
    std::string className;

    bool classDefined{false};
    bool classWithoutBrackets{false};

    std::stack<bracePair> braceStack;

public:

    classParser(std::string classFile)
    {

        file = std::ifstream(classFile);

        if (!file)
        {

            std::cerr << classFile << " could not be opened\n";
            exit(1);

        }

        fileName = classFile;
        className = trimExtension(classFile);

    }

    ~classParser()
    {

        file.close();

    }

    void memberVariableDeclared(std::string line)
    { 

    }

    bool classDefinitionBegin(std::string curLine)
    {

        if (containsKeyWord(curLine, "class") && !stringContainsChar(curLine, ';'))
        {

            if (bracePairBegins(curLine))
            {

                braceStack.push(bracePair{true});
                std::cout << "definition beginning\n";
                classDefined = true;
                return true;

            }
            else
            {

                classWithoutBrackets = true;
                return true;

            }

        }

        if (classWithoutBrackets && firstNonEmptyChar(curLine, '{'))
        {

            classDefined = true;
            classWithoutBrackets = false;
            braceStack.push(bracePair{true});
            std::cout << "definition beginning\n";
            return true;

        }

        return false;

    }

    bool isEmpty(std::string line)
    {

        for (const auto character : line)
        {

            if (character == ' ')
            {

                continue;

            }
            else 
            {

                return false;

            }

        }

        return true;

    }

    void checkLine(std::string line)
    {

        if (isEmpty(line))
        {

            return;

        }

        classDefinitionBegin(line);

        if (firstNonEmptyChar(line, '{'))
        {

            braceStack.push(bracePair{true});

        }


    }

    bool containsKeyWord(std::string line, std::string keyword)
    {

        std::vector<std::string> splitString = split(line, ' ');

        if (splitString[0] == keyword)
            return true;

        return false;

    }

    void parse()
    {

        std::string curLine;

        while (std::getline(file, curLine))
        {
            
            checkLine(curLine);

        }

    }

    void printClassExtent() {std::cout << getExtension(fileName) << std::endl;}

    void printClassName() {std::cout << className << std::endl;}

};

int main(int argc, char const *argv[])
{
    
    classParser parser(argv[1]);

    parser.parse();

    return 0;
}
