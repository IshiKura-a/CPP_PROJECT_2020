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
	auto pod = doc.FirstChildElement("queryresult")->FirstChildElement("pod");
	if (!pod) throw std::runtime_error("Unexpected return value: result not found");
	auto subpod = pod->FirstChildElement("subpod");
	if (!subpod) throw std::runtime_error("Unexpected return value: result not found");
	auto resText = subpod->FirstChildElement("plaintext");
	if (!resText) throw std::runtime_error("Unexpected return value: result not found");
	auto res = resText->GetText();
	return res;
}
