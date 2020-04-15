
function result = oriented_edges(img,sigma,threshold,direction,tolerance)
orig = read_gray(img);
%figure(1); imshow(orig, []);

canny_edges = canny4(orig, sigma, 1.35, threshold, 2*threshold);
figure(2); imshow(canny_edges);

% 7th attempt:-------------------------------------------------------------

grad_rc = gradient_orientations(canny_edges);
figure(3); imshow(grad_rc);

angle1 = abs(mod(direction,180));
low = abs(mod(angle1 - tolerance,180));
high = abs(mod(angle1 + tolerance,180));

[row, col] = size(canny_edges);
result = zeros(row, col);
for c = 1 : col
    for r = 1 : row
        if canny_edges(r,c) ~= 0 % if r,c is edge pixel
            go = grad_rc(r,c);
            
            thetas =  atan2(gradient_y, gradient_x);
            
            %go = gradient_orientations(r1,c1);
            
            if (go >= low) && (go <= high)
                result(r,c) = 255;
            end
        end
    end
end

figure(4); imshow(result);

% 6th attempt:-------------------------------------------------------------
%{
norms = gradient_norms(orig);
figure(3); imshow(norms);

result = canny_edges & norms;
figure(4); imshow(result);
%}

% 5th attempt:-------------------------------------------------------------
%{
dx = [-1 0 1; -2 0 2; -1 0 1] / 8;
dx = imrotate(dx, direction, 'bilinear', 'loose');
dy = dx';

gradient_x = imfilter(canny_edges, dx, 'same', 'symmetric');
gradient_y = imfilter(canny_edges, dy, 'same', 'symmetric');

thetas =  atan2(gradient_y, gradient_x);

result = thetas / pi * 180;
result(result < 0) = result(result < 0) + 180;
result(result > 180) = 180;
figure(4); imshow(result);
%}

% 4th attempt:-------------------------------------------------------------
%{
dx = [-1 0 1; -2 0 2; -1 0 1] / 8;
dy = dx';

dxb1 = imfilter(orig, dx, 'symmetric');
dyb1 = imfilter(orig, dy, 'symmetric');
normals = (dxb1 .^2 + dyb1 .^2).^0.5;
figure(3); imshow(normals);

result = canny_edges & normals;
figure(4); imshow(result);
%}

% 3rd attempt:-------------------------------------------------------------
%{
dx = [-1 0 1; -2 0 2; -1 0 1] / 8;
rot = imrotate(dx, direction, 'bilinear', 'loose');
angle_edges = abs(imfilter(canny_edges, rot, 'symmetric'));
figure(3); imshow(angle_edges);

result = canny_edges & angle_edges;
figure(4); imshow(result);
%}

% 1st attempt:-------------------------------------------------------------
%normals = gradient_norms(edges);
%figure(3); imshow(normals);

%orientation = gradient_orientations(normals, sigma);
%figure(4); imshow(orientation);

%result = edges & normals & orientation;
%figure(5); imshow(result);


% 2nd attempt:-------------------------------------------------------------
%orientation = gradient_orientations(edges);
%figure(6); imshow(orientation);

%{
[row, col] = size(edges);
result = [row, col];
for c = 1 : col
    for r = 1 : row
        if edges(r,c) == 255 && gradient_orientations(r,c) < % tolerence degrees from direction
            normal = gradient_orientations(r,c);
        end
    end
end
%}

end
