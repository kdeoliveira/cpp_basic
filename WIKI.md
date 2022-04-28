# C++

Object-oeriented programming language
Data is hidden through encapsulation
Namespace to avoid name collision
No garbage collector, memory allocation

## Basics

### r/l-values
- l-value: 
Modifiable object that persists after operation
- r-value:
Non modifiable and temporary value used in an expressions 
Note that on prefix/postfix r-value becomes l-valued. 
  - postfix: executes and stores immediately; reference old value 
  - prefix: executes and stores immediately; reference new modified value
### Signature
Defines input and output of function
### Overload
Methods of same name and return value but different parameters (arity and/or type)
- Operator overload
Redefinition of default operators
### Override
Subclass redefines superclass method
### Polymorphism
Ability of an object to take different forms/type at runtime (through pointers)
- Static Polymorphism:
It takes place at compile-time where types are assigned to objects statically (templates, overloading).
- Virtual Functions
Enforces type checking done at runtime
- Pure Virtual
Virtual function with no implementation: ``virtual void function() = 0;``
### Ducktyping
Perform type checking at runtime (method overloading)
### Abstraction
Ability of exposing data while hidding its defition
### Friend
Allows a class or function to access private, protected and public members of another class where it is defined
### Inline
Compiler uses as a hint to place a copy of the code (definition) to each point where function is referenced.  
Eliminates call overhead but increases object code size
### Static
Static members have space allocated in memory for the lifetime of the running process. Hence, only one copy of that member is present in memory.
### Constructor & Destructor
Automatically called when an object is created.  
Whereas, when an object is out of scope the destructor is called
- class() = default:
Compiler will implicitly define a consstructor for this class
- class() = delete:
Undefined constructor type. Compiler will fail if invoked
- class() {} : explicit:
Ideal in polymorphism which prevents wrong auto-conversion made by compiler
- Member initialization list:
Initialization of data members before calling constructor's body (ideally for constant members).
### Shallow Copy
Faster, stores the memory address reference of an object to another.  
Changes made in one affects others
### Deep Copy
Slower, performs complete copy of an object to a new memory address.  
Data independence

## Advanced

### RAII
Resource Acquisition is Initialization idiom which binds the lifetime of a resource to the same lifetime of an object. Hence construction and destruction of a resource is directly attached to the constructor and destructor of a class.

Note that class shuold only manage one resource only (Sngle Responsibility Principle).
### Copying
- copy constructor
`class a(b)`
`A(const A& _x)`
- copy assignment constructor
`a = b`
`A& operator=(const A& _x)`
Such constructors should be explicitly defined if the class manages or acquires a resource (pointers, object, etc).

### Noncopyable resources
Resources that should not be moved or copied: mutexes, file handles, sempahores. In such cases applies *Rule of zero* where no special constructor/operator is defined.

### Rule of three
If you need to explicitly declare either the destructor, copy constructor or copy assignment operator yourself, you probably need to explicitly declare all three of them.

### Rule of five (C++11)
If rule of three applies, then declare Move constructor and Move asignment operator.
- move constructor
`A& operator=(A&& x)`
- move assignment operator
`A(A&& _x)`

Note that move allows a resource owned by a r-value to be moved into a l-value without copying
### Copy and swap idiom
It uses swappable definition which makes of an unqualified call on a non-member `swap(t, u)` function. It swaps the value of t and u.

Such idioms provides the swap function used in copy/move assignment implementation that checks for self-assignmnent and provides exception safety (on exception, state is rolled back to safe state).

Note that on copy assignments, the arguments should be passed by value for proper copying.
### Argument-dependent lookup
It uses ADL to do an unqualified call to any overloaded definition name (eg. std::swap, or other user-defined function in this namespace). 
Use of friend function for user-defined swap since it is placed outside the class scope but inside the same namespace, while allowing access to class' private data members.

```
#include <utility>
using std::swap;
swap(u, t);
```

It will perform ADL on both std::swap and user-defined swap and call the appropriate one at compile-time. The compiler performs verification over all unqualified names by looking up the namespaces of each parameters object of the function.

### Variadic
- Function template:
They can be implemented recursively by providing (1) base case with one template as a fallback and (2) recursive case calls itself and base case.
- Class template:
It provides (1) the base case which only provides the type definition and (2) with actual implementation can call itself.


## Algorithm

### Iterators
The iterators can either iterator forwards and backward. It represents a pointer used in STL containers pointing to specific elements in a sequenced type