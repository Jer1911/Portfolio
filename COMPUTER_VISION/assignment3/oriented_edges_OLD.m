
function result = oriented_edges(img,sigma,threshold,direction,tolerance);
orig = read_gray(img);
%figure(1); imshow(orig, []);

edges = canny4(orig, sigma, 1.35, threshold, 2*threshold);
%figure(2); imshow(edges);

normals = gradient_norms(edges);
%figure(3); imshow(normals);

orientation = gradient_orientations(normals, sigma);
%figure(4); imshow(orientation);

result = edges & normals & orientation;
figure(5); imshow(result);

end
