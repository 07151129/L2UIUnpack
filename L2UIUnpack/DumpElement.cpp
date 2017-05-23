//
//  DumpElement.cpp
//  L2UIUnpack
//

#include <exception>
#include <limits>
#include <memory>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <libxml/tree.h>

#include "Attribute.h"
#include "Element.h"

bool BoolAttribute::dump(xmlNodePtr dst) const {
	if (hidden)
		return false;
	if (name.empty())
		throw std::runtime_error("Dumping BoolAttribute with no name");
	xmlSetProp(dst, BAD_CAST name.c_str(), value ? BAD_CAST "true" : BAD_CAST "false");
	return true;
}

bool StrAttribute::dump(xmlNodePtr dst) const {
	if (hidden)
		return false;
	if (name.empty())
		throw std::runtime_error("Dumping StrAttribute with no name");
	const char* val = nullptr;
	if (value)
		val = (const char*)value.get();
	else
		val = "";
	if (!force && charset == charset::utf8 && !std::strcmp(defaultValue, val))
		return false;

	xmlSetProp(dst, BAD_CAST name.c_str(), BAD_CAST val);
	return true;
}

bool IntAttribute::dump(xmlNodePtr dst) const {
	if (hidden)
		return false;
	if (!force && defaultValues.find(value) != defaultValues.end())
		return false;
	if (name.empty())
		throw std::runtime_error("Dumping IntAttribute with no name");
	xmlSetProp(dst, BAD_CAST name.c_str(), BAD_CAST std::to_string(value).c_str());
	return true;
}

bool CompactIntAttribute::dump(xmlNodePtr dst) const {
	if (hidden)
		return false;
	if (!force && defaultValues.find(value) != defaultValues.end())
		return false;
	if (name.empty())
		throw std::runtime_error("Dumping CompactIntAttribute with no name");
	xmlSetProp(dst, BAD_CAST name.c_str(), BAD_CAST std::to_string(value).c_str());
	return true;
}

bool FloatAttribute::dump(xmlNodePtr dst) const {
	if (hidden)
		return false;
	if (!force && (std::isnan(value) || defaultValues.find(value) != defaultValues.end() || value <= std::numeric_limits<float>::epsilon()))
		return false;
	if (name.empty())
		throw std::runtime_error("Dumping FloatAttribute with no name");
	xmlSetProp(dst, BAD_CAST name.c_str(), BAD_CAST std::to_string(value).c_str());
	return true;
}

bool EnumAttribute::dump(xmlNodePtr dst) const {
	if (hidden)
		return false;
	if (name.empty())
		throw std::runtime_error("Dumping EnumAttribute with no name");
	if (value < 0 || static_cast<size_t>(value) >= getNameTableSz())
		throw std::runtime_error(std::string(name) + " value " + std::to_string(value) + " out of nameTable bounds");
	if (!force && !std::strcmp(getNameTable()[value], "None"))
		return false;
	xmlSetProp(dst, BAD_CAST name.c_str(), BAD_CAST getNameTable()[value]);
	return true;
}

bool Element::dump(xmlNodePtr dst) const {
	bool nondefault = false;
	if (!tag)
		throw std::runtime_error("Dumping Element with no name");
	xmlNodePtr node = xmlNewChild(dst, nullptr, BAD_CAST tag, nullptr);
	for (const auto& child : children)
		nondefault |= child->dump(node);
	if (!nondefault) {
		xmlUnlinkNode(node);
		xmlFreeNode(node);
	}
	return nondefault;
}
