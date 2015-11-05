#include "image_to_array.h"
#include <stdio.h>

ImageData image_to_array( const char* filename, bool threshold )
{
	ImageData ret;
	IplImage* image;

  image = cvLoadImage(filename, 1);   // Read the file

	// convert to gray
	IplImage* grey = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U, 1);
	cvCvtColor(image, grey, CV_BGR2GRAY);

	// threshold image

	if( threshold )
	{
	  IplImage* thresh = cvCreateImage(cvSize(image->width,image->height),IPL_DEPTH_8U, 1);
		cvThreshold( grey, thresh, 127, 255, 0 );
		grey = thresh;
	}
	ret.height = grey->height;
	ret.width = grey->width;

    if(! grey->imageData )                              // Check for invalid input
    {
        printf("Could not open or find the image\n" );
        exit(-1);
    }

	// allocate memory for image
	ret.data = (unsigned char**) malloc( sizeof(unsigned char*) * ret.height );
	for(int i = 0; i < ret.height; i++ )
	{
		ret.data[i] = (unsigned char*) malloc( sizeof(unsigned char) * ret.width );
	}

	// set image data
	for( int i = 0; i < ret.height; i++ )
	{
		for( int j = 0; j < ret.width; j++ )
		{
			ret.data[i][j] = ((unsigned char) (grey->imageData + grey->widthStep*i)[j]);
		}
	}

	return ret;
}

IplImage* array_to_image( ImageData data, const char* display_name )
{
	// initialize image
	IplImage* out_image = cvCreateImage(cvSize(data.width,data.height), IPL_DEPTH_8U, 0);

	// copy image data to array
	for( int i = 0; i < data.height; i++ )
	{
		for( int j = 0; j < data.width; j++ )
		{
			((unsigned char*)(out_image->imageData+out_image->widthStep*i))[j] = data.data[i][j];
		}
	}

	if( display_name != NULL )
	{

		// display image 
    	cvNamedWindow( display_name, CV_WINDOW_AUTOSIZE );// Create a window for display.
	    cvShowImage( display_name, out_image );                   // Show our image inside it.

	}
	return out_image;
}

//unsigned char* get_pixel( ImageData
