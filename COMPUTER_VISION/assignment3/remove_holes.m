function closed = remove_holes(img)

closed = imfill(padarray(img,size(img),'symmetric'),'holes');
closed = closed(size(img,1)+(1:size(img,1)),size(img,2)+(1:size(img,2)));

end

