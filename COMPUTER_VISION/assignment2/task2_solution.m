filename = 'soccer_field4.jpg';
color = double(imread(filename));
r = color(:,:, 1);
g = color(:,:, 2);
b = color(:,:, 3);

% show the field:
green = ((g - r > 10) & (g - b > 0));
no_holes = remove_holes(green);
field = largest_connected(no_holes);
figure(1); imshow(field);

% show the red players:
red = ((r - g > 10) & (r - b > 10));
red_players = field & ~red;
red_players = ~red_players & field;
red_players = bwareaopen(red_players,50);
figure(2); imshow(red_players);

% show the blue players:
blue = ((b - g > 10) & (b - r > 10));
blue_players = field & ~blue;
blue_players = ~blue_players & field;
blue_players = bwareaopen(blue_players,15);
figure(3); imshow(blue_players);

