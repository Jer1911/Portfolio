Name: Jeremy Ecker
TXState ID: A04839221 -- NetID: jbe38

PROJECT 2 README:

Task 1:
Function remove_holes(BINARY_IMAGE)
-takes a binary image as argument
-returns binary image with holes closed
-Initial attempts failed to remove border-connected holes in the zebra
 picture, so a better method was needed. Thanks to the padarray function, I
 was able to make a border around the image, thus ensuring that all holes
 would be filled, even ones connected to a border. I chose symmetric
 padding, then used imfill with holes argument. Finally, resized to remove
 the temporary border. In the end, I was able to make it work in only 2
 lines of code.

Task 2:
Script task2_solution.m
-Creates 3 figures, one of the soccer field, one of red players, and one of
 blue players.
-Assumes 'soccer_field4.jpg' is in the same directory.
-First, I extract the RGB colors from the image. For the field, I isolate
 green and remove holes, then isolate the largest connected component. For
 the players, I isolated red and blue, respectively. Then I used logical
 operators on the field and color and used the bwareaopen function. For red
 players, the pixel value 50 was chosen; for blue, 15. End result was 19
 lines of code (not counting comments).

Task 3:
Script task3_solution.m
-Creates 2 figures, one of the sky and one of the water.
-Assumes 'ocean2.jpg' is in the same directory.
-To show the sky, threshold, erosion, and largest connected component
 operations are used.
 For the water, I found it difficult to isolate, so a variety of techniques
 were employed.
 - First, I decided it would be easiest to isolate the trees and rocks and
   use their negations and sky negation, so whatever was left over would be
   the water.
 - trees: blur, threshold, remove holes, largest connected
 - rocks: To find the rocks, I needed a preliminary water to help me
   isolate them.
  - preliminary water: threshold, open, largest connected, remove holes
  Next was the tricky part since it proved difficult to isolate the rocks
  using normal morphological operations.
  So here is how it worked: canny edge detection, logical negation of trees
  sky and water. This resulted in some funky looking lines, but the lines
  were in the correct place to show the rocks. So, I dilated 4 times, then
  largest connected, remove holes, blur, then erode 5 times. The result was
  a pretty good approximation of just the rocks.
 - Finally the water:
   The water is not trees, not rocks, and not sky. Then, erode 3 times
   (this was needed because there was a pesky swath of water that was not
   connected to anything), then find largest connected.
-Ultimately, it is not exactly like the provided solution picture, but it
 is pretty close. I suspect I must have overlooked something simple, since
 the assignment claims that it is do-able with only 14 lines of code! (I
 would appreciate seeing the more efficient solution...). Mine was 29 lines
 of code without comments.
-IMPORTANT NOTE:
 task3_solution.m has several dependencies which are included in the .zip
 submission. It is not recommended to use other files in place of the
 provided ones, because I had to correct an error in canny4.m in which dxb1
 and dyb1 needed to be cast to doubles. Otherwise the function will not
 work.

  