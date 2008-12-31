#ifndef RSS_PARSER__H
#define RSS_PARSER__H

#include <string>

#include <rss.h>
#include <rsspp.h>

namespace newsbeuter {

	class configcontainer;
	class cache;

	class rss_parser {
		public:
			rss_parser(const char * uri, cache * c, configcontainer *, rss_ignores * ii);
			~rss_parser();
			std::tr1::shared_ptr<rss_feed> parse();
			bool check_and_update_lastmodified();
		private:
			void replace_newline_characters(std::string& str);
			std::string render_xhtml_title(const std::string& title, const std::string& link);
			time_t parse_date(const std::string& datestr);
			unsigned int monthname_to_number(const std::string& mon);
			void set_rtl(std::tr1::shared_ptr<rss_feed>& feed, const char * lang);
			int correct_year(int year);

			void retrieve_uri(const std::string& uri);
			void download_http(const std::string& uri);
			void get_execplugin(const std::string& plugin);
			void download_filterplugin(const std::string& filter, const std::string& uri);

			void check_and_log_error();

			void fill_feed_fields(std::tr1::shared_ptr<rss_feed>& feed);
			void fill_feed_items(std::tr1::shared_ptr<rss_feed>& feed);

			void set_item_title(std::tr1::shared_ptr<rss_feed>& feed, std::tr1::shared_ptr<rss_item>& x, rsspp::item& item);
			void set_item_author(std::tr1::shared_ptr<rss_item>& x, rsspp::item& item);
			void set_item_content(std::tr1::shared_ptr<rss_item>& x, rsspp::item& item);
			void set_item_enclosure(std::tr1::shared_ptr<rss_item>& x, rsspp::item& item);
			std::string get_guid(rsspp::item& item);

			void add_item_to_feed(std::tr1::shared_ptr<rss_feed>& feed, std::tr1::shared_ptr<rss_item>& item);

			void handle_content_encoded(std::tr1::shared_ptr<rss_item>& x, rsspp::item& item);
			void handle_itunes_summary(std::tr1::shared_ptr<rss_item>& x, rsspp::item& item);

			std::string my_uri;
			cache * ch;
			configcontainer *cfgcont;
			bool skip_parsing;
			bool is_valid;
			rss_ignores * ign;
			rsspp::feed f;
	};

}

#endif
