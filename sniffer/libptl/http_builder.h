#ifndef __ptl_http_builder_h
#define __ptl_http_builder_h

#include <string>

namespace ptl {

// Http packet构造的工具类
struct Http_builder {
    // 构造200 ok 报文
	static std::string build_200_ok(const char *payload);
	
};

}   // namespace ptl

#endif

