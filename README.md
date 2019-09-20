# Vertical Scrolling Rhythm Game Library
I'm hoping this could be a universal vsrg library that other engines could extend from.

## Goal
Extensibility on a rich library that covers new and old formats

### Surface-level Convention Note
While this is easily expandable, this library heavily focuses on efficient memory management. There will be a lot of functions requiring `shared_ptr` usage instead of relying deep copying of objects.

I also use a base unit of millisecond for most classes, so if there's a need to convert into other units, you can access `TimedObject::UnitScale::` class namespace to get other conversions from seconds to hours

### Extensibility
You can view how you can extend from this repository by looking at my [Examples](examples.md)

## Main Features
Everything is documented in [Road Map](roadmap.md). I will list everything that will be implemented and possibly more over time.

### Dependents
- [**yaml_cpp**](https://github.com/jbeder/yaml-cpp) for YAML standard format exporting and importing
