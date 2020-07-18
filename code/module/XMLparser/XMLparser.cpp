#include "XMLparser.h"
#include <stdexcept>
#include <third-party/tinyxml2.h>

std::string XMLParser::parseCurlResult(const std::string& xml) noexcept(false)
{
	tinyxml2::XMLDocument doc;
	auto err = doc.Parse(xml.c_str());
	if (err)
		throw std::runtime_error("parse xml failed.");
	if (std::string(doc.FirstChildElement("queryresult")->Attribute("error")) != "false")
		throw std::runtime_error("calculate latex result failed.");
	std::string res = doc.FirstChildElement("queryresult")->FirstChildElement("pod")->FirstChildElement("subpod")->FirstChildElement("plaintext")->GetText();
	return res;
}
