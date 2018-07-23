//
//  net_config.c
//  os_c
//
//  Created by mac_zyf on 2018/7/22.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "socket.h"

int main() {
    struct hostent *hostinfo; //计算机系统的主机信息
    struct netent *netinfo; //网络信息
    struct protoent *protoinfo; //协议信息
    struct servent *servinfo; //服务信息
    struct addrinfo addrinfo1, *addrinfo2, *addrinfo3; //地址信息
    
    char **address;
    int i;
    char a[100]; //用于保存地址
    
    //获得主机信息
    sethostent(1);
    while ((hostinfo = gethostent()) != NULL) {
        printf("%s ", hostinfo->h_name); //主机名字
        address = hostinfo->h_addr_list;
        i = 0;
        while (address[i] != NULL) {
            printf("%s ", inet_ntop(AF_INET, address[0], a, INET6_ADDRSTRLEN)); //将得到的地址转换成点分十进制
            i++;
        }
        printf("%d", hostinfo->h_length); //主机地址字节数
        printf("\n\n");
    }
    endhostent();
   
    //获取网络信息
    setnetent(1);
    while ((netinfo = getnetent()) != NULL) {
        printf("%s ", netinfo->n_name); //loopback 不明觉厉
        printf("%d\n\n", netinfo->n_net); //网络编号 127不知道什么东西。。
    }
    endnetent();
    
    //获取协议信息
    setprotoent(1);
    while ((protoinfo = getprotoent()) != NULL) {
        printf("%s ", protoinfo->p_name); //协议名字
        printf("%d\n", protoinfo->p_proto); //协议号
    }
    endprotoent();
    
    //获取服务信息
    setservent(1);
    while ((servinfo = getservent()) != NULL) {
        printf("%s ", servinfo->s_name); //服务名
        printf("%d ", servinfo->s_port); //端口号
        printf("%s\n", servinfo->s_proto); //协议名
    }
    endservent();
    
//    //获取某个主机的某个服务的信息
//    getaddrinfo("localhost", "blp5", &addrinfo1, &addrinfo2);
//    for (addrinfo3 = addrinfo2; addrinfo3 != NULL; addrinfo3 = addrinfo3->ai_next) {
//        printf("%s \n", inet_ntop(AF_INET, addrinfo3->ai_addr, a, INET6_ADDRSTRLEN));
//    }
}
