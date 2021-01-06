#include "net/http/client/curl_easy.hpp"

#define IMPLEMENT_CURL_OPTION(FUNCTION_NAME, OPTION_NAME, OPTION_TYPE) \
	void CurlEasy::FUNCTION_NAME(OPTION_TYPE arg) \
	{ \
		native::CURLcode ec; \
		FUNCTION_NAME(arg, ec); \
		if (ec != native::CURLE_OK) throw std::logic_error("curl set opt error."); \
	} \
	void CurlEasy::FUNCTION_NAME(OPTION_TYPE arg, native::CURLcode& ec) \
	{ \
		ec = native::curl_easy_setopt(handle_, OPTION_NAME, arg); \
	}

#define IMPLEMENT_CURL_OPTION_STRING(FUNCTION_NAME, OPTION_NAME) \
	void CurlEasy::FUNCTION_NAME(const char* str) \
	{ \
		native::CURLcode ec; \
		FUNCTION_NAME(str, ec); \
		if (ec != native::CURLE_OK) throw std::logic_error("curl set opt error."); \
	} \
	void CurlEasy::FUNCTION_NAME(const char* str, native::CURLcode& ec) \
	{ \
		ec = native::curl_easy_setopt(handle_, OPTION_NAME, str); \
	} \
	void CurlEasy::FUNCTION_NAME(const std::string& str) \
	{ \
		native::CURLcode ec; \
		FUNCTION_NAME(str, ec); \
		if (ec != native::CURLE_OK) throw std::logic_error("curl set opt error."); \
	} \
	void CurlEasy::FUNCTION_NAME(const std::string& str, native::CURLcode& ec) \
	{ \
		ec = native::curl_easy_setopt(handle_, OPTION_NAME, str.c_str()); \
	}

namespace libjstack::net::http::curl_easy {
    CurlEasy::CurlEasy() {
        init();
    }

    void CurlEasy::perform() {
        native::CURLcode res = native::curl_easy_perform(handle_);
    }

    void CurlEasy::init() {
        handle_ = native::curl_easy_init();

        if (!handle_)
        {
            throw std::bad_alloc();
        }
    }

    CurlEasy::~CurlEasy() {
        if (handle_)
        {
            native::curl_easy_cleanup(handle_);
            handle_ = nullptr;
        }
    }

    IMPLEMENT_CURL_OPTION(set_write_function, native::CURLOPT_WRITEFUNCTION, write_function_t)
    IMPLEMENT_CURL_OPTION(set_write_data, native::CURLOPT_WRITEDATA, void*)


    IMPLEMENT_CURL_OPTION_STRING(set_url, native::CURLOPT_URL)
    IMPLEMENT_CURL_OPTION_STRING(set_useragent, native::CURLOPT_USERAGENT)
}
/*
//#define IMPLEMENT_CURL_OPTION_BOOLEAN(FUNCTION_NAME, OPTION_NAME) \
//	inline void FUNCTION_NAME(bool enabled) \
//	{ \
//		native::CURLcode ec; \
//		FUNCTION_NAME(enabled, ec); \
//		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
//	} \
//	inline void FUNCTION_NAME(bool enabled, native::CURLcode& ec) \
//	{ \
//		ec = native::CURLcode(native::curl_easy_setopt(handle_, OPTION_NAME, enabled ? 1L : 0L)); \
//	}
//
//#define IMPLEMENT_CURL_OPTION_ENUM(FUNCTION_NAME, OPTION_NAME, ENUM_TYPE, OPTION_TYPE) \
//	inline void FUNCTION_NAME(ENUM_TYPE arg) \
//	{ \
//		native::CURLcode ec; \
//		FUNCTION_NAME(arg, ec); \
//		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
//	} \
//	inline void FUNCTION_NAME(ENUM_TYPE arg, native::CURLcode& ec) \
//	{ \
//		ec = native::CURLcode(native::curl_easy_setopt(handle_, OPTION_NAME, (OPTION_TYPE)arg)); \
//	}
//
//#define IMPLEMENT_CURL_OPTION_STRING(FUNCTION_NAME, OPTION_NAME) \
//	inline void FUNCTION_NAME(const char* str) \
//	{ \
//		native::CURLcode ec; \
//		FUNCTION_NAME(str, ec); \
//		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
//	} \
//	inline void FUNCTION_NAME(const char* str, native::CURLcode& ec) \
//	{ \
//		ec = native::CURLcode(native::curl_easy_setopt(handle_, OPTION_NAME, str)); \
//	} \
//	inline void FUNCTION_NAME(const std::string& str) \
//	{ \
//		native::CURLcode ec; \
//		FUNCTION_NAME(str, ec); \
//		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
//	} \
//	inline void FUNCTION_NAME(const std::string& str, native::CURLcode& ec) \
//	{ \
//		ec = native::CURLcode(native::curl_easy_setopt(handle_, OPTION_NAME, str.c_str())); \
//	}
//
//#define IMPLEMENT_CURL_OPTION_GET_STRING(FUNCTION_NAME, OPTION_NAME) \
//	inline std::string FUNCTION_NAME() \
//	{ \
//		char *info = NULL; \
//		native::CURLcode ec = native::CURLcode(native::curl_easy_getinfo(handle_, OPTION_NAME, &info)); \
//		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
//		return info; \
//	}
//
//#define IMPLEMENT_CURL_OPTION_GET_DOUBLE(FUNCTION_NAME, OPTION_NAME) \
//	inline double FUNCTION_NAME() \
//	{ \
//		double info; \
//		native::CURLcode ec = native::CURLcode(native::curl_easy_getinfo(handle_, OPTION_NAME, &info)); \
//		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
//		return info; \
//	}
//
//#define IMPLEMENT_CURL_OPTION_GET_LONG(FUNCTION_NAME, OPTION_NAME) \
//	inline long FUNCTION_NAME() \
//	{ \
//		long info; \
//		native::CURLcode ec = native::CURLcode(native::curl_easy_getinfo(handle_, OPTION_NAME, &info)); \
//		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
//		return info; \
//	}
//
//#define IMPLEMENT_CURL_OPTION_GET_LIST(FUNCTION_NAME, OPTION_NAME) \
//	inline std::vector<std::string> FUNCTION_NAME() \
//	{ \
//		struct native::curl_slist *info; \
//		std::vector<std::string> results; \
//		native::CURLcode ec = native::CURLcode(native::curl_easy_getinfo(handle_, OPTION_NAME, &info)); \
//		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
//		struct native::curl_slist *it = info; \
//		while (it) \
//		{ \
//			results.push_back(std::string(it->data)); \
//			it = it->next; \
//		} \
//		native::curl_slist_free_all(info); \
//		return results; \
//	}
 */