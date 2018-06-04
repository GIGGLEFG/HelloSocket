#include<stdio.h>  
#include<stdlib.h>  
#include<errno.h>  
#include<string.h>  
#include<sys/types.h>  
#include<netinet/in.h>  
#include<sys/socket.h>  
#include<sys/wait.h>  
  
#define PORT 1500//���������յĶ˿ں�   
#define BACKLOG 5/*��������*/   
  
int main(){  
    int sockfd,new_fd;/*socket����ͽ������Ӻ���¾��*/  
    struct sockaddr_in my_addr;/*�������ĵ�ַ��Ϣ�ṹ�壬�����о�������Ը�ֵ*/  
    struct sockaddr_in their_addr;/*�ͻ��˵ĵ�ַ��Ϣ*/  
    int sin_size;  
  
    sockfd=socket(AF_INET,SOCK_STREAM,0);//����socket   
    if(sockfd==-1){  
        printf("socket failed:%d",errno);  
        return -1;  
    }  
    my_addr.sin_family=AF_INET;/*�����Ա�ʾ���ձ�����������������*/  
    my_addr.sin_port=htons(PORT);/*���������յĶ˿ں�*/  
    my_addr.sin_addr.s_addr=htonl(INADDR_ANY);/*IP��ַ���������ݱ�ʾ����IP*/  
    bzero(&(my_addr.sin_zero),8);/*������������0*/  
    if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))<0){//�󶨵�ַ�ṹ���socket  
        printf("bind error");  
        return -1;  
    }  
        listen(sockfd,BACKLOG);//�������� ����һ������������socket������ڶ�����������������   
        while(1){  
            sin_size=sizeof(struct sockaddr_in);  
            new_fd=accept(sockfd,(struct sockaddr*)&their_addr,&sin_size);//����������֪�����յ���Ϣ�������ֱ���socket��������յ��ĵ�ַ��Ϣ�Լ���С   
            if(new_fd==-1){  
                printf("receive failed");  
       		} else{  
	            printf("receive success");  
	            send(new_fd,"Hello World!",12,0);//�������ݣ������ֱ���ȷ�Ϻ����������ɵľ����buf�����ݣ�buf�Ĵ�С��������Ϣ����Ϊ0���ɣ�   
        	}  
    	}  
    return 0;  
}   

