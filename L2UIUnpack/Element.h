//
//  Element.h
//  L2UIUnpack
//

#ifndef Element_hpp
#define Element_hpp

#include <cstdio>
#include <memory>
#include <type_traits>
#include <vector>

#include <libxml/tree.h>

#include "Attribute.h"
#include "ElementBase.h"

struct Element : public ElementBase {
	std::vector<std::unique_ptr<ElementBase>> children;
	int fdes;
	const char* tag = nullptr;
	
	virtual bool dump(xmlNodePtr dst) const override final;
	
	Element(int fdes, const char* tag = "") : fdes(fdes), tag(tag) {
		children = std::vector<std::unique_ptr<ElementBase>>();
	};
};

template <typename T, typename LenType = IntAttribute> class List : public ElementBase {
private:
	std::vector<std::unique_ptr<T>> backing;
	
	int fdes;
	LenType len;
public:
	List() = delete;
	
	List(int fdes) : fdes(fdes), len(fdes) {
		static_assert(std::is_base_of<ElementBase, T>::value,
					  "Template argument to List must extend ElementBase");
		static_assert(std::is_same<IntAttribute, LenType>::value ||
					  std::is_same<CompactIntAttribute, LenType>::value,
					  "LenType of List must be IntAttribute or CompactIntAttribute");

		backing.reserve(static_cast<size_t>(len.value));
		for (int32_t i = 0; i < len.value; i++)
			backing.emplace_back(std::unique_ptr<T>(new T(fdes)));
	}
	
	std::vector<std::unique_ptr<T>>& value() {
		return backing;
	}
	
	virtual bool dump(xmlNodePtr dst) const override final {
		bool nondefault = false;
		for (const auto& el : backing)
			nondefault |= el->dump(dst);
		return nondefault;
	}
};

#endif /* Element_h */
