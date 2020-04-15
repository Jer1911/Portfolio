function [gradient,thetas] = canny_jer(image, sigma)

b1 = blur_image(image, sigma);

dx = [-1 0 1; -2 0 2; -1 0 1]/8;
dy = dx';  % dy is the transpose of dx

% compute dx, dy, and gradient (edited to cast to doubles - JBE38)
dxb1 = double(imfilter(b1, dx, 'same', 'symmetric'));
dyb1 = double(imfilter(b1, dy, 'same', 'symmetric'));
gradient = (dxb1 .^2 + dyb1 .^2).^0.5;

% compute edge orientations, in values ranging from 0 to 180 degrees
thetas = gradient_orientations(dxb1, dyb1);

end


