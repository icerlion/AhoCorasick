#include "AhoCorasick.hpp"

int main()
{
    CAhoCorasick hAhoCorasick(false);
    hAhoCorasick.AddWord("ABCD");
    hAhoCorasick.AddWord("BELIEVE");
    hAhoCorasick.AddWord("ELF");
    hAhoCorasick.AddWord("ELEPHANT");
    hAhoCorasick.AddWord("PHANTOM");
    hAhoCorasick.RefreshRedirectState();
    std::set<std::string> setRst = hAhoCorasick.SearchPattern("000abcdABcd012ELELF");
    return 0;
}