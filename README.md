# rectangle_language
Programming Languages course final project - winter 2020-21

Rectangle Language was the final project for the Programming Language course at IASBS in winter 2020-21. It gets an input file containing information about a work area and various rectangles, all colored with greyscale colors, then generates a jpeg output.

syntax
------
Work area and rectangles should be defined under the `#init` section. All properties must have values.  A rectangle's coordinates can be changed under the `#move` section. comments start with `//`.
```
// comment
#init
workarea = {height, width, color}
rectangle = {top, left, height, width, color, name}
rectangle = {top, left, height, width, color, name}
.
.
.
rectangle = {top, left, height, width, color, name}
#move
name.property = new value
//comment
name.property = new value
.
.
.
name.property = new value
```

semantics
---------
#### Properties:
| property | acceptable value | is mutable |
| -------- |:----------------:| ----------:|
| top | integer | yes |
| left | integer | yes |
| height | positive integer | yes |
| width | positive integer | yes |
| color | 0-255 (R = G = B) | no |
| name | string | no |


#### Coordinates
The origin of the coordinate system is at the top left corner. `top` axis goes downward and `left` axis goes rightward.
| position | top | left |
| -------- |:---:| ----:|
| top left | 0 | 0 |
| top right | 0 | max |
| bottom left | max | 0 |
| bottom right | max | max |

output
------
Rectangle Language uses [toojpeg](https://github.com/stbrumme/toojpeg) library for generating jpeg files.
