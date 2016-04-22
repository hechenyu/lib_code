#ifndef __ptl_httpresp_h
#define __ptl_httpresp_h

#include <stdint.h>
#include <string>

namespace ptl {

struct Httpresp_header {
	std::string version;
	std::string status;
	std::string reason;
	std::string content_type;
	std::string content_length;
};

bool httpresp_parse(uint8_t *beg, uint8_t *end, 
		struct Httpresp_header *httpresp_hdr);

}   // namespace ptl

#endif
