#include "JsonParser.h"
#include <rapidjson/document.h>
#include <cctype>
#include <stdexcept>


std::string JsonParser::parseCurlReturnVal(const std::string& json, std::string API)
{
	for (auto& ch : API) {
		ch = std::tolower(ch);
	}

	if (API == "baidu")
		return parseCurlReturnValBaidu(json);
	else if (API == "mathpix")
		return parseCurlReturnValMathpix(json);
	else
		throw std::runtime_error("Invalid API for formula recognition");
}

std::string JsonParser::parseCurlReturnValBaidu(const std::string& json)
{
	rapidjson::Document doc;
	doc.Parse(json.c_str());
	if (doc.HasMember("error_code"))
		throw std::runtime_error(doc["error_msg"].GetString());
	std::string latex_string;
	for (auto& res : doc["words_result"].GetArray())
	{
		latex_string += res["words"].GetString();
	}
	return latex_string;
}

std::string JsonParser::parseCurlReturnValMathpix(const std::string& json)
{
	rapidjson::Document doc;
	doc.Parse(json.c_str());
	if (doc.HasMember("error"))
		throw std::runtime_error(doc["error_info"]["message"].GetString());
	return doc["latex_simplified"].GetString();
}
