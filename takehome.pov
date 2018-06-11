// Cornell Box
// Adapted from original
// Author: Ryan Schmitt
// Reworked by: Ian Dunn

camera {
  location  <0, 5, 15.5>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 5, 0>
}

light_source {< 0.0, 3.0,  0.0> color rgb <0.72, 0.72, 0.48>}

box {<-2, -5, -4.5>, <2, 5, 4.5>
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.8 reflection 0.8}
  rotate <0, -45, 0>
  translate <-7, 5, -5>
}

box {<-2, -5, -4.5>, <2, 5, 4.5>
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.2 diffuse 0.8 reflection 0.8}
  rotate <0, 45, 0>
  translate <7, 5, -5>
}


// Blue
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <0.4, 0.6, 1.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
  scale <4.5, 4.5, 0.6>
  translate <-6.5, 2, -4>
}

// Orange
sphere { <0, 0, 0>, 1.0
  pigment { color rgb <1.0, 0.65, 0.0> }
  finish {ambient 0.2 diffuse 0.6 specular 0.7 roughness 0.02 ior 1.6 reflection 0.6}
  scale <4.5, 4.5, 0.6>
  translate <6.5, 2, -4>
}
triangle {
  <-.001,1, 0 >,
  <-.001, -.3,3 >,
  <1,-.3, 0 >
  pigment {color rgb <0.65, 0.4, 0.4>}
  finish {ambient 0.3 diffuse 0.4}
}

triangle {
  <0,1, 0 >,
  <-1, -.3,0 >,
  <0,-.3, 3 >
  pigment {color rgb <0.65, 0.4, 0.4>}
  finish {ambient 0.3 diffuse 0.4}
}

triangle {
  <-1, -.3,0 >,
  <0,-1.3, 0 >,
  <0,-.3, 3 >
  pigment {color rgb <0.65, 0.4, 0.4>}
  finish {ambient 0.3 diffuse 0.4}
}

triangle {
  <0,-.3, 2 >,
  <0,-1.3, 0 >,
  <1, -.3,0 >
  pigment {color rgb <0.65, 0.4, 0.4>}
  finish {ambient 0.3 diffuse 0.4}
}



triangle {
  <-.001,1, 0 >,
  <-.001, -.3,3 >,
  <1,-.3, 0 >
  pigment {color rgb <0.65, 0.4, 0.4>}
  finish {ambient 0.3 diffuse 0.4}
  translate <0, 8, 0>
}

triangle {
  <0,1, 0 >,
  <-1, -.3,0 >,
  <0,-.3, 3 >
  pigment {color rgb <0.65, 0.4, 0.4>}
  finish {ambient 0.3 diffuse 0.4}
    translate <0, 8, 0>
}

triangle {
  <-1, -.3,0 >,
  <0,-1.3, 0 >,
  <0,-.3, 3 >
  pigment {color rgb <0.65, 0.4, 0.4>}
  finish {ambient 0.3 diffuse 0.4}
  translate <0, 8, 0>
}

triangle {
  <0,-.3, 2 >,
  <0,-1.3, 0 >,
  <1, -.3,0 >
  pigment {color rgb <0.65, 0.4, 0.4>}
  finish {ambient 0.3 diffuse 0.4}
    translate <0, 8, 0>
}


// THE ROOM

// floor @ y=0
triangle { <-5,0,5>, <5,0,-5>, <-5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-5,0,5>, <5,0,5>, <5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}

// right wall
triangle { <5,0,5>, <5,10,5>, <5,0,-5>
   pigment { color rgb <1,1,0> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <5,10,5>, <5,10,-5>, <5,0,-5>
   pigment { color rgb <1,1,0> }
   finish { ambient 0 diffuse 0.5 }
}

// left wall
triangle { <-5,0,5>, <-5,0,-5>, <-5,10,-5>
   pigment { color rgb <1,0,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-5,10,5>, <-5,0,5>, <-5,10,-5>
   pigment { color rgb <1,0,1> }
   finish { ambient 0 diffuse 0.5 }
}

// back wall
triangle { <5,10,-5>, <-5,10,-5>, <5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <5,0,-5>, <-5,10,-5>, <-5,0,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}

// ceiling @ y=10, w/ a 1x1 hole in the middle
//big left part
triangle { <-5,10,5>, <-5,10,-5>, <-1,10,5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-1,10,5>, <-5,10,-5>, <-1,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
//big right part
triangle { <5,10,5>, <1,10,5>, <1,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <5,10,5>, <1,10,-5>, <5,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
//little front part
triangle { <-1,10,5>, <1,10,1>, <1,10,5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-1,10,5>, <-1,10,1>, <1,10,1>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
//little back part
triangle { <-1,10,-1>, <1,10,-5>, <1,10,-1>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}
triangle { <-1,10,-1>, <-1,10,-5>, <1,10,-5>
   pigment { color rgb <1,1,1> }
   finish { ambient 0 diffuse 0.5 }
}



