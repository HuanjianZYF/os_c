//
//  semaphore.c
//  os_c
//
//  用信号量打出了0101010101010101010101010101010101010101还是比较激动，虽然没什么技术含量
//  Created by mac_zyf on 2018/7/22.
//  Copyright © 2018年 mac_zyf. All rights reserved.
//

#include "ipc.h"

int semid; //信号量的标识符
void init_semaphore(void); //初始化信号量,num是信号量的值，这里只要一个信号量
void samaphore_p(int type); //信号量p操作,type表示信号量集合中的索引
void samaphore_v(int type); //信号量v操作,type表示信号量集合中的索引
void print_stdout(int type);

int main() {
    int i;
    init_semaphore();
    printf("%d %d\n", semid, semctl(semid, 0, GETVAL));
    
    if (fork() <= 0) {
        for (i = 0; i < 20; i++){
            print_stdout(1);
        }
    } else {
        for (i = 0; i < 20; i++){
            print_stdout(0);
        }
    }
    printf("\n");
}

//先做1进程的P操作，再做0进程的V操作
void print_stdout(int type) {
    char *ch;
    ch = type == 1 ? "1" : "0";
    
    samaphore_p(type);
    write(STDOUT_FILENO, ch, 1);
    samaphore_v(1 - type);
}

void init_semaphore() {
    union semun sem;
    
    //创建一个信号量
    semid = semget(IPC_PRIVATE, 2, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH | IPC_CREAT);
    
    //信号量的值是1，另一个是0
    sem.val = 1;
    semctl(semid, 0, SETVAL, sem);
    sem.val = 0;
    semctl(semid, 1, SETVAL, sem);
}

void samaphore_p(int type) {
    struct sembuf buf;
    
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;
    buf.sem_num = type;
    
    semop(semid, &buf, 1);
}

void samaphore_v(int type) {
    struct sembuf buf;
    
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO;
    buf.sem_num = type;
    
    semop(semid, &buf, 1);
}
