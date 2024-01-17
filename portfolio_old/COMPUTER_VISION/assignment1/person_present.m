function present = person_present(file_name1)

[a, b] = parse_frame_name(file_name1);
file_name0 = make_frame_name(a, b-1);
file_name2 = make_frame_name(a, b+1);

frame0 = read_gray(file_name0);
frame1 = read_gray(file_name1);
frame2 = read_gray(file_name2);

diff1 = abs(frame0 - frame1);
diff2 = abs(frame2 - frame1);

motion = min(diff1, diff2);

threshold = 2;
thresholded = (motion > threshold);

[labels, number] = bwlabel(thresholded, 4);

counters = zeros(1,number);
for i = 1:number
component_image = (labels == i);
counters(i) = sum(component_image(:));
end
[area, id] = max(counters);

% Detect a person if the area is greater than 1k pixels:
if (area > 1000)
    present = 1;
else
    present = 0;
end

end

