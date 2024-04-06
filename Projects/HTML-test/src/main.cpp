/* Code written by Jared Andraszek */

#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include "html-parser.hpp"

/**
 * @brief Used to trim whitespace around a string.
 *
 * @param str string to trim
 * @return std::string new string with whitespace trimmed.
 */
std::string trim(const std::string &str);

void testing();

int main(int argc, char *argv[])
{
    // Get the program name;
    // testing();

    const std::string PROGRAM_NAME = trim(argv[0]);
    HTMLParser htmlParser;

    // First we parse each page
    for (int i = 1; i < argc; i++)
    {
        // get each argument to the program.
        const std::string HTML_PAGE = argv[i];

        // If the argument is not the program
        if (HTML_PAGE.find(PROGRAM_NAME) == std::string::npos)
        {
            // then ask to parse the HTML page.
            std::cout << "Parsing: '" << HTML_PAGE << "'\n";
            htmlParser.parse(HTML_PAGE);
        }
    }

    // Second we print the results
    std::cout << std::setw(24) << "Page"
              << std::setw(10) << "Balanced"
              << std::setw(13) << "Visit Count" << '\n';
    for (int i = 1; i < argc; i++)
    {
        // get each argument to the program.
        const std::string HTML_PAGE = argv[i];

        // If the argument is not the program
        if (HTML_PAGE.find(PROGRAM_NAME) == std::string::npos)
        {
            /* then print out if it is balanced and number of web pages
             * that can be visited from the page
             */
            const std::string BAL = htmlParser.isBalanced(HTML_PAGE) ? "yes" : "no";
            const int VISIT_COUNT = htmlParser.pageVisitAmount(HTML_PAGE);
            std::cout << std::setw(24) << HTML_PAGE
                      << std::setw(10) << BAL
                      << std::setw(13) << VISIT_COUNT << '\n';
        }
    }
}

std::string trim(const std::string &str)
{
    std::string::size_type start;
    std::string::size_type end;

    // iterate to the first non-space character
    for (start = 0; start < str.length() && isspace(str[start]); ++start)
    {
    }

    // iterate to the last non-space character
    for (end = str.length() - 1;
         end != std::string::npos && isspace(str[end]); --end)
    {
    }

    return str.substr(start, end - start);
}

void testing()
{
    HTMLParser htmlparser;
    const std::string CSU = "pages/csu.html";
    const std::string UNBAL = "pages/unbalanced1.html";
    htmlparser.parse(CSU);
    htmlparser.parse(UNBAL);

    htmlparser.print();

    if (htmlparser.isBalanced(CSU))
    {
        std::cout << "CSU is balanced\n";
    }
    else
    {
        std::cout << "CSU is not balanced (ERROR)\n";
    }

    if (htmlparser.isBalanced(UNBAL))
    {
        std::cout << "\nUnbalanced 1 is balanced (ERROR)\n";
    }
    else
    {
        std::cout << "\nUnbalanced 1 is unbalanced\n";
    }

    int CSUvisit = htmlparser.pageVisitAmount(CSU);
    std::cout << "\ncsu.html had " << CSUvisit << " links\n";

    int UNBALvisit = htmlparser.pageVisitAmount(UNBAL);
    std::cout << "\nunbalanced1.html had " << UNBALvisit << " links\n";

    htmlparser.print();
}