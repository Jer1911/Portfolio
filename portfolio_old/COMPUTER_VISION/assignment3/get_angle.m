function [low,high,angle] = get_angle(direction,tolerance)
angle = abs(mod(direction,180));

low = angle - tolerance;
high = angle + tolerance;



%low = mod(angle - tolerance,180);
%high = low + 2 * tolerance;

%{
if low > high
    tmp = low;
    low = high;
    high = tmp;
%}

angle
low
high

end
