#include <opencv2/opencv.hpp>
#include "SocketMatTransmissionClient.h"

int main() {
    using namespace std;
    using namespace cv;

    SocketMatTransmissionClient socketMat;
    if (socketMat.socketConnect("127.0.0.1", 7999) < 0)
    {
        return 0;
    }
    VideoCapture cap("/home/shi/Downloads/1.mp4");
    Mat image;
    while (1)
    {
        cap >> image;
        if (image.empty()){
            cout<< "empty" <<endl;
            return 0;
        }

        resize(image,image,Size(640,480));
        cout<<"sent"<<endl;
        socketMat.transmit(image);
        waitKey(1);
    }

    socketMat.socketDisconnect();
    return 0;
}
