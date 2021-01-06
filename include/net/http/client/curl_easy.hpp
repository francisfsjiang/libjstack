
#ifndef LIBJSTACK_CURL_EASY_HPP
#define LIBJSTACK_CURL_EASY_HPP

#pragma once

#include <boost/noncopyable.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "net/http/client/curl_native.hpp"

#define DECLARE_CURL_OPTION(FUNCTION_NAME, OPTION_TYPE) \
	void FUNCTION_NAME(OPTION_TYPE arg); \
	void FUNCTION_NAME(OPTION_TYPE arg, native::CURLcode& ec);

#define DECLARE_CURL_OPTION_STRING(FUNCTION_NAME) \
	void FUNCTION_NAME(const char* str); \
	void FUNCTION_NAME(const char* str, native::CURLcode& ec); \
	void FUNCTION_NAME(const std::string& str); \
	void FUNCTION_NAME(const std::string& str, native::CURLcode& ec);

namespace libjstack::net::http::curl_easy {
    namespace native = libjstack::net::http::curl_native;

    class CurlEasy : public boost::noncopyable {
    public:
        CurlEasy();
        ~CurlEasy();

        void perform();

        typedef size_t (*write_function_t)(char* ptr, size_t size, size_t nmemb, void* userdata);
        DECLARE_CURL_OPTION(set_write_function, write_function_t)
        DECLARE_CURL_OPTION(set_write_data, void*)
        typedef size_t (*read_function_t)(void* ptr, size_t size, size_t nmemb, void* userdata);
        DECLARE_CURL_OPTION(set_read_function, read_function_t)
        DECLARE_CURL_OPTION(set_read_data, void*)


        DECLARE_CURL_OPTION_STRING(set_url)
        DECLARE_CURL_OPTION_STRING(set_useragent)

    private:
        void init();
        libjstack::net::http::curl_native::CURL* handle_;
    };
}

#undef DECLARE_CURL_OPTION
#undef DECLARE_CURL_OPTION_STRING

/*
#define DECLARE_CURL_OPTION_BOOLEAN(FUNCTION_NAME, OPTION_NAME) \
	inline void FUNCTION_NAME(bool enabled) \
	{ \
		boost::system::error_code ec; \
		FUNCTION_NAME(enabled, ec); \
		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
	} \
	inline void FUNCTION_NAME(bool enabled, boost::system::error_code& ec) \
	{ \
		ec = boost::system::error_code(native::curl_easy_setopt(handle_, OPTION_NAME, enabled ? 1L : 0L)); \
	}

#define DECLARE_CURL_OPTION_ENUM(FUNCTION_NAME, OPTION_NAME, ENUM_TYPE, OPTION_TYPE) \
	inline void FUNCTION_NAME(ENUM_TYPE arg) \
	{ \
		boost::system::error_code ec; \
		FUNCTION_NAME(arg, ec); \
		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
	} \
	inline void FUNCTION_NAME(ENUM_TYPE arg, boost::system::error_code& ec) \
	{ \
		ec = boost::system::error_code(native::curl_easy_setopt(handle_, OPTION_NAME, (OPTION_TYPE)arg)); \
	}

#define DECLARE_CURL_OPTION_STRING(FUNCTION_NAME, OPTION_NAME) \
	inline void FUNCTION_NAME(const char* str) \
	{ \
		boost::system::error_code ec; \
		FUNCTION_NAME(str, ec); \
		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
	} \
	inline void FUNCTION_NAME(const char* str, boost::system::error_code& ec) \
	{ \
		ec = boost::system::error_code(native::curl_easy_setopt(handle_, OPTION_NAME, str)); \
	} \
	inline void FUNCTION_NAME(const std::string& str) \
	{ \
		boost::system::error_code ec; \
		FUNCTION_NAME(str, ec); \
		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
	} \
	inline void FUNCTION_NAME(const std::string& str, boost::system::error_code& ec) \
	{ \
		ec = boost::system::error_code(native::curl_easy_setopt(handle_, OPTION_NAME, str.c_str())); \
	}

#define DECLARE_CURL_OPTION_GET_STRING(FUNCTION_NAME, OPTION_NAME) \
	inline std::string FUNCTION_NAME() \
	{ \
		char *info = NULL; \
		boost::system::error_code ec = boost::system::error_code(native::curl_easy_getinfo(handle_, OPTION_NAME, &info)); \
		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
		return info; \
	}

#define DECLARE_CURL_OPTION_GET_DOUBLE(FUNCTION_NAME, OPTION_NAME) \
	inline double FUNCTION_NAME() \
	{ \
		double info; \
		boost::system::error_code ec = boost::system::error_code(native::curl_easy_getinfo(handle_, OPTION_NAME, &info)); \
		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
		return info; \
	}

#define DECLARE_CURL_OPTION_GET_LONG(FUNCTION_NAME, OPTION_NAME) \
	inline long FUNCTION_NAME() \
	{ \
		long info; \
		boost::system::error_code ec = boost::system::error_code(native::curl_easy_getinfo(handle_, OPTION_NAME, &info)); \
		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
		return info; \
	}

#define DECLARE_CURL_OPTION_GET_LIST(FUNCTION_NAME, OPTION_NAME) \
	inline std::vector<std::string> FUNCTION_NAME() \
	{ \
		struct native::curl_slist *info; \
		std::vector<std::string> results; \
		boost::system::error_code ec = boost::system::error_code(native::curl_easy_getinfo(handle_, OPTION_NAME, &info)); \
		boost::asio::detail::throw_error(ec, BOOST_PP_STRINGIZE(FUNCTION_NAME)); \
		struct native::curl_slist *it = info; \
		while (it) \
		{ \
			results.push_back(std::string(it->data)); \
			it = it->next; \
		} \
		native::curl_slist_free_all(info); \
		return results; \
	}
*/

#endif //LIBJSTACK_CURL_EASY_HPP
