#include "InputParser.h"

const std::string& InputParser::getCmdOption(const std::string& option) const {
	std::vector<std::string>::const_iterator itr;
	itr = std::find(this->tokens.begin(), this->tokens.end(), option);
	if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
		return *itr;
	}
	static const std::string empty_string("");
	return empty_string;
}
bool InputParser::cmdOptionExists(const std::string& option) const {
	bool check = std::find(this->tokens.begin(), this->tokens.end(), option)
		!= this->tokens.end();
	if (check == false && option == "" && this->tokens.begin() == this->tokens.end())
		check = true;
	return check;
}