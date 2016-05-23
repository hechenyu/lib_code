#ifndef	__snf_wrap_pcap_h
#define	__snf_wrap_pcap_h

#include <pcap.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 获得用于捕获网络数据包的数据包捕获描述字
 */
char *Pcap_lookupdev(); 

/**
 * 获得该网络设备的ip地址及掩码信息
 * device：网络设备名
 * netp：ip地址
 * maskp：掩码
 */
void Pcap_lookupnet(const char *device, bpf_u_int32 *netp, bpf_u_int32 *maskp);

/**
 * 获得用于捕获网络数据包的数据包捕获描述字
 * device：指定打开的网络设备名
 * snaplen：捕获数据的最大字节数
 * promisc：是否将网络接口设置为混杂模式
 * to_ms：指定超时时间(毫秒)
 */
pcap_t *Pcap_open_live(const char *device, int snaplen, int promisc, int to_ms);

/**
 * 将字符串描述的条件编译到过滤程序中
 * p：调用pcap_open_live函数获得的用于捕获网络数据包的描述字
 * fp：指向bpf_program结构的指针
 * str：指定要编译到过滤程序中的字符串
 * optimize：控制结果代码的优化
 * netmask：指定本地网络的子网掩码
 */
void Pcap_compile(pcap_t *p, struct bpf_program *fp, char *str, int optimize, bpf_u_int32 netmask);

/**
 * 将过滤规则应用到指定的数据包捕获描述字
 * p：调用pcap_open_live函数获得的用于捕获网络数据包的描述字
 * fp：指向bpf_program结构的指针，来自于调用pcap_compile函数获得的结果
 */
void Pcap_setfilter(pcap_t *p, struct bpf_program *fp); 

/**
 * 打开以前保存捕获数据包的文件, 用于读取:
 * fname参数指定打开的文件名,
 * 该文件中的数据格式与tcpdump和tcpslice兼容, 
 * "-"为标准输入
 */
pcap_t *Pcap_open_offline(const char *fname);

/**
 * 捕获单个数据包
 * p：调用pcap_open_live函数获得的用于捕获网络数据包的描述字
 * h：指向p_cap_pkthdr结构的指针的地址
 * 成功：获得的网络数据包内容
 * 失败：NULL (loop broken out or EOF, use pcap_file judge)
 */
const u_char *Pcap_next(pcap_t *p, struct pcap_pkthdr *h);

/**
 * 获取一个可打开的网络设备的列表
 * 返回pcap_if_t *需要通过pcap_freealldevs释放
 */
pcap_if_t *Pcap_findalldevs();

#ifdef __cplusplus
}
#endif

#endif
