//
//  Attribute.cpp
//  L2UIUnpack
//

#include <codecvt>
#include <cstdio>
#include <cwchar>
#include <exception>
#include <locale>

#include <unistd.h>

#include "Attribute.h"

BoolAttribute::BoolAttribute(int fdes, const char* name, bool hidden, bool force) : Attribute(fdes, name, hidden, force) {
	IntAttribute attr(fdes);
	if (attr.value == 0 || attr.value == 1)
		value = static_cast<bool>(attr.value);
	else {
		this->hidden = true;
		value = false;
	}
}

IntAttribute::IntAttribute(int fdes, const char* name, bool hidden, bool force) : Attribute(fdes, name, hidden, force) {
	uint8_t bytes[4];
	if (::read(fdes, bytes, sizeof(bytes)) <= 0)
		throw std::runtime_error("Read failed");
	value = (bytes[3] << 24) |
			(bytes[2] << 16) |
			(bytes[1] << 8)  |
			 bytes[0];
}

StrAttribute::StrAttribute(int fdes, const char* name, bool hidden, bool force) : Attribute(fdes, name, hidden, force) {
	CompactIntAttribute att(fdes);
	len = static_cast<size_t>(att.value > 0 ? att.value : -2 * att.value);
	if (len != 0) {
		charset = att.value >= 0 ? charset::utf8 :
			charset::utf16;
		value = std::unique_ptr<uint8_t[]>(new uint8_t[len]);
		if (::read(fdes, value.get(), len) <= 0)
			throw std::runtime_error("Read failed");
		if (value[len - 1] != '\0')
			throw std::runtime_error("Expected null-terminated string");
		if (charset == charset::utf16) {
			std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
			std::string conv = converter.to_bytes((char16_t*)value.get());
			value = std::unique_ptr<uint8_t[]>(new uint8_t[conv.size() + 1]);
			memcpy(value.get(), conv.c_str(), conv.size() + 1);
		}
	}
}

CompactIntAttribute::CompactIntAttribute(int fdes, const char* name, bool hidden, bool force) : Attribute(fdes, name, hidden, force) {
	value = 0;
	uint8_t bytes[5];
	
	for (size_t i = 0; i < 5; i++) {
		if (::read(fdes, &bytes[i], 1) <= 0)
			throw std::runtime_error("Read failed");
		if (i == 0) {
			value |= bytes[0] & 0x3f;
			if (!(bytes[0] & 0x40))
				break;
		} else if (i == 4)
			value |= (bytes[4] & 0x1f) << 27;
		else {
			value |= (bytes[i] & 0x7f) << (6 + ((i - 1) * 7));
			if (!(bytes[i] & 0x80))
				break;
		}
	}
	if ((bytes[0] & 0x80) > 0)
		value *= -1;
}

FloatAttribute::FloatAttribute(int fdes, const char* name, bool hidden, bool force) : Attribute(fdes, name, hidden, force) {
	IntAttribute att(fdes);
	memcpy(&value, &att.value, sizeof(att.value));
}

EnumAttribute::EnumAttribute(int fdes, const char* name, bool hidden, bool force) : Attribute(fdes, name, hidden, force) {
	IntAttribute att(fdes);
	value = att.value;
	if (value < 0)
		value += 1;
}
