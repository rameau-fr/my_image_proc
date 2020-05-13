#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <message_filters/subscriber.h>
#include <image_transport/subscriber_filter.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//GLOBALS
string TopicImage; 
image_transport::Publisher pub;
float scale;


void ReceiveImage(const sensor_msgs::Image::ConstPtr& msg)
{
	ROS_INFO("Image Received");

    // Receiving the image
	cv_bridge::CvImageConstPtr cv_ptr2 = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	Mat image = cv_ptr2->image;

	// Resizethe image
	Mat Image_resize;
	resize(image, Image_resize, Size(image.cols*scale, image.rows*scale));
	cout << image.size() << endl;
	cout << Image_resize.size() << endl;
	// Publish the resized image
    sensor_msgs::ImagePtr msgRes = cv_bridge::CvImage(std_msgs::Header(), "bgr8", Image_resize).toImageMsg();
    msgRes->header.stamp = msg->header.stamp;
    pub.publish(msgRes);
	/*namedWindow("ResizeIm", WINDOW_NORMAL); 
	imshow( "ResizeIm", Image_resize );
	cv::waitKey(1);*/
}
	
int main(int argc, char **argv)
{

	ros::init(argc, argv, "image_resize");
	ros::NodeHandle n("~");

	// Read the parameters
    n.getParam("in", TopicImage);
    string TopicOut;
    n.getParam("out", TopicOut);
    if (n.getParam("scale", scale)) {}
    else {scale = 1;}
	cout << TopicImage << endl;
	cout << TopicOut << endl;
	cout << scale << endl;

    // Run the code
	image_transport::ImageTransport it(n);
	image_transport::TransportHints hints("raw", ros::TransportHints());
	image_transport::Subscriber sub = it.subscribe(TopicImage, 1, ReceiveImage);

	//Advertise the resized image
	pub = it.advertise(TopicOut, 10);
	
  	ros::spin();

  return 0;

}
