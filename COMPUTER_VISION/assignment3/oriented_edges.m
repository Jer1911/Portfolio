
function result = oriented_edges(img,sigma,threshold,direction,tolerance)
orig = read_gray(img);
canny_edges = canny4(orig, sigma, 1.35, threshold, 2*threshold);
grad = gradient_orientations(orig,sigma);

angle = abs(mod(direction,180));
low = angle - tolerance;
high = angle + tolerance;

[row, col] = size(canny_edges);
result = zeros(row, col);
for c = 1 : col
    for r = 1 : row
        if canny_edges(r,c) ~= 0
            go = grad(r,c);
            if (go >= low) && (go <= high)
                result(r,c) = 255;
            end
        end
    end
end

end
