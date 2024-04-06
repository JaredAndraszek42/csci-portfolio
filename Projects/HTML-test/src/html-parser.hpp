/* Code written by Jared Andraszek */

#ifndef HTML_PARSER_HPP
#define HTML_PARSER_HPP

#include <string>
#include <stack>
#include <vector>

class HTMLParser
{
public:
    HTMLParser();

    ~HTMLParser();

    /**
     * Reads an HTML file and stores the tags in a container.
     * Returns false if the file could not be opened.
     */
    bool parse(const std::string &filename);

    /**
     * Returns true if the webpage exists and all the tags are balanced.
     */
    bool isBalanced(const std::string &filename);

    /**
     * Returns the number of unique pages that can be visited.
     * Links to pages that don't exist are not counted.
     */
    int pageVisitAmount(const std::string &filename);

    void print();

private:
    // Consists of a filename and the stack of tags //
    struct page
    {
        page(const std::string &fileName);
        std::string pageName;
        std::stack<std::string> pageStack;
    };

    // A vector that contains pages //
    std::vector<page> *pages;

    bool pageInStack(const std::string &filename);
    std::stack<std::string> findPageByName(const std::string &str);
    bool sameTag(const std::string &pageStackTag, const std::string &strStackTag);

    bool stringInVector(const std::string &str, std::vector<std::string> &vector);
    bool doesPageExist(const std::string &filename);
};

#endif
