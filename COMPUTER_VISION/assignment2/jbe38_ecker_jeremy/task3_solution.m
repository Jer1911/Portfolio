filename = 'ocean2.jpg';
orig = imread(filename);
%figure(1); imshow(orig);

nh = [0,1,0; 1,1,1; 0,1,0];

% show the sky:
sky = (orig > 187);
sky = imerode(sky,nh);
sky = largest_connected(sky);
figure(2); imshow(sky);

% find the trees:
trees = blur_image(orig,1);
trees = (trees < 95);
trees = remove_holes(trees);
trees = largest_connected(trees);
%figure(3); imshow(trees);

% find preliminary water:
water = (orig > 125) & (orig < 150);
water = imopen(water,nh);
water = largest_connected(water);
water = remove_holes(water);
%figure(4); imshow(water);

% find the rocks:
rocks = canny(orig,0.5) & ~trees & ~sky & ~water;
for i = 1:4
    rocks = imdilate(rocks,nh);
end
rocks = blur_image(remove_holes(largest_connected(rocks)),1);
for i = 1:5
    rocks = imerode(rocks,nh);
end
%figure(5); imshow(rocks);

% show the final water:
water = ~trees & ~rocks & ~sky;
for i = 1:3
    water = imerode(water,nh);
end
water = largest_connected(water);
figure(6); imshow(water);



