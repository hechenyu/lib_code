#include "http_builder.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <string>

using std::string;

namespace ptl {

namespace {

// 获取当前时间
// 格式如: Mon, 29 Jun 2015 23:24:42 GMT
string get_date_gmt()
{
    time_t t = time(0);
    char timebuf[36] = {0};
    strftime(timebuf, 36, "%a, %d %b %Y %H:%M:%S GMT", gmtime(&t));
    return timebuf;
}

}	// namespace 

// 构造http200报文
string Http_builder::build_200_ok(const char *payload)
{
	const char *http_header_template =
		"HTTP/1.0 200 OK\r\n"
		"Date: %s\r\n"
		"Server: nginx\r\n"
		"Content-Length: %d\r\n"
		"Keep-Alive: timeout=2, max=20\r\n"
		"Connection: Keep-Alive\r\n"
		"Content-Type: text/html; charset=iso-8859-1\r\n"
		"\r\n";

	char http_header_data[1024];
	memset(http_header_data, 0, sizeof(http_header_data));
    int payload_len = strlen(payload);
	sprintf(http_header_data, http_header_template, get_date_gmt().c_str(), payload_len);

    string http_200_ok;
    http_200_ok.resize(sizeof(http_header_data) + payload_len + 1);
	sprintf((char *) http_200_ok.c_str(), "%s%s", http_header_data, payload);

	return http_200_ok;
}

}   // namespace ptl
