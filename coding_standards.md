# Coding Standards

These are the coding standards I follow on this project.

* Yes to exceptions
* No to C-style casts ( "(int)1.5" )
* Use "#pragma once" rather than header guards
** (This is because this project is already Windows-only, and the pragma is prettier :)
* Follow Google style formatting, except that we indent 4 spaces, not 2.

## Comment Style

We will use Qt-style doxygen comments. Class, function, and member comments are as follows:

/*!
 * \brief A brief description.
 *
 * A more detailed description.
 */
class Foo;

We won't use structural commands except for a file, as in:

/*!
 * \file filename.extension
 *
 * A description of the file.
 * Author: the author
 */

(Is there any specific information we should include in the file comment?)
