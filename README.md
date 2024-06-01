# ShapeScape

ShapeScape allows you to create images based on text configuration provided via
input file. The configuration supports various geometric objects, such as lines,
circles, polygons and others. Example configuration files can be found in the
`/examples` directory. Supported image formats are: **PNG**, **BMP**, and **PPM**.

## Building the app

### Prerequisities

You need to have [make](https://www.gnu.org/software/make/) installed on your
computer, as well as [libpng](http://www.libpng.org/pub/png/libpng.html). After
installing libpng, configure the `LDFLAGS` variable in `Makefile` accordingly.

### Building

To compile the app run `make bin`, to generate documentation run `make doc`,
to remove all generated files run `make rm`.

## Running the app

The basic usage is:

```sh
$ shapescape <option(s)> SOURCE
```

for example:

```sh
$ shapescape -r Example1.png ./examples/example_1.txt
```
