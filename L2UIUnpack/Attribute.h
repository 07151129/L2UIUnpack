//
//  Attribute.h
//  L2UIUnpack
//

#ifndef Attribute_h
#define Attribute_h

#include <cstdint>
#include <memory>
#include <set>
#include <string>

#include <libxml/tree.h>

#include "ElementBase.h"

struct Attribute : public ElementBase {
	int fdes;
	std::string name;
	bool hidden; /* Ignore when dumping if true */
	bool force; /* Force dumping even if the value is default */
	
	Attribute() = delete;
	Attribute(int fdes, const char* name = "", bool hidden = false, bool force = false) : fdes(fdes), name(name), hidden(hidden), force(force) {};
	Attribute(const char* name = "", bool hidden = false, bool force = false) : name(name), hidden(hidden), force(force) {};
};

struct BoolAttribute : public Attribute {
	bool value;
	
	BoolAttribute(int fdes, const char* name = "", bool hidden = false, bool force = false);
	BoolAttribute(bool value, const char* name = "", bool hidden = false, bool force = false) :
	Attribute(name, hidden, force), value(value) {};
	
	virtual bool dump(xmlNodePtr branch) const override final;
};

struct IntAttribute : public Attribute {
	int32_t value;
	std::set<int32_t> defaultValues {-9999};
	
	struct IntValue {
		int32_t value;
		
		IntValue() = delete;
		IntValue(int32_t val) : value(val) {};
	};
	
	IntAttribute(int fdes, const char* name = "", bool hidden = false, bool force = false);
	IntAttribute(IntValue value, const char* name = "", bool hidden = false, bool force = false) :
	Attribute(name, hidden, force), value(value.value) {};
	
	virtual bool dump(xmlNodePtr branch) const override final;
};

struct StrAttribute : public Attribute {
	size_t len;
	std::unique_ptr<uint8_t[]> value;
	const char* defaultValue {"undefined"};
	
	enum charset {
		utf8,
		utf16
	} charset = utf8;
	
	StrAttribute(int fdes, const char* name = "", bool hidden = false, bool force = false);
	
	virtual bool dump(xmlNodePtr branch) const override final;
};

struct CompactIntAttribute : public Attribute {
	int32_t value;
	std::set<int32_t> defaultValues {-9999};
	
	CompactIntAttribute(int fdes, const char* name = "", bool hidden = false, bool force = false);
	
	virtual bool dump(xmlNodePtr branch) const override final;
};

struct FloatAttribute : public Attribute {
	float value;
	std::set<float> defaultValues {-9999};
	
	FloatAttribute(int fdes, const char* name = "", bool hidden = false, bool force = false);
	
	virtual bool dump(xmlNodePtr branch) const override final;
};

struct EnumAttribute : public Attribute {
	int32_t value;
	
	EnumAttribute(int fdes, const char* name = "", bool hidden = false, bool force = false);
	virtual const char* const* getNameTable() const = 0;
	virtual size_t getNameTableSz() const = 0;
	
	virtual bool dump(xmlNodePtr branch) const override final;
};

#endif /* Attribute_h */
