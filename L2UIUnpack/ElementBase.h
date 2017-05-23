//
//  ElementBase.h
//  L2UIUnpack
//

#ifndef ElementBase_h
#define ElementBase_h

#include <libxml/tree.h>

struct ElementBase {
	/* True if non-default value */
	virtual bool dump(xmlNodePtr branch) const = 0;
	
	virtual ~ElementBase() = 0;
};

#endif /* ElementBase_h */
