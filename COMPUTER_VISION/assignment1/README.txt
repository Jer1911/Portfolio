Name: Jeremy Ecker
TxState ID: A04839221 (netID: jbe38)

Task 2 Solution:
Reproduce exactly the code from Task 1, up until
the point where 'area' is determined from max(counters). If the area is
too small, then there isn't a person. I determined 1k to be an appropriate
value. Since we know the person is moving linearly, we only need to look at
this area. If the person was moving towards / away from the camera, a
better solution would be required.
All tests showed an accurate 1 or 0, dependant on the 1k value. On edge
cases, sometimes the value was less than 1k even though part of the
person was showing, but the specification says this is okay.

Task 3 Solution:
Use the professor's handy function 'parse_frame_name' to extract the
numbers from the image files. Subtract to find the number of frames. Next,
do as it says in the instructions and call 'find_bounding_box' twice to
get two sets of data. Since we know that the person is moving to the left,
we only need to check the difference of 'left', in this case. Armed with
this information, it is a matter of applying the formula:
distance = rate * time (d=rt -> r=d/t).
The results seemed to be accurate. Not having any data to compare it to,
this is a guess.

