#ifndef	__snf_wrap_libnet_h
#define	__snf_wrap_libnet_h

#include <libnet.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 初始化libnet环境, 返回libnet描述符(描述符最终应该通过libnet_destroy释放)
 * injection_type: 构造发送的报文类型, 例如: LIBNET_RAW4构造发送IPv4报文
 * device：指定打开的网络设备名
 */
libnet_t *Libnet_init(int injection_type, const char *device);

/**
 * 获取设备的MAC地址
 */ 
struct libnet_ether_addr *Libnet_get_hwaddr(libnet_t *l);

/**
 * 获取设备的IPv4地址
 */
uint32_t Libnet_get_ipaddr4(libnet_t *l);

/**
 * 将IP地址字符串或是DNS域名转换成网络字节序的IP地址, 仅支持IPv4
 * l: 调用libnet_init函数获得的libnet上下文
 * host_name: IP地址字符串或是DNS域名
 * use_name: LIBNET_RESOLVE或LIBNET_DONT_RESOLVE
 */
uint32_t Libnet_name2addr4(libnet_t *l, char *host_name, uint8_t use_name);

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
 * 自动构造以太网报首
 * dst: 目的MAC地址
 * type: 上层协议类型
 * l: 调用libnet_init函数获得的libnet上下文
 */
libnet_ptag_t Libnet_autobuild_ethernet(const uint8_t *dst, uint16_t type, libnet_t *l);

/**
 * 构造ARP报首
 * hrd: 链路层地址类型
 * pro: 网络层地址类型
 * hln: 链路层地址长度
 * pln: 网络层地址长度
 * op: ARP操作类型
 * sha: 发送方链路层地址
 * spa: 发送方网络地址
 * tha: 目标链路层地址
 * tpa: 目标网络地址
 * payload: 可选有效载荷(可为NULL)
 * paylaod_s: payload长度(可为0)
 * l: 调用libnet_init函数获得的libnet上下文
 * ptag: 协议标签, 0表示新创建, 其他表示一个已存在的报首
 */
libnet_ptag_t Libnet_build_arp(uint16_t hrd, uint16_t pro, uint8_t hln, uint8_t pln,
        uint16_t op, const uint8_t *sha, const uint8_t *spa, const uint8_t *tha, const uint8_t *tpa,
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

/**
 * 构造IP选项
 * options: IP选项字节序列
 * options_s: IP选项字节序列长度
 * l: 调用libnet_init函数获得的libnet上下文
 * ptag: 协议标签, 0表示新创建, 其他表示一个已存在的报首
 */
libnet_ptag_t Libnet_build_ipv4_options(const uint8_t *options, uint32_t options_s, libnet_t *l,
        libnet_ptag_t ptag);

/**
 * 构造TCP报首
 * sp: 源端口
 * dp: 目的端口
 * seq: 序号
 * akc: 确认号
 * control: 控制字段
 * win: 窗口尺寸
 * sum: 校验和(0标识libnet自动填写)
 * urg: 紧急指针
 * len: tcp报文总长度(用于计算校验和)
 * payload: 可选有效载荷(可为NULL)
 * paylaod_s: payload长度(可为0)
 * l: 调用libnet_init函数获得的libnet上下文
 * ptag: 协议标签, 0表示新创建, 其他表示一个已存在的报首
 */
libnet_ptag_t Libnet_build_tcp(uint16_t sp, uint16_t dp, uint32_t seq, uint32_t ack,
        uint8_t control, uint16_t win, uint16_t sum, uint16_t urg, uint16_t len, 
        const uint8_t* payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag);

/**
 * 构造TCP选项
 * options: TCP选项字节序列
 * options_s: TCP选项字节序列长度
 * l: 调用libnet_init函数获得的libnet上下文
 * ptag: 协议标签, 0表示新创建, 其他表示一个已存在的报首
 */
libnet_ptag_t Libnet_build_tcp_options(const uint8_t *options, uint32_t options_s, libnet_t *l,
        libnet_ptag_t ptag);

/**
 * 构造TCP报首
 * sp: 源端口
 * dp: 目的端口
 * udp: udp报文总长度
 * sum: 校验和(0标识libnet自动填写)
 * payload: 可选有效载荷(可为NULL)
 * paylaod_s: payload长度(可为0)
 * l: 调用libnet_init函数获得的libnet上下文
 * ptag: 协议标签, 0表示新创建, 其他表示一个已存在的报首
 */
libnet_ptag_t Libnet_build_udp(uint16_t sp, uint16_t dp, uint16_t len, uint16_t sum, 
        const uint8_t* payload, uint32_t payload_s, libnet_t *l, libnet_ptag_t ptag);

/**
 * 构造DNS报首
 * h_len: LIBNET_UDP_DNSV4_H or LIBNET_TCP_DNSV4_H
 * id: 标识
 * flags: 标志
 * num_q: 问题记录数
 * num_anws_rr: 回答记录数
 * num_auth_rr: 授权记录数
 * num_addi_rr: 附加记录数
 * payload: 可选有效载荷(可为NULL)
 * paylaod_s: payload长度(可为0)
 * l: 调用libnet_init函数获得的libnet上下文
 * ptag: 协议标签, 0表示新创建, 其他表示一个已存在的报首
 */
libnet_ptag_t Libnet_build_dnsv4(uint16_t h_len, uint16_t id, uint16_t flags,
        uint16_t num_q, uint16_t num_anws_rr, uint16_t num_auth_rr,
        uint16_t num_addi_rr, const uint8_t* payload, uint32_t payload_s, libnet_t *l,
        libnet_ptag_t ptag);

/**
 * 从libnet上下文中拉取预构建的报文
 * 只支持advanced模式的libnet_init
 * l: 调用libnet_init函数获得的libnet上下文
 * packet: 包含报文的内容的buffer(*packet使用后需要通过libnet_adv_free_packet释放)
 * packet_s: 包含报文的内容的buffer长度
 */
void Libnet_adv_cull_packet(libnet_t *l, uint8_t **packet, uint32_t *packet_s);

/**
 * 将预先构造好的报文(通过libnet_bulic_xxx)发送到网络接口
 * l: 调用libnet_init函数获得的libnet上下文(发送成功后, 应该通过libnet_clear_packet释放内存)
 */
int Libnet_write(libnet_t *l);

#ifdef __cplusplus
}
#endif

#endif
