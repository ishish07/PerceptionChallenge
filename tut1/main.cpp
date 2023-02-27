#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

/*
 * This method processes the given image so that it is easy to find contours and approximate polygon shapes later
 */
cv::Mat preprocess(cv::Mat img) {
    cv::Mat imgGray, imgCanny, imgDil, imgThreshLow, imgThreshHigh, output; // declaring all Mat objects
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2HSV); // converting to HSV colorspace
    cv::inRange(imgGray, cv::Scalar(0,135,135), cv::Scalar(15,255,255), imgThreshLow); // making image for low range of HSV red
    cv::inRange(imgGray, cv::Scalar(159,135,135), cv::Scalar(179,255,255), imgThreshHigh); // making image for high range of HSV red
    cv::addWeighted(imgThreshHigh, 0.5, imgThreshLow, 0.5, 0, output, -1); // combining the two images created above
    cv::Canny(output, imgCanny, 25, 75); // detecting edges of our image
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3)); 
    cv::dilate(imgCanny, imgDil, kernel); // making the edges easier to see
    return imgDil;
}

/*
 * This method draws the cones on a blank image and finds their center points
 */
void getContours(cv::Mat imgDil, cv::Mat img) {
    std::vector<std::vector<cv::Point>> contours; // creating vector to store contour points
    std::vector<cv::Vec4i> hierarchy; 
    cv::findContours(imgDil, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE); // finding the contours of dilated image
    cv::Mat image(img.rows, img.cols, CV_8UC1, cv::Scalar(0, 0, 0)); // creating a blank image to work with later
    std::vector<std::vector<cv::Point>> conpoly(contours.size()); // creating vector to store approximate polygonal shapes
    for (int i = 0; i < contours.size(); i++) {
        cv::approxPolyDP(contours[i], conpoly[i], 10,true); // finding approximate polygon outlines
        if (conpoly[i].size() == 3 || conpoly[i].size() == 4) { // limiting the polygons to trianges/squares to get cones
            cv::drawContours(image, conpoly, i, cv::Scalar(255,255,255), 2); // drawing the triangles/squares on a blank image
        }
    }
    cv::Mat labels, stats, centroids;
    connectedComponentsWithStats(image, labels, stats, centroids); // storing all center points of different cones into centroids 
    // drawing lines on img according to the given image "original.png"
    cv::line(img, centroids.at<cv::Point2d>(cv::Point(3, 0)), centroids.at<cv::Point2d>(cv::Point(15, 0)), cv::Scalar(255,0,0), 5);
    cv::line(img, centroids.at<cv::Point2d>(cv::Point(4, 0)), centroids.at<cv::Point2d>(cv::Point(16, 0)), cv::Scalar(255,0,0), 5);
}

int main(int argc, char** argv) {

    std::string path = argv[1]; // second argument is the path to the image
    cv::Mat img = cv::imread(path); // stores the image in the Mat variable called img
    cv::Mat img2 = cv::imread(path); // creates a copy of the original image
    cv::Mat imgDil = preprocess(img); // preprocesses the given image to get it ready to find contours
    getContours(imgDil, img); // gets the contours on the processed image
    cv::imshow("image", img); // shows the image with lines drawn on it
    cv::imshow("original", img2); // shows the original image without lines 
    cv::imwrite("images/answer.png", img); // creates a file for the updated image
    cv::waitKey(0); // ensures the images are shown until the program terminates
    return 0;
}