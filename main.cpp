#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <functional>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::pair<char,std::vector<size_t>> & p) {
	os << p.first << ": ";
	std::copy(p.second.begin(), p.second.end(), std::ostream_iterator<size_t>(os," "));
	return os;
    }

    std::ostream & operator<<(std::ostream & os, const std::pair<char,size_t> & p) {
        os << p.first << ": " << p.second;
        return os;
    }

    template<>
    struct less<std::pair<char,size_t>> {
        bool operator()(const std::pair<char,size_t> & p1, const std::pair<char,size_t> & p2) {
            return p1.second < p2.second;
        }
    };
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
        
        std::vector<std::pair<char,size_t>> strNoDups;
        auto it = dict.begin();
        size_t last = it->second.front();
        strNoDups.push_back(std::make_pair(it->first,last));
        ++it;        
        while (it != dict.end()) {
            if (it->second.size() > 1) {
                auto jt = std::upper_bound(it->second.begin(), it->second.end(), last);
                if (jt == it->second.end()) {
                    strNoDups.push_back(std::make_pair(it->first,it->second.back()));                    
                }
                else
                    strNoDups.push_back(std::make_pair(it->first,*jt));
            }
            else {
                strNoDups.push_back(std::make_pair(it->first,it->second.front()));
                last = strNoDups.back().second;
            }
            ++it;
        }

        std::sort(strNoDups.begin(), strNoDups.end(), std::less<std::pair<char,size_t>>());
        std::cout << "After removing:\n";
        std::copy(strNoDups.begin(), strNoDups.end(), std::ostream_iterator<std::pair<char,size_t>>(std::cout, "\n"));

        std::string result;
        for (auto it = strNoDups.begin(); it != strNoDups.end(); ++it)
            result += it->first;

        return result;
    }
};

int main() {
    // std::string s{"bcabc"};
    // std::string s{"cbacdcbc"};
    std::string s{"geeksforgeeks"};

    solution soln;
    auto rtn = soln.removeDupLetters(s);
    std::cout << "The resulting string after removing duplicate letters:\n"
              << rtn << std::endl;
}
