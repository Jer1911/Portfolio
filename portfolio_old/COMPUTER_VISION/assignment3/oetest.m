img = 'frame0040.tif';
result1 = oriented_edges(img, 1.4, 4, 0, 15);
result2 = oriented_edges(img, 1.4, 4, 45, 15);
result3 = oriented_edges(img, 1.4, 4, 90, 15);
result4 = oriented_edges(img, 1.4, 4, 135, 15);

figure(1); imshow(result1);
figure(2); imshow(result2);
figure(3); imshow(result3);
figure(4); imshow(result4);
