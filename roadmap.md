# Roadmap

This defines where the project is at and what is coming

## Basic Structure

This is the **minimum barebone structure** for any VSRG.
```
- Timed Objects
    - Hit Objects
        - Normal Note
        - Long Note
    - Event Objects
        - Timing Point
        - Scroll Point
- Wrapper Objects
    - Timed Object Wrapper
        - Hit Object Wrapper
        - Event Object Wrapper
    - VSRG Map
    - VSRG Settings
```
## Test Units

Test Units currently are quite messy, I'm planning to make a test unit for each repo if we do happen to extend.

Test Units should ideally test all functions and intended behavior but I'm currently speeding through most implementations for me to go back and verify it 100%.

## Game Specific Structure

Game specific structures will mainly just extend off of `vsrg` whereby it'll have their own Classes that can extend off of `HitObject` or `EventObjects` via inheritance.

The main different between `HitObject` and `EventObject` is that `HitObject` **will always have a column**.

### Game Specific Implementations

I will be working on implementing parsing for the more **popular** VSRGs with a stable format in `vsrg` or `vsrg_game`.

Functions that extend off of `VsrgMap` will be available as the following format:
```
VsrgMap::loadO2Jam(std::string file_path);
VsrgMap::saveStepMania(std::string file_path);
```

## Extended Functions

Mainly all of the extended functions that aren't vital to a basic library.

I am considering to move this extended library to another repository. Likely named `vsrg_extend`

It will feature a lot of algorithms that can make data manipulation easier. I'm hoping to do everything in `C++` so that integration isn't a pain in the rear.

