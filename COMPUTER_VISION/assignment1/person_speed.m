function speed = person_speed(file1,file2)

[sequence_name1, frame1] = parse_frame_name(file1);
[sequence_name2, frame2] = parse_frame_name(file2);

[top1,bottom1,left1,right1] = find_bounding_box(file1);
close all;
[top2,bottom2,left2,right2] = find_bounding_box(file2);
close all;

time = frame2 - frame1;
distance = left1 - left2;
speed = (distance / time);

end

