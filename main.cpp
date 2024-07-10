#include "detect_green_light.h"
#include "MvCameraControl.h"
#include <stdio.h>
#include <string.h>
#include "unistd.h"
#include <stdlib.h>

cv::Mat ConvertBayerRG8ToBGR(cv::Mat bayerImage)
{
    cv::Mat bgrImage;
    cv::cvtColor(bayerImage, bgrImage, cv::COLOR_BayerBG2BGR);
    return bgrImage;
}

cv::Mat CaptureVideoFrame(void* handle)
{
    MV_FRAME_OUT stImageInfo = {0};
    int nRet = MV_CC_GetImageBuffer(handle, &stImageInfo, 1000);
    if (nRet == MV_OK)
    {
        int nWidth = stImageInfo.stFrameInfo.nWidth;
        int nHeight = stImageInfo.stFrameInfo.nHeight;

        // ����һ����ͨ��ͼ��BAYER RG8��
        cv::Mat bayerImage(nHeight, nWidth, CV_8UC1, stImageInfo.pBufAddr);

        // �� BAYER RG8 ͼ��ת��Ϊ BGR ͼ��
        cv::Mat bgrImage = ConvertBayerRG8ToBGR(bayerImage);

        nRet = MV_CC_FreeImageBuffer(handle, &stImageInfo);
        if (nRet != MV_OK)
        {
            printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
        }
        return bgrImage;
    }
    else
    {
        printf("Get Image fail! nRet [0x%x]\n", nRet);
        return cv::Mat();
    }
}

//int main(int argc, char** argv) {
int main() {
//	VideoCapture cap;
//       cap.open(0);

//	if (!cap.isOpened()) {
//		cerr << "Error" << endl;
//		return -1;
//	}
	Mat frame;
    int nRet = MV_OK;
        void* handle = NULL;
        MV_CC_DEVICE_INFO_LIST stDeviceList;
        memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

        // ö���豸
        nRet = MV_CC_EnumDevices(MV_USB_DEVICE, &stDeviceList);
        if (nRet != MV_OK)
        {
            printf("Enum Devices failed! nRet [0x%x]\n", nRet);
            return -1;
        }

        if (stDeviceList.nDeviceNum < 1)
        {
            printf("No devices found!\n");
            return -1;
        }

        // �������
        nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[0]);
        if (nRet != MV_OK)
        {
            printf("Create Handle failed! nRet [0x%x]\n", nRet);
            return -1;
        }

        // ���豸
        nRet = MV_CC_OpenDevice(handle);
        if (nRet != MV_OK)
        {
            printf("Open Device failed! nRet [0x%x]\n", nRet);
            MV_CC_DestroyHandle(handle);
            return -1;
        }

        // �������ظ�ʽΪ BAYER RG8
        nRet = MV_CC_SetEnumValue(handle, "PixelFormat", PixelType_Gvsp_BayerRG8);
        if (nRet != MV_OK)
        {
            printf("Set Pixel Format failed! nRet [0x%x]\n", nRet);
            MV_CC_DestroyHandle(handle);
            return -1;
        }

        // ��ʼȡ��
            nRet = MV_CC_StartGrabbing(handle);
            if (nRet != MV_OK)
            {
                printf("Start Grabbing failed! nRet [0x%x]\n", nRet);
                MV_CC_DestroyHandle(handle);
                return -1;
            }

        namedWindow("Processed", WINDOW_NORMAL);

        while (true)
        {
            cv::Mat frame = CaptureVideoFrame(handle);
            if (frame.empty())
                break;
            //������ʮ����
            line(frame, Point(frame.size().width/2, 0), Point(frame.size().width/2, frame.size().height), Scalar(0, 0, 255));
            line(frame, Point(0, frame.size().height/2), Point(frame.size().width, frame.size().height/2), Scalar(0, 0, 255));
            detect_green_light(frame);
            imshow("Processed", frame);
            if (waitKey(30) == 27) { // 27 ��Esc����ASCII��
                break;
            }
          }
        // ֹͣȡ��
           nRet = MV_CC_StopGrabbing(handle);
           if (nRet != MV_OK)
           {
               printf("Stop Grabbing failed! nRet [0x%x]\n", nRet);
           }

           // �ر��豸
           nRet = MV_CC_CloseDevice(handle);
           if (nRet != MV_OK)
           {
               printf("Close Device failed! nRet [0x%x]\n", nRet);
           }

           // ���پ��
           MV_CC_DestroyHandle(handle);

           // �ͷŴ�����Դ
           cv::destroyAllWindows();

           return 0;
       }
