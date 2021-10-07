# FAQ

The FAQs are not in any particular order.

---
## Setting up

### <a name="version"></a> I have [software X] [version Y] installed on my machine. Will the installation still work?

The OIP only works with the versions listed in [setup instructions](./SetupHelp.md).
No guaranty is given for other versions.

Other tested versions (please help us extend this list if you succeed with not-yet listed versions):

- CMake: 3.18.2

### <a name="cmake_warnings></a> CMake shows a lot of red warnings in its log panel.

That is expected behaviour.
As long as it says *Configuring done* or *Generation done* you're good to go!

### I deviated from the default install folders for third party libraries. How to proceed?

You're on your own here.
There should be some CMake variables prepared, however this has not been thoroughly tested.

---
## Compilation

### Compiling IFC libraries takes a long time.

Welcome to the club!

### Error C2977: 'boost::mpl::list': too many template arguments

Compile **OpenInfraPlatform.Commands.UpdateBoostMPL** provided in the solution in folder `OpenInfraPlatform.Commands`.

### Warning C4127: conditional expression is constant

You can safely ignore it, if it comes from an auto-generated IFC library.

### Warning C4251: class '...' needs to have dll-interface to be used by clients of class '...'

You can safely ignore it, if it comes from an auto-generated IFC library.

### Warning C4506: no definition for inline function

You can safely ignore it, if it comes from an auto-generated IFC library.

---
## UI

### How do I navigate the viewport?

See [wiki](https://github.com/tumcms/Open-Infra-Platform/wiki/Camera-control).


