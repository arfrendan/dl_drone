//
// Created by shi on 24/11/2019.
//

#ifndef TEST_SOCKETMATTRANSMISSIONCLIENT_H
#define TEST_SOCKETMATTRANSMISSIONCLIENT_H
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace cv;


const int IMG_WIDTH = 640;
const int IMG_HEIGHT = 480;
const int PACKAGE_NUM =2;
const int BUFFER_SIZE = IMG_WIDTH*IMG_HEIGHT*3/PACKAGE_NUM;

struct sentbuf
{
    char buf[BUFFER_SIZE];
    int flag;
};

class SocketMatTransmissionClient
{
public:
    SocketMatTransmissionClient(void);
    ~SocketMatTransmissionClient(void);

private:
    int sockClient;
    struct sentbuf data;

public:

    int socketConnect(const char* IP, int PORT);

    int transmit(cv::Mat image);

    void socketDisconnect(void);
};
#endif //TEST_SOCKETMATTRANSMISSIONCLIENT_H
