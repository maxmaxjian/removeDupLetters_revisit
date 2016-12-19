#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<char,std::vector<size_t>> & p) {
	os << p.first << ": ";
	std::copy(p.second.begin(), p.second.end(), std::ostream_iterator<size_t>(os," "));
	return os;
    }
}

class solution {
public:
    std::string removeDupLetters(const std::string & s) {
	std::map<char,std::vector<size_t>> dict;
	for (size_t i = 0; i < s.size(); ++i) {
	    if (dict.find(s[i]) == dict.end())
		dict[s[i]] = std::vector<size_t>();
	    dict[s[i]].push_back(i);
	}
	std::copy(dict.begin(), dict.end(), std::ostream_iterator<std::pair<char,std::vector<size_t>>>(std::cout, "\n"));
	return std::string();
    }
};

int main() {
    // std::string s{"bcabc"};
    std::string s{"cbacdcbc"};

    solution soln;
    auto rtn = soln.removeDupLetters(s);
}
