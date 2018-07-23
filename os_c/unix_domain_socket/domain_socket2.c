//
//  domain_socket2.c
//  os_c
//
//  Created by mac_zyf on 2018/7/23.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "domain_socket.h"

int main() {
    struct sockaddr_un unaddress; //域套接字地址
    int unsocket; //域套接字
    
    //创建有名字的域套接字
    unsocket = socket(AF_UNIX, SOCK_STREAM, 0);
    unaddress.sun_family = AF_UNIX;
    strcpy(unaddress.sun_path, "/Users/zyf/Downloads/c.socket");
    unaddress.sun_len = 30;
    bind(unsocket, (struct sockaddr *) &unaddress, 100);
    
    //不学了.....
}
