/* Code written by Jared Andraszek */

#include "html-parser.hpp"

#include <fstream> // To read HTML files.
#include <iostream>

HTMLParser::page::page(const std::string &fileName)
    : pageName(fileName)
{
}

HTMLParser::HTMLParser()
{
    pages = new std::vector<HTMLParser::page>();
}

HTMLParser::~HTMLParser()
{
    delete pages;
}

bool HTMLParser::parse(const std::string &filename)
{
    bool retVal = false;

    if (pageInStack(filename))
    { // If the page is already in the vector //
        retVal = true;
    }
    else
    {
        // Makes the new page & file stream //
        std::ifstream stream(filename);

        if (stream.fail())
        {                  // If the file DNE //
            return retVal; // Exit the function //
        }

        page pageToParse(filename);
        std::string check = "";
        char character;

        while (!stream.eof())
        {
            stream.get(character);

            if (stream.eof())
            {
                // Skips the other if statements //
                // Especially the '>' statement  //
            }
            else if (character == '<')
            {
                check.append("<");
            }
            else if (character == '>')
            {
                check.append(">");
                pageToParse.pageStack.push(check);
                check = "";
            }
            else if (check.compare("") > 0 && check.at(0) == '<')
            {
                check.push_back(character);
            }
        }
        pages->push_back(pageToParse);
        retVal = true;
    }
    return retVal;
}

bool HTMLParser::pageInStack(const std::string &filename)
{
    std::vector<HTMLParser::page>::iterator iter;

    if (pages->size() == 0)
        return false;
    else
    {
        for (iter = pages->begin(); iter != pages->end(); iter++)
        {
            // if the page at index's pagename is the same as the filename we   //
            // are looking for, return true as the pagename is in pages         //
            if (iter->pageName.compare(filename) == 0)
                return true;
        }
    }

    return false;
}

void HTMLParser::print()
{
    std::vector<HTMLParser::page>::reverse_iterator riter;
    std::stack<std::string> copyStack;

    std::cout << "There are " << pages->size() << " pages.\n";

    for (riter = pages->rbegin(); riter != pages->rend(); riter++)
    {
        copyStack = riter->pageStack;
        std::cout << "\nThe stack for " << riter->pageName << ":\n";

        while (!copyStack.empty())
        {
            std::cout << copyStack.top() << "\n";
            copyStack.pop();
        }
    }
}

bool HTMLParser::isBalanced(const std::string &filename)
{
    if (!pageInStack(filename))
    { // Check if filename is in Stack //
        parse(filename);
    }

    std::stack<std::string> strStack = std::stack<std::string>();
    std::stack<std::string> pageStack = findPageByName(filename);

    while (!pageStack.empty())
    {
        if (strStack.empty())
        {
            strStack.push(pageStack.top());
            pageStack.pop();
        }
        else
        {
            if (sameTag(pageStack.top(), strStack.top()))
            {
                pageStack.pop();
                strStack.pop();
            }
            else
            {
                strStack.push(pageStack.top());
                pageStack.pop();
            }
        }
    }

    return strStack.empty();
}

bool HTMLParser::sameTag(const std::string &pageStackTag, const std::string &strStackTag)
{
    bool retVal = false;

    std::string strSubstring = strStackTag.substr(2, strStackTag.size() - 3);
    std::string pageSubstring = pageStackTag.substr(1, pageStackTag.size() - 2);

    if (strSubstring.compare("a") == 0)
    {                                   // If it is comparing a reference link //
        if (pageSubstring.at(0) == 'a') // Allows for the reference link //
            return true;
    }
    else
    {
        if (strSubstring.compare(pageSubstring) == 0)
        {
            return true;
        }
    }

    return retVal;
}

std::stack<std::string> HTMLParser::findPageByName(const std::string &str)
{
    std::vector<HTMLParser::page>::iterator iter;

    for (iter = pages->begin(); iter != pages->end(); iter++)
    {
        if (iter->pageName.compare(str) == 0)
        {
            return iter->pageStack;
        }
    }

    return std::stack<std::string>();
}

int HTMLParser::pageVisitAmount(const std::string &filename)
{
    int pagesVisited = 0;
    if (!pageInStack(filename))
    { // Check if filename is in Stack //
        if (!parse(filename))
        {
            return 0;
        }
    }

    std::vector<std::string> strPagesVisited;
    std::stack<std::string> pageStack = findPageByName(filename);
    std::string tempString;
    std::string newFileName;

    while (!pageStack.empty())
    {
        tempString = pageStack.top();
        std::string tagSubstring = tempString.substr(1, tempString.length() - 2);

        if (tagSubstring.at(0) == 'a')
        {
            // sets the newFileName to a substring of the substring //
            newFileName = tagSubstring.substr(8, tagSubstring.length() - 9);

            // Check if the file name was already checked //
            if (!stringInVector(newFileName, strPagesVisited) && doesPageExist(newFileName))
            {
                strPagesVisited.push_back(newFileName);

                // Recursive call to check the pageVisits the new filename has //
                if (filename.compare(newFileName) != 0)
                {
                    pagesVisited += pageVisitAmount(newFileName);

                    // If the newFileName Exists, Add 1         //
                    // Was added to counter the files that DNE  //
                    if (pageInStack(newFileName) && doesPageExist(newFileName))
                    {
                        pagesVisited++;
                    }
                }
            }
        }

        pageStack.pop();
    }

    return pagesVisited;
}

bool HTMLParser::stringInVector(const std::string &str, std::vector<std::string> &vector)
{
    bool retVal = false;

    for (auto index : vector)
    {
        if (index.compare(str) == 0)
        {
            retVal = true;
        }
    }

    return retVal;
}

bool HTMLParser::doesPageExist(const std::string &filename)
{
    std::ifstream stream(filename);
    bool retVal = true;

    if (stream.fail())
        retVal = false;

    return retVal;
}