#include "string_tokenizer.h"
#include <functional>

std::string StringTokenizer::strip(std::string s) {
	std::string result = "";

	int n  = s.size();
	
	// repace all 'tab' -> 'space'
	for (int i = 0; i < n; ++i) 
		if (s[i] == '\t') s[i] = ' ';

	int left = 0, right = n - 1;
	
	// let left is the first position with s[left] != ' ';
	while (s[left] == ' ' && left < n) left++;

	// let right is the last position with s[right] != ' ';
	while (s[right] == ' ' && right >= 0) right--;


	std::function<bool(const char&)> validCharacter = [](const char& c) {
		return (c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9');
	};

	// then s[left..right] is not contains 'space' at begin and end
	// strip space between left and right, then assign s by the result
	// result is the string that contains words separate by only one 'space' character;
	for (; left <= right; ++left) {
		if (validCharacter(s[left])) 
		{
			if (left > 0 && s[left - 1] == ' ' && validCharacter(result.back())) 
				result += ' ';
			result += s[left];
		} 
		else 
		{
			if (s[left] == ' ');
			else
				result += s[left];
		}
	}

	return result;
}

// split the given string by separator
// return vector string
std::vector<std::string> StringTokenizer::parse(std::string s, std::string separator) {
	int offset = 0;
	size_t f = s.find(separator, offset);
	std::vector<std::string> result;
	while (f != std::string::npos) {
		result.push_back(s.substr(offset, f - offset));
		offset = f + separator.size();
		f = s.find(separator, offset);
	}
	result.push_back(s.substr(offset));
	return result;
}

// remove all 'dest' in string s
std::string StringTokenizer::remove(std::string s, char dest) {
	std::string res = "";
	for (auto x: s) if (x != dest) res += x;
	return res;
}
