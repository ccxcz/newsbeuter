/* rsspp - Copyright (C) 2008 Andreas Krennmair <ak@newsbeuter.org>
 * Licensed under the MIT/X Consortium License. See file LICENSE
 * for more information.
 */

#ifndef RSSPP_INTERNAL__H
#define RSSPP_INTERNAL__H

#include <rsspp.h>

#define CONTENT_URI		"http://purl.org/rss/1.0/modules/content/"
#define RDF_URI			"http://www.w3.org/1999/02/22-rdf-syntax-ns#"
#define ITUNES_URI		"http://www.itunes.com/dtds/podcast-1.0.dtd"
#define DC_URI			"http://purl.org/dc/elements/1.1/"
#define ATOM_0_3_URI	"http://purl.org/atom/ns#"
#define ATOM_1_0_URI	"http://www.w3.org/2005/Atom"

namespace rsspp {

struct rss_parser {
		virtual void parse_feed(feed& f, xmlNode * rootNode) = 0;
		virtual ~rss_parser() { }
	protected:
		std::string get_content(xmlNode * node);
		std::string w3cdtf_to_rfc822(const std::string& w3cdtf);
};

struct rss_09x_parser : public rss_parser {
		virtual void parse_feed(feed& f, xmlNode * rootNode);
	private:
		item parse_item(xmlNode * itemNode);
};

struct rss_20_parser : public rss_09x_parser {
};

struct rss_10_parser : public rss_parser {
	virtual void parse_feed(feed& f, xmlNode * rootNode);
};


struct atom_parser : public rss_parser {
		virtual void parse_feed(feed& f, xmlNode * rootNode);
	private:
		item parse_entry(xmlNode * itemNode);
};

struct rss_parser_factory {
	static rss_parser * get_object(feed& f);
};

}

#endif
