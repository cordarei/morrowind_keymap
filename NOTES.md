#TODO

 - DLL configuration
 - Exception safety
 - Other refactoring
 - Comment/code style

## DLL configuration

Do we really need DInputWrapper as a separate DLL? We like de-coupling, but
we have the same function exported from both DLLs with no real reason to
separate them.

## Exception Safety

Need to check/ensure exception safety in DInputWrapper.dll. We're not
using smart pointers there so it could cause a problem.

We could improve error checking everywhere, actually.

## Other refactoring

Along with enhancing/adding configuration etc, we may want to pull
out some stuff into shared headers, or maybe a library. Especially the
config stuff will be needed in the DLL and the config tool (if any).

## Comment/Code style

Really ought to decide on a code and comment style.
Comments are currently half-ass JavaDoc/Qt style.
