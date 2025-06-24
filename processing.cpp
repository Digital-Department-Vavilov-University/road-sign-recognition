include "opencv2/highgui/highgui.hpp"
 
using namespace cv;
 
intdotX1 = 0;
intdotY1 = 0;
intdotX2 = 0;
intdotY2 = 0;
 
void CallBackFunc(intevent, intx, inty, intflags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
         dotX1 = x;
         dotY1 = y;
         printf("Left button - position (%d, %d)\n", x, y);
     }
     elseif  ( event == EVENT_RBUTTONDOWN )
     {
         dotX2 = x;
         dotY2 = y;
         printf("Right button - position (%d, %d)\n", x, y);
     }
}
 
int main()
{
    // Объявляем переменные и дирректории для сохранения файлов
    intgoodCount = 0;
    intbadCount = 0;
 
    chardir[] = "C:\\Users\\const\\Desktop\\openCV\\cascades\\AutoNet\\right\\";
    charfileName[512]; // Имя результирующего файла
 
for(inti = 0; i<500; i++)
{
    // Read image from file
    charInputName[512];
    sprintf(InputName, "%stemp\\%d.jpg",dir, i);
    printf("\nOpen image ... %s\n\n", InputName);
    IplImage* image = cvLoadImage(InputName,1);
 
    // Create a window
    namedWindow("My Window", 1);
 
    // Set the callback function for any mouse event
    setMouseCallback("My Window", CallBackFunc, NULL);
 
    IplImage* temp = 0;         // Временная переменная, в которой отображает-ся выделенная область для saveImage
    MattempMat;                // Временная переменная класса Mat
    IplImage* saveImage = 0;    // Переменная, в которой будет храниться изоб-ражения для сохранения
    charWait;                  // Переменная для сохранения результата работы функции cvWaitKey()
     while(1)
    {
        Wait = cvWaitKey(33);
        // Clone image on the temp and convert this to Mat
        temp = cvCloneImage(image);
        tempMat = cvarrToMat(temp);
 
        saveImage = cvCloneImage(image);
 
        // Если мы выделили область
        if(dotX1 != 0 && dotX2 != 0)
        {
            // Draw a rectangle
            Point dot1(dotX1, dotY1);
            Point dot2(dotX2, dotY2);
            rectangle( tempMat, dot1, dot2, Scalar( 255, 255, 0 ), +2, 8 );
 
            // Save the good image
            if(tolower(Wait) == 'g')
            {
                printf("\n\tYou press [ G ] ...\n");
                cvSetImageROI(saveImage, cvRect(dotX1, dotY1, abs(dotX2-dotX1), abs(dotY2-dotY1)));
                cvShowImage("ROI", saveImage);
                 printf("\nPress Enter, if you want save image, else press ESC ... \n\n");
                charsaveOrNot = cvWaitKey(0);  // Сохранять изображение или нет
                 // Enter   Соохранять
                if(saveOrNot == 13)
                {
                    // Cохраняем изображение в дирректорию
                    sprintf(fileName, "%sGood\\%d.jpg", dir, goodCount);
                    printf("\nSave image ... %s\n", fileName);
                    cvSaveImage(fileName, saveImage);
                     // Сохраняемтекст в dat-файл
                    sprintf(fileName, "%sGood.dat", dir);
                    printf("Write in ... %s\n\n", fileName);
                    FILE*out1;
                    out1 = fopen(fileName,"a");
                        fprintf(out1, "Good\\%d.jpg  1  0 0 %d %d\n", good-Count, abs(dotX2-dotX1), abs(dotY2-dotY1));
                    fclose(out1);
 
                    goodCount++;
                    cvDestroyWindow("ROI");
                }
                // ESC  несохранить
                elseif(saveOrNot == 27)
                {
                    cvDestroyWindow("ROI");
                }
            }
 
            // Save the bad image
            elseif(tolower(Wait) == 'b')
            {
                printf("\n\tYou press [ B ] ...\n");
                cvSetImageROI(saveImage, cvRect(dotX1, dotY1, abs(dotX2-dotX1), abs(dotY2-dotY1)));
                cvShowImage("ROI", saveImage);
 
                printf("\nPress Enter, if you want save image, else press ESC ... \n\n");
                charsaveOrNot = cvWaitKey(0);  // Сохранять изображение или нет
 
                // Enter   Соохранять
                if(saveOrNot == 13)
                {
                    // Cохраняем изображение в дирректорию
                    sprintf(fileName, "%sBad\\%d.jpg", dir, badCount);
                    printf("\nSave image ... %s\n", fileName);
                    cvSaveImage(fileName, saveImage);
 
                    // Сохраняемтекст в dat-файл
                    sprintf(fileName, "%sBad.dat", dir);
                    printf("Write in ... %s\n\n", fileName);
                    FILE*out2;
                    out2 = fopen(fileName,"a");
                        fprintf(out2, "Bad\\%d.jpg\n", badCount);
                    fclose(out2);
                     badCount++;
                    cvDestroyWindow("ROI");
                }
                // ESC  несохранить
                elseif(saveOrNot == 27)
                {
                    cvDestroyWindow("ROI");
                }
            }
        }
         cvShowImage( "My Window", temp );
 
        if(Wait == 27)    // ESC
        {
            // освобождаемресурсы
            cvReleaseImage(& image);
            cvReleaseImage(& temp);
            cvReleaseImage(&saveImage);
            // удаляем окно
            cvDestroyWindow("MyWindow");
             break;
        }
        // Нужно освобождать память на каждой итерации, чтобы не переполнялась память
        cvReleaseImage(& temp);
        cvReleaseImage(&saveImage);
    }
}
    return 0;
}