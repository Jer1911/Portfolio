function [top,bottom,left,right] = find_bounding_box(file_name1)
% Parse the input file name to get the before and after frames:
[a, b] = parse_frame_name(file_name1);
file_name0 = make_frame_name(a, b-1);
file_name2 = make_frame_name(a, b+1);

% Read the frames into grayscale using the professor's handy function:
frame0 = read_gray(file_name0);
frame1 = read_gray(file_name1);
frame2 = read_gray(file_name2);

% Calculate the motion:
diff1 = abs(frame0 - frame1);
diff2 = abs(frame2 - frame1);
motion = min(diff1, diff2);

% Make a thresholded; 2 seemed to work best for me:
threshold = 2;
thresholded = (motion > threshold);

% Make connected components:
[labels, number] = bwlabel(thresholded, 4);

% Count pixels and find the largest connected:
counters = zeros(1,number);
for i = 1:number
% first, find all pixels having that label.
component_image = (labels == i);
% second, sum up all white pixels in component_image
counters(i) = sum(component_image(:));
end
[area, id] = max(counters);
person = (labels == id);

% find coordinates of all non-zero pixels.
[rows, cols] = find(person);

% Assign return values:
top = min(rows);
bottom = max(rows);
left = min(cols);
right = max(cols);

% Grab a color image:
original_image = imread(file_name1, 'tif');
result_image = original_image; % make a copy (why?)

% Draw color image with rectangle:
yellow = [255 255 0];
rect = draw_rectangle(result_image, yellow, top, bottom, left, right);
imshow(rect, []);

end

