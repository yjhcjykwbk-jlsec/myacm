#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

using namespace cv;
using namespace std;

// static void help()
// {
//     printf(
//             "\nDemonstrate the use of the HoG descriptor using\n"
//             "  HOGDescriptor::hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());\n"
//             "Usage:\n"
//             "./peopledetect (<image_filename> | <image_list>.txt)\n\n");
// }

int main(int argc, char** argv)
{
    Mat img;
    FILE* f = 0;
    char _filename[1024];
	//char *_filename="posListINRIA.txt";

    //if( argc == 1 )
    //{
    //    printf("Usage: peopledetect (<image_filename> | <image_list>.txt)\n");
    //    return 0;
    //}
    //img = imread(argv[1]);

	//img = imread("negListINRIA.txt");

    //if( img.data )
    //{
    //    strcpy(_filename, argv[1]);
    //}
    //else
    //{
    //    f = fopen(argv[1], "rt");
    //    if(!f)
    //    {
    //        fprintf( stderr, "ERROR: the specified file could not be loaded\n");
    //        return -1;
    //    }
    //}

	 f = fopen("posListINRIA.txt", "rt");

    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    namedWindow("people detector", 1);

    for(;;)
    {
        char* filename = _filename;
        if(f)
        {
            if(!fgets(filename, (int)sizeof(_filename)-2, f))	//ÿ�ζ�ȡһ�У���һ��ͼƬ��·��
			//destination,maxnumber,souce,���ض�ȡ���ַ���,�������л�EOF����
		    //����ܶ�ȡmaxnumber-1���ַ�����ΪĬ�ϻ���ϡ�\0����Ҫ����Ԥ��λ��
                break;
            //while(*filename && isspace(*filename))
            //  ++filename;
            if(filename[0] == '#')
                continue;
            int l = (int)strlen(filename);
            while(l > 0 && isspace(filename[l-1]))
                --l;
            filename[l] = '\0';
            img = imread(filename);	//ÿ��ѭ�������ȡһ��ͼƬ
        }
        printf("%s:\n", filename);
        if(!img.data)
            continue;

        fflush(stdout);//����ļ�����������д��ʽ���ļ�ʱ��������������д���ļ�
        vector<Rect> found, found_filtered;
        double t = (double)getTickCount();
        // run the detector with default parameters. to get a higher hit-rate
        // (and more false alarms, respectively), decrease the hitThreshold and
        // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
        hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);
		/*
		img				�C Source image. 
		found_locations �C objects boundaries(x,y,width,height).
		hit_threshold	�C Threshold for the distance between features and SVM classifying plane.
		win_stride		�C Window stride. It must be a multiple of block stride.
		padding			�C Mock parameter to keep the CPU interface compatibility. It must be (0,0).  ????
		scale0			�C Coefficient of the detection window increase.
		group_threshold	�C Coefficient to regulate the similarity threshold. When detected, some
		objects can be covered by many rectangles. 0 means not to perform grouping.  ԭ���ܼ��һ���ˣ�����Ϊ4��ʱ���Ȼû��
		*/
        t = (double)getTickCount() - t;
        printf("tdetection time = %gms\n", t*1000./cv::getTickFrequency());
        size_t i, j;
        for( i = 0; i < found.size(); i++ )//ȥ���ռ��о������������ϵ�����򣬱������
        {
            Rect r = found[i];
            for( j = 0; j < found.size(); j++ )
                if( j != i && (r & found[j]) == r)
                    break;
            if( j == found.size() )
                found_filtered.push_back(r);
        }
        for( i = 0; i < found_filtered.size(); i++ )
        {
            Rect r = found_filtered[i];
            // the HOG detector returns slightly larger rectangles than the real objects.
            // so we slightly shrink the rectangles to get a nicer output.
            r.x += cvRound(r.width*0.1);
            r.width = cvRound(r.width*0.8);
            r.y += cvRound(r.height*0.07);
            r.height = cvRound(r.height*0.8);
            rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 3);// tl:the top-left corner,br: the bottom-right corner
        }
        imshow("people detector", img);
        int c = waitKey(5000) & 255;
        if( c == 'q' || c == 'Q' || !f)
            break;
    }
    if(f)
        fclose(f);
    return 0;
}
