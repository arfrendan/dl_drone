//
// Created by shi on 24/11/2019.
//
#include "SocketMatTransmissionClient.h"
using namespace std;
using namespace cv;
SocketMatTransmissionClient::SocketMatTransmissionClient(void)
{
}

SocketMatTransmissionClient::~SocketMatTransmissionClient(void)
{
}


int SocketMatTransmissionClient::socketConnect(const char* IP, int PORT)
{
    struct sockaddr_in    servaddr;

    if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout<<"create socket error: "<<strerror(errno)<<"\n"<< endl;
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IP, &servaddr.sin_addr) <= 0)
    {
        cout<<"inet_pton error for " <<IP<<"\n"<<endl;
        return -1;
    }

    if (connect(sockClient, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        cout<<"connect error: "<< strerror(errno)<<"  errorno:"<<errno<<"\n"<<endl;
        return -1;
    }
    else
    {
        cout<< "connect success"<<endl;
    }
}


void SocketMatTransmissionClient::socketDisconnect(void)
{
    close(sockClient);
}

int SocketMatTransmissionClient::transmit(cv::Mat image)
{
    if (image.empty())
    {
        cout<<"empty image\n\n"<<endl;
        return -1;
    }

    if(image.cols != IMG_WIDTH || image.rows != IMG_HEIGHT || image.type() != CV_8UC3)
    {
        cout<<"the image must satisfy : cols =="<< IMG_WIDTH<<"  rows == "<<IMG_HEIGHT<<"type == CV_8UC3\n\n"<<endl;
        return -1;
    }


    int colByte = image.cols*image.channels() * sizeof(uchar);
    for (int i = 0; i<image.rows; i++)
    {
        char* data = (char*)image.ptr<uchar>(i);
        int sedNum = 0;
        char buf[BUFFER_SIZE] = { 0 };
        while (sedNum < colByte)
        {
            int sed = (BUFFER_SIZE < colByte - sedNum) ? BUFFER_SIZE: (colByte - sedNum);
            memcpy(buf, &data[sedNum], sed);
            int SendSize = send(sockClient, buf, sed, 0);
            if(SendSize<0){
                printf("send image error: %s(errno: %d)\n", strerror(errno), errno);
            }
            sedNum += SendSize;

        }
    }
    char recvBuf[50];
    int ns = recv(sockClient, recvBuf, 50, 0);
    recvBuf[ns] = '\0';
    printf("severRecv %s\n", recvBuf);

//    for(int k = 0; k < PACKAGE_NUM; k++)
//    {
//        int num1 = IMG_HEIGHT / PACKAGE_NUM * k;
//        for (int i = 0; i < IMG_HEIGHT / PACKAGE_NUM; i++)
//        {
//            int num2 = i * IMG_WIDTH * 3;
//            uchar* ucdata = image.ptr<uchar>(i + num1);
//            for (int j = 0; j < IMG_WIDTH * 3; j++)
//            {
//                data.buf[num2 + j] = ucdata[j];
//            }
//        }
//
//        if(k == PACKAGE_NUM - 1)
//            data.flag = 2;
//        else
//            data.flag = 1;
//
//        if (send(sockClient, (char *)(&data), sizeof(data), 0) < 0)
//        {
//            printf("send image error: %s(errno: %d)\n", strerror(errno), errno);
//            return -1;
//        }
//    }
}
