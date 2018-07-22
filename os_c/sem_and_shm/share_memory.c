//
//  share_memory.c
//  os_c
//
//  Created by mac_zyf on 2018/7/22.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "ipc.h"

void init_shareMemory(void);
int shmid; //共享内存id

int main() {
    void *share_memory_location;
    int *p;
    
    init_shareMemory();
    if (fork() <= 0) {
        share_memory_location = shmat(shmid, 0, 0);
        p = (int *) share_memory_location;
        *(p + 1) = '#'; //在共享内存里写一个字符
        shmdt(share_memory_location);
    } else {
        share_memory_location = shmat(shmid, 0, 0);
        p = (int *) share_memory_location;
        sleep(5);
        printf("%c\n", *(p + 1));
        shmdt(share_memory_location);
    }
}

void init_shareMemory(void) {
    shmid = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
}
