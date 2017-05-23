//
//  Schema.h
//  L2UIUnpack
//

#ifndef Schema_h
#define Schema_h

#include <memory>
#include <vector>

#include "Element.h"

class Schema {
private:
	void dump(const ElementBase* el, std::unique_ptr<char[]> name, const char* comment_str);
protected:
	enum Version {
		CT26,
	};
	static constexpr const char* versionNames[] {"CT26"};
	Version ver;
	int fdes;
	const char* xdat_path;
	std::vector<std::unique_ptr<ElementBase>> list_children;
	std::vector<std::unique_ptr<ElementBase>> single_children;

public:
	Schema() = delete;
	Schema(Version ver, int fdes, const char* xdat_path = nullptr)
	: ver(ver), fdes(fdes), xdat_path(xdat_path) {};
	
	void dump();
};

#endif /* Schema_h */
