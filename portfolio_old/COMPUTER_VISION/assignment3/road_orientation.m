function result = road_orientation(img)

orig = read_gray(img);

threshold = 4;
sigma = 1.4;

%{
rho = x*cos(theta) + y*sin(theta)
– rho: distance of line from origin.
– theta: direction PERPENDICULAR to line
%}
[gradient,thetas] = canny_jer(orig,sigma);

result = gradient;


end
