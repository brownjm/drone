#include "udpsocket.h"
#include <iostream>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

int main() {
    UDPSocket command{"192.168.10.1", 8889};
    command.send("command");
    command.recv();
    command.send("streamon");
    command.recv();

    //cv::VideoCapture cap{"udp://0.0.0.0:11111", cv::CAP_FFMPEG};
    cv::VideoCapture cap{"udp://0.0.0.0:11111", cv::CAP_ANY};
    if (!cap.isOpened()) {
        std::cerr << "Unable to open udp capture stream\n";
        return -1;
    }

    while (true) {
        cv::Mat frame;
        if (!cap.read(frame)) {
            std::cerr << "Read blank frame\n";
            continue;
        }
        cv::imshow("Tello", frame);
        if (cv::waitKey(1) == 27) { // ESC
            break;
        }
    }
}
