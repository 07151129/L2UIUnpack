//
//  DumpSchema.cpp
//  L2UIUnpack
//

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <libxml/tree.h>

#include "Schema.h"

constexpr const char* Schema::versionNames[];

void Schema::dump(const ElementBase* el, std::unique_ptr<char[]> name, const char* comment_str) {
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr l2ui_node = xmlNewNode(nullptr, BAD_CAST "L2UI");
	
	xmlNodePtr comment = xmlNewComment(BAD_CAST comment_str);
	xmlDocSetRootElement(doc, comment);
	xmlAddSibling(comment, l2ui_node);
	
	xmlSetProp(l2ui_node, BAD_CAST "xmlns", BAD_CAST "http://www.lineage2.co.kr/ui");
	xmlSetProp(l2ui_node, BAD_CAST "xmlns:xsi", BAD_CAST "http://www.w3.org/2001/XMLSchema-instance");
	xmlSetProp(l2ui_node, BAD_CAST "xsi:schemaLocation", BAD_CAST "http://www.lineage2.co.kr/ui ..\\..\\Schema.xsd");
	
	el->dump(l2ui_node);
	xmlSaveFormatFile(name.get(), doc, 1);
	xmlFreeDoc(doc);
}

static char* filename(const ElementBase* el_base) {
	auto el = static_cast<const Element*>(el_base);
	const char* res = nullptr;
	
	if (!strcmp(el->tag, "Shortcut"))
		res = (const char*)((StrAttribute*)el->children.front().get())->value.get();
	else if (!strcmp(el->tag, "Window"))
		res = (const char*)((StrAttribute*)((Element*)(el->children.front().get()))->children.front().get())->value.get();
	else
		res = el->tag;
	
	char* res_xml = new char[strlen(res) + strlen(".xml") + 1];
	sprintf(res_xml, "%s.xml", res);
	return res_xml;
}

void Schema::dump() {
	static constexpr const char* CREATEDBY = "Created by L2UIUnpack";
	if (!xdat_path)
		xdat_path = "(unknown)";
	size_t comment_len = strlen(CREATEDBY) + 1 + strlen(xdat_path) +
	strlen(" from ") + 3 + strlen(versionNames[ver]);
	auto comment_str = std::unique_ptr<char[]>(new char[comment_len]);
	sprintf(comment_str.get(), "%s from %s (%s)", CREATEDBY, xdat_path, versionNames[ver]);

	for (const auto& child : list_children) {
		auto el_list = static_cast<List<ElementBase>*>(child.get());
		
		for (const auto& el : el_list->value()) {
			auto file = std::unique_ptr<char[]>(filename(el.get()));
			dump(el.get(), std::move(file), comment_str.get());
		}
	}
	for (const auto& child : single_children) {
		auto file = std::unique_ptr<char[]>(filename(child.get()));
		dump(child.get(), std::move(file), comment_str.get());
	}
}
