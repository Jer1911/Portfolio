% Before you run this code, make sure that you are in the right directory.
%
% First, download the zip files containing code and data for this unit, from 
% the lectures web page (accessible from the course website).
% 
% Second, unzip the zip files.
%
% Third, modify the addpath and cd commands in the beginning of the code,
% to reflect the locations of code and data on your computer
%
% Now you can copy lines from this script file and paste them to Matlab's
% command window.

%%

% The addpath and cd lines are the only lines in the code that you may have
% to change, in order to make the rest of the code work. Adjust
% the paths to reflect the locations where you have stored the code 
% and data in your computer.

restoredefaultpath;
clear all;
close all;

addpath C:\Users\vangelis\Files\Academia\Teaching\TxState\CS4379C-Spr2019\Lectures\Code\00_common\00_detection
addpath C:\Users\vangelis\Files\Academia\Teaching\TxState\CS4379C-Spr2019\Lectures\Code\00_common\00_images
addpath C:\Users\vangelis\Files\Academia\Teaching\TxState\CS4379C-Spr2019\Lectures\Code\00_common\00_utilities
addpath C:\Users\vangelis\Files\Academia\Teaching\TxState\CS4379C-Spr2019\Lectures\Code\06_hough
cd C:\Users\vangelis\Files\Academia\Teaching\TxState\CS4379C-Spr2019\Lectures\Data\06_hough

%%

clear; close all;

i1 = zeros(300, 300);
i1 = draw_line(i1, [280, 1], [1, 280]);
figure(1); imshow(i1, []);

[h1, theta1, rho1] = hough(i1);
[rows1, cols1] = find(h1 == max(max(h1))); 
disp([rho1(rows1(1)), theta1(cols1(1))])
i2 = zeros(300, 300);
i2 = draw_line2(i2, rho1(rows1(1)), theta1(cols1(1)));
figure(2); imshow(i2, []);

%%

clear; close all;
input = read_gray('road1.bmp');
output = hough_demo(input, 2, 1);
figure(1); imshow(input, []);
figure(2); imshow(output, []);

%%

clear; close all;
input = read_gray('road2.bmp');
output = hough_demo(input, 2, 1);
figure(1); imshow(input, []);
figure(2); imshow(output, []);

%%

clear; close all;
input = read_gray('road3.bmp');
output = hough_demo(input, 2, 1);
figure(1); imshow(input, []);
figure(2); imshow(output, []);

%%

clear; close all;
input = read_gray('road4.jpg');
output = hough_demo(input, 2, 1);
figure(1); imshow(input, []);
figure(2); imshow(output, []);

%%

clear; close all;
input = read_gray('road5.jpg');
output = hough_demo(input, 2, 1);
figure(1); imshow(input, []);
figure(2); imshow(output, []);

%%

clear; close all;
input = read_gray('road6.jpg');
output = hough_demo(input, 2, 1);
figure(1); imshow(input, []);
figure(2); imshow(output, []);

%%

clear; close all;
input = read_gray('road7.jpg');
output = hough_demo(input, 2, 1);
figure(1); imshow(input, []);
figure(2); imshow(output, []);

%%

clear; close all;
input = read_gray('road9.jpg');
output = hough_demo(input, 2, 1);
figure(1); imshow(input, []);
figure(2); imshow(output, []);

%%

clear; close all;
input = read_gray('road8.jpg');
output = hough_demo(input, 2, 1);
output2 = hough_demo(input, 10, 2);
figure(1); imshow(input, []);
figure(2); imshow(output, []);
figure(3); imshow(output2, []);

%%
