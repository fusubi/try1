#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>
#include<sys/types.h>
#include<winsock.h>
#include<errno.h>
#include<fcntl.h>
#include<Winsock.h>
#include<time.h>
#include<ws2tcpip.h>
#pragma comment(lib,"winsock.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"lwsock32.lib")link_libraries(-lIphlpapi);
#pragma warning(disable 4996)
int main(){
WSADATA wsaData;
WSAStartup(MAKEWORD(2,2),&wsaData);
int s_fd,c_fd;
struct sockaddr_in ser,c_addr;
int ret;
char buff[1024];
char buff_1[1024];
char hav[1000];
s_fd=socket(AF_INET,SOCK_STREAM,0);
if(s_fd<0){
	perror("socker");
	exit(0);
}
ser.sin_port=htons(11111);
ser.sin_family=AF_INET;
ser.sin_addr.s_addr=INADDR_ANY;
ret=bind(s_fd,(struct sockaddr *)&ser,sizeof(struct sockaddr));
if(ret<0){
	perror("bing");
}
ret=listen(s_fd,3);
if(ret<0){
	perror("listen");
}
int addrlen=sizeof(struct sockaddr_in);
printf("wait to connect....\n");
while(1){
ret=accept(s_fd,(struct sockaddr *)&c_addr,&addrlen);
if(ret<0){
	perror("accept");
}
printf("connected by %s\n",inet_ntoa(c_addr.sin_addr));

c_fd=ret;

printf("begin:******************(default continue)\n");
ret=recv(c_fd,buff,1024,0);//recv filename
if(ret<0){
	printf("recv filename failed\n");
	return -1;
}
if(buff=="null"){
printf("supposed to over\n");
return -1;
break;
}
	
printf("receive filename :%s\n",buff);
FILE * fp;
FILE * fp1;
fp=fopen(buff,"rb");
memcpy(buff_1,buff,strlen(buff)+1);
int i=0,j=0,k=0;
char *name[32];
while(buff[i]){
if(buff[i]=='.'){j=j+1;}
	i++;
}
if(j>0){
name[0]=strtok(buff,".");
char etr[32];
for(i=0;i<j;i++){
strcpy(etr,strtok(NULL,"."));
name[i+1]=etr;
}

for(i=j-1;i>0;i--){
strcat(name[i-1],name[i]);
}
strcpy(buff,name[0]);
fp1=fopen(strcat(strcat(buff,"_1."),etr),"wb");}
if(j==0){

fp1=fopen(strcat(buff,"_1"),"wb");
}
if(fp==NULL){
	perror("open");
	return 0;
}

fseek(fp,0,SEEK_END);
int file_size=ftell(fp);
char *p=(char *)malloc(file_size);
fseek(fp,0,SEEK_SET);
ret=fread(p,1,file_size,fp);
if(ret<0){
	printf("fread failed.\n");
	return -1;
}
ret=fwrite(p,1,file_size,fp1);
if(ret<0){
	printf("fwrite failed.\n");
	return -1;
}
printf("copy one %s to %s\n",buff_1,buff);
fseek(fp,0,SEEK_SET);
char file_size_str[32];
sprintf(file_size_str,"%d",file_size);
printf("fiel_size_str:%s\n",file_size_str);
while(!send(c_fd,file_size_str,32,0));//send file_size
int exdata=file_size;
while(!feof(fp)&&exdata>0){
char fil[1024];
if(exdata>1024){
ret=fread(fil,1,1024,fp);
if(ret<0){
	perror("fread");
	return 0;}
send(c_fd,fil,1024,0);//send file_data
}

else{
ret=fread(fil,1,exdata,fp);
if(ret<0){
        perror("fread");
        return -1;
}
send(c_fd,fil,exdata,0);//send file_data
}
exdata=exdata-1024;
}
printf("file sent\nend:******************\n");
strcpy(buff,"null");
fclose(fp);
}
close(s_fd);
close(c_fd);
}

