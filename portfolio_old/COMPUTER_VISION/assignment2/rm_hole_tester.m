% Script to excercise remove_holes function.

img1 = imread('Data/person_with_holes.gif');
img2 = imread('Data/simple_with_holes.gif');
img3 = imread('Data/zebra_with_holes.gif');
img4 = imread('Data/ocean_with_holes.gif');

img1a = remove_holes(img1);
img2a = remove_holes(img2);
img3a = remove_holes(img3);
img4a = remove_holes(img4);

figure(1); imshow(img1a);
figure(2); imshow(img2a);
figure(3); imshow(img3a);
figure(4); imshow(img4a);

img5 = imbinarize(imread('test.png'));
img5a = remove_holes(img5);
figure(5); imshow(img5a);
