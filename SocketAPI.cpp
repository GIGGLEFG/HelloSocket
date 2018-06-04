#include<sys/types.h>
#include<netinet/in.h>  
#include<sys/socket.h>  
#include<sys/wait.h>  

int main() {
	/****************************************
	socket() 
	我们使用系统调用socket()来获得文件描述符：
	#include<sys/types.h>
	#include<sys/socket.h>
	int socket(int domain, int type, int protocol); 
	第一个参数domain设置为“AF_INET”。
	第二个参数是套接口的类型：SOCK_STREAM或
	SOCK_DGRAM。第三个参数设置为0。
	系统调用socket()只返回一个套接口描述符，如果出错，则返回-1。
	****************************************/
	//创建一个socket句柄
	int sockfd=socket(AF_INET,SOCK_STREAM,0);

	/*socket的地址信息*/  
    struct sockaddr_in dest_addr;	
    my_addr.sin_family=AF_INET;/*该属性表示 IPV4方式 接收本机或其他机器传输*/  
    my_addr.sin_port=htons(PORT);/*服务器接收的端口号*/  
    my_addr.sin_addr.s_addr=htonl(INADDR_ANY);/*IP地址，括号内容表示本机IP*/  
    bzero(&(my_addr.sin_zero),8);/*将其他属性置0*/  

	//客户端发出连接请求，传入句柄，目标地址和大小   
    int ret = connect(sockfd,(struct sockaddr*)&dest_addr,sizeof(struct sockaddr))
	if (ret == -1)
        printf("connect failed:%d",errno);//connect 失败时返回 -1 可以打印errno   

	//服务器绑定一个地址结构体和socket，作为服务器的标志
    if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))<0){  
        printf("bind error");  
        return -1;  
    }
	
	/****************************************
	listen() 
	如果你希望不连接到远程的主机，也就是说你希望等待一个进入的连接请求，然后再处理它们。
	这样，你通过首先调用listen()，然后再调用accept()来实现。系统调用listen()的形式如下：
	int listen(int sockfd, int backlog); 
	第一个参数是系统调用socket()返回的套接口文件描述符。
	第二个参数是进入队列中允许的连接的个数。进入的连接请求在使用系统调用accept()应答之前
	要在进入队列中等待。这个值是队列中最多可以拥有的请求的个数。大多数系统的缺省设置为20。
	你可以设置为5或者10。当出错时，listen()将会返回-1值。
	当然，在使用系统调用listen()之前，我们需要调用bind()绑定到需要的端口，否则系统内核将
	会让我们监听一个随机的端口。所以，如果你希望监听一个端口，下面是应该使用的系统调用的
	顺序：
	****************************************/
	//服务器开启监听 ，第一个参数为服务器本身的socket句柄，第二个参数是最大监听数	
	listen(sockfd,BACKLOG);

	/****************************************
	accept() 
	系统调用accept()比较起来有点复杂。在远程的主机可能试图使用connect()连接你使用
	listen()正在监听的端口。但此连接将会在队列中等待，直到使用accept()处理它。调用accept()
	之后，将会返回一个全新的套接口文件描述符来处理这个单个的连接。这样，对于同一个连接
	来说，你就有了两个文件描述符。原先的一个文件描述符正在监听你指定的端口，新的文件描
	述符可以用来调用send()和recv()。
	****************************************/
	//在这里阻塞知道接收到消息，参数分别是socket句柄，接收到的地址信息以及大小	
	int new_fd=accept(sockfd,(struct sockaddr*)&their_addr,&sin_size);

	//发送内容，参数分别是确认后连接新生成的句柄，buf的内容，buf的大小，其他信息（设为0即可）	 
	send(new_fd,"Hello World!",12,0);
	
	//接收内容，connect成功后可以接收服务器发出的数据，将数据打入buf，参数分别是句柄，储存处，最大长度，其他信息（设为0即可）。
	#define MAX_DATA 100/*接收到的数据最大程度*/
	char buf[MAX_DATA];/*储存接收数据*/
	recv(sockfd,buf,MAX_DATA,0);	 

#if 0
======== TCP ========
TCP_Server
socket()
bind()
listen()
accept()
write()
read()
close() 和shutdown()
 
TCP_Client
socket()
connect()
send() 和recv()
close() 和shutdown()
 
======== UDP ========
UDP_Server
socket()
bind()
sendto() 和recvfrom()
close() 和shutdown()
 
UDP_Client
socket()
sendto() 和recvfrom()
close() 和shutdown()

getpeername() 
gethostname()

#endif
	
	return 0;
}
