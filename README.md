*forked from [Rolias/PropertyHelper.h](https://gist.github.com/Rolias/48d453a0490d36090193)*

# Overview
These macros are intended to reduce the amount of boilerplate code the user has to write when using the Qt Frameworks's Q_PROPERTY feature. The idea was to provide something similar to C#'s auto property feature.

```cs
public double myValue {get;set;}
```

I was after the lack of clutter not the syntax. This file contains two macros.

### The First Macro
```c
AUTO_PROPERTY(TYPE, NAME)
```

It will create a standard

```c
Q_PROPERTY (TYPE, NAME READ NAME WRITE Name NOTIFY NAMEChanged) 
```

macro of the passed type and name. In addition, it will create a standard getter named _NAME_, setter named _Name_ and signal named _NAMEChanged_(_TYPE_ value) It will also create the member data variable. Note it does not use the more standard setName syntax, mostly because I didn't know how to do the capitalization trick. The member var is named with an `a_` prefix because it is intended to remind the user to **NOT** use the member variable name directly. The user should use the property name instead. If you don't like the `a_` prefix change the macro.

## The Second Macro
```c
READONLY_PROPERTY(TYPE, NAME)
```

will create a standard

```c
Q_PROPERTY( TYPE NAME READ NAME CONST)
```

It will create the getter and the member variable name. It also creates a **private** setter function. The function is just named NAME, i.e. it doesn't use a set prefix. In this macro, the member variable again uses `a_` but the user is expected to initialize this variable directly. All reads of the variable should be done through the property for consistency.

## Example Usages
```c
 AUTO_PROPERTY(QString, myProperty)
 READONLY_PROPERTY(double, myValueProp)
```

## Usage Notes
Use these macros in the `private:` section of your header only. They use both `public` and `private` keywords and leave the header in the private section. Putting these macros directly under the `Q_OBJECT` macro at the top of the class is acceptable. If for some reason you have to use these macros in the public section it is your responsibility to add the public: keyword after the macro.

#### Warning!
Note that these macros are only intended to be used as shown. The parameters are **NOT** intended to be expressions but simply the type and name. The parameters aren't parenthesized in the body of the macro and the entire macro is not parenthesized. Enjoy responsibly.

#### Note on Initializers
If you uses these macros at the top of your class then the member variables they create will be the first ones in your class. Therefore, to make tools like lint happy, you should add these variables to your initializer list in the order they are declared; before any variables that come after these macros. If you want to fully initialize variables in the order they are declared then even `AUTO_PROPERTY` created variables will need to be accessed directly. There is no harm in doing this. In general I was trying to adhere to the philosophy of the member variables being hidden and only the property being used.

```
The MIT License (MIT)

Copyright (c) 2014 Syncor Systems, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
