# ray-tracer
A CPU raytracer

Feature - Autostereogram
My program accepts an additional flag, "-sis." This enables autostereogram rendering, which translates .pov files into viewable 3D images. More information regarding autostereograms can be viewed here:
http://www.hidden-3d.com/how_to_view_stereogram.php
https://developer.nvidia.com/gpugems/GPUGems/gpugems_ch41.html
https://www.ime.usp.br/~otuyama/stereogram/basic/index.html
For debugging purposes, the "-dm" enables depthmap rendering, which translates .pov files into a 2D depth map.

![alt text](https://github.com/zackragozzino/ray-tracer/blob/master/Output_Images/mickey_SIS.png)
![alt text](https://github.com/zackragozzino/ray-tracer/blob/master/Output_Images/valentine_SIS.png)
![alt text](https://github.com/zackragozzino/ray-tracer/blob/master/Output_Images/saturn_SIS.png)

Optimization:
My major optimization came from reducing the number of times I calculate intersections.
I created a class called "HitObject" that holds a reference to the intersected object of a hit,
the hit position in world space, and the t value of the hit. Each Hit instance holds a reference
to a HitObject and functions update the values of the HitObject by calling the getObjectT() function.
This was particularly helpful when adding spatial data structures to my code as it meant I could
update hit information during tree traversal. Because of this, my spatial data structure code
ran significantly faster than before.




