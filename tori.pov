

camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.5, 0,  0>
  look_at   <0, 0, 0>
}

light_source {<10, 10, 3> color rgb <1.0, 1.0, 1.0>}


// Floor
plane {<0, 1, 0>, -4
  pigment {color rgb <0.6, 0.3, 0.6>}
  finish {ambient 0.4 diffuse 1.0}
}

// Background
plane {<0, 0, 1>, -100
  pigment {color rgb <0.8, 0.6, 0.4>}
  finish {ambient 0.2 diffuse 0.4}
}

box {<-6, -6, -6>, <6, 6, 6>
pigment {color rgbf <0.0, 0.0, 1.0, 0.8>}
  finish {ambient 0.2 diffuse 0.8 reflection 0.6 refraction 1.0 ior 1.333}
  translate <-20, -3, -12>
}

box {<-4, -4, -4>, <4, 4, 4>
pigment {color rgbf <0.0, 1.0, 0.0, 0.8>}
  finish {ambient 0.2 diffuse 0.8 reflection 0.6 refraction 1.0 ior 1.333}
  translate <-4, -3, -7>
}

box {<-2, -2, -2>, <2, 2, 2>
pigment {color rgbf <1.0, 1.0, 0.0, 0.8>}
  finish {ambient 0.2 diffuse 0.8 reflection 0.6 refraction 1.0 ior 1.333}
  translate <3, -3, -3>
}

box {<-1, -1, -1>, <1, 1, 1>
pigment {color rgbf <1.0, 0.0, 0.0, 0.8>}
  finish {ambient 0.2 diffuse 0.8 reflection 0.6 refraction 1.0 ior 1.333}
  translate <7, -3, 1>
}