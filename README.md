# PerceptionChallenge



<div style="display:inline-block">
<img src="tut1/images/original.png" height="700" width="500">
<img src="tut1/images/answer.png" height="700" width="500">
</div>

Methodology: This program first tries to find cones through color detection. After getting everything within a specified color range into a new image, it finds the edges of the objects in the image and dilates them. Next, the program searches for contours on the updated image and also finds approximate polygonal shapes for the objects. Afterwards, the polygons with 3 or 4 sides are drawn on a new image. Next, we find the center point of each of these polygons and put them in an array. Finally, we draw 2 lines from the starting cones point to the ending cones point based on the array we just created.

What did I try: Initially, I was opposed to using color detection for identifying the cones. My thought process was that what makes cones unique is their shape and their height, not their color necessarily. Perhaps there are other items in the image that have the same color but are not cones. However, not using color detection at all made it very difficult to isolate the cones. Even after using approxPolyDP(), and filtering for polygons with 3 or 4 sides, I still did not have an image with just cones in it. As a result, I decided to switch my approach to using color detection first. One thing I was unable to do was find a way for the program to understand which cones to draw lines through. I had to hard code which points to do this through, but in the future I would like to create an algorithm to calculate which points should be drawn through. Many times, the center points do not have the same or similar x/y values. 

Libraries Used: imgproc and highgui
I used the imgproc libraries for preprocessing the image and find/drawing contours on the image. I used the highgui library for showing the image to the user and writing it to a file. Most of the work was done using the imgproc library. However, the highgui library is what allowed me to test how my program was changing the image
