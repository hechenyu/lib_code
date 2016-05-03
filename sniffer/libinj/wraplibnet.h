#ifndef	__inj_wraplibnet_h
#define	__inj_wraplibnet_h

#include <libnet.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 初始化libnet环境, 返回libnet描述符
 * injection_type: 构造发送的报文类型, 例如: LIBNET_RAW4构造发送IPv4报文
 * device：指定打开的网络设备名
 */
libnet_t *Libnet_init(int injection_type, const char *device);

/**
 * 将IP地址字符串或是DNS域名转换成网络字节序的IP地址, 仅支持IPv4
 * l: 调用libnet_init函数获得的libnet上下文
 * host_name: IP地址字符串或是DNS域名
 * use_name: LIBNET_RESOLVE或LIBNET_DONT_RESOLVE
 */
uint32_t Libnet_name2addr4(libnet_t *l, char *host_name, uint8_t use_name);

/**
 * 将预先构造好的报文(通过libnet_bulic_xxx)发送到网络接口
 * l: 调用libnet_init函数获得的libnet上下文
 */
int Libnet_write(libnet_t *l);

/**
 * 构造以太网报首
 * dst: 目的MAC地址
 * src: 源MAC地址
 * type: 上层协议类型
 * payload: 可选有效载荷(可为NULL)
 * paylaod_s: payload长度(可为0)
 * l: 调用libnet_init函数获得的libnet上下文
 * ptag: 协议标签, 0表示新创建, 其他表示一个已存在的报首
 */
libnet_ptag_t Libnet_build_ethernet(const uint8_t *dst, const uint8_t *src, uint16_t type, 
        const uint8_t* payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag);

/**
 * 构造IPv4报首
 * ip_len: ip报文总长度
 * tos: 服务类型
 * id: 标识
 * frag: 标志和分片偏移
 * ttl: 生存时间
 * prot: 上层协议类型
 * sum: 校验和(0标识libnet自动填写)
 * src: 源IP地址
 * dst: 目的IP地址
 * payload: 可选有效载荷(可为NULL)
 * paylaod_s: payload长度(可为0)
 * l: 调用libnet_init函数获得的libnet上下文
 * ptag: 协议标签, 0表示新创建, 其他表示一个已存在的报首
 */
libnet_ptag_t Libnet_build_ipv4(uint16_t ip_len, uint8_t tos, uint16_t id, uint16_t frag, 
        uint8_t ttl, uint8_t prot, uint16_t sum, uint32_t src, uint32_t dst, 
        const uint8_t* payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag);

#ifdef __cplusplus
}
#endif

#endif
