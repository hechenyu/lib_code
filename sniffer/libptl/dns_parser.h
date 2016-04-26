// -*- C/C++ -*-
// HeXu's
// 2012

#ifndef	__ptl_dns_parser_h
#define	__ptl_dns_parser_h

#include <stdint.h>
#include <string>

namespace ptl {

/**
 *  DNS header format
 *  reference: RFC 1035
 *
 *                                  1  1  1  1  1  1
 *    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                      ID                       |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                    QDCOUNT                    |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                    ANCOUNT                    |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                    NSCOUNT                    |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                    ARCOUNT                    |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *
 *  all fields are network byte order
 */
struct Dns_header {
	uint16_t id;			// id assigned by the program that generates any kind of query
	uint16_t flags;			// flags of dns
	uint16_t num_q;			// the number of questions
	uint16_t num_answ_rr;	// the number of resource records
	uint16_t num_auth_rr;	// the number of authority records
	uint16_t num_addi_rr;	// the number of additional records
};

/**
 *  Question section format
 *  reference: RFC 1035
 *
 *                                  1  1  1  1  1  1
 *    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                                               |
 *  /                     QNAME                     /
 *  /                                               /
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                     QTYPE                     |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |                     QCLASS                    |
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *
 *  all fields are network byte order
 */
struct Dns_question {
    std::string qname;
	uint16_t qtype;
	uint16_t qclass;
};

// 解析dns的question,
// nameptr指向question开始,
// end为数据区结尾(防止数据截断造成处理越界),
// 如果解析成功返回, question name在原始数据中的长度,
// 否则返回-1表示错误,
// 解析出来的域名放在name中.
int parser_dns_query(const uint8_t *beg, const uint8_t *end, Dns_question &qry);

}   // namespace ptl

#endif

