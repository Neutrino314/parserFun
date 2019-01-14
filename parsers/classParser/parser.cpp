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

    std::string access;
    std::string modifiers;
    std::string varName;
    std::string varVal;

};

struct bracePair
{

    bool firstFound;
    bool secondFound;

};

std::size_t countInstances(std::string line, const char delimiter)
{

    std::size_t instanceCount = 0;

    for (const auto character : line)
    {

        if (character == delimiter)
        {

            instanceCount++;

        }

    }

    return instanceCount;

}

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

    std::vector<std::string> modifiers = {"const", "long", "short", "unsigned", "signed"};

    std::vector<std::string> basicTypes = {"int", "float", "double", "bool"};

    std::stack<bracePair> braceStack;

    std::vector<std::vector<std::string>> combinedLines;

    std::vector<std::vector<std::string>> candidateVars;

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

    bool isModifier(std::string candidate)
    {

        for (auto modifier : modifiers)
        {

            if (candidate == modifier)
            {

                return true;

            }

        }

        return false;

    }

    bool isType(std::string candidate)
    {

        for (auto type : basicTypes)
        {

            if (candidate == type)
            {

                return true;

            }

        }

        return false;

    }

    bool containsKeyWord(std::string line, std::string keyWord)
    {

        std::vector<std::string> lineVect = sanitizeLine(line);

        for (auto symbol : lineVect)
        {

            if (symbol == keyWord || symbol == (keyWord += ";"))
            {

                return true;

            }

        }

        return false;

    }

    void checkStack()
    {

        if (braceStack.size() == 0)
        {
            return;
        }
        else
        {
            if (braceStack.top().secondFound == true && braceStack.size() > 1)
            {

                braceStack.pop();

            }
        }

    }

    void checkBraces(std::vector<std::string>& line)
    {

        for (auto string : line)
        {

            if (stringContainsChar(string, '{') && stringContainsChar(string, '}'))
            {

                continue;

            }
            else if (stringContainsChar(string, '{'))
            {

                braceStack.push(bracePair{true, false});

            }
            else if (stringContainsChar(string, '}') && braceStack.size() != 1)
            {

                braceStack.top().secondFound = true;

            }

            checkStack();

        }

    }

    std::vector<std::string> removeEmptyStrings(std::vector<std::string>& vect)
    {

        std::vector<std::string> newVect;

        for (const auto symbol : vect)
        {

            if (symbol != "")
            {

                newVect.emplace_back(symbol);

            }

        }

        return newVect;

    }

    std::vector<std::string> sanitizeLine(std::string line)
    {

        std::vector<std::string> splitLine = split(line, ' ');

        return removeEmptyStrings(splitLine);
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

    void removeString(std::vector<std::string>& stringVect, const std::string strRemove)
    {

        for (std::size_t i = 0; i < stringVect.size(); i++)
        {

            if (stringVect[i] == strRemove)
            {

                stringVect.erase(stringVect.begin() + i);
                return;

            }

        }

    }

    void printLine(std::vector<std::string>& stringVect)
    {

        for (const auto symbol : stringVect)
        {

            std::cout << symbol << ' ';

        }

        std::cout << std::endl;

    }

    bool checkField(std::vector<std::string>& stringVect)
    {

        if (stringVect[0] == "private:")
        {

            curAccessModifier = "private";
            return true;

        }
        else if (stringVect[0] == "public:")
        {

            curAccessModifier = "public";
            return true;

        }
        else if (stringVect[0] == "protected:")
        {

            curAccessModifier = "protected";
            return true;

        }

        return false;

    }

    bool isMethod(std::string line)
    {

        if (stringContainsChar(line, '(') && !stringContainsChar(line, '='))
        {

            return true;

        }

        return false;
    }

    void checkLine(std::string line)
    {

        std::vector<std::string> lineVect = sanitizeLine(line);

        if (lineVect.size() == 0)
        {

            return;

        }

        if (lineVect[0] == "#include")
        {

            return;

        }

        if (checkField(lineVect))
        {

            line = removeChar(line, ':');
            lineVect = sanitizeLine(line);
            removeString(lineVect, curAccessModifier);

        }

        checkBraces(lineVect);

        if (braceStack.size() > 1)
        {

            return;

        }

        if (lineVect[0] == "}")
        {

            return;

        }

        if (!stringContainsChar(line, ';'))
        {

            return;

        }

        if (isMethod(line))
        {

            return;

        }

        combinedLines.emplace_back(lineVect);

    }


    void parse()
    {

        std::string curLine;

        while (std::getline(file, curLine))
        {
            
            checkLine(curLine);

        }

        if (combinedLines.back()[0] == "};")
        {

            combinedLines.erase(combinedLines.end());

        }

        for (auto line : combinedLines)
        {

            printLine(line);

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
