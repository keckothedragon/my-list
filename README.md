# My List
This project is from about a year ago, and contains two separate implementations for generic lists: one in C, and one in C++.

Since I created this project a while ago, there is no commit history.

## MyList
This is my C implementation, and uses a void* to represent data and a chunk size to allow for any type. It supports standard list features, such as appending, indexing, and automatic reallocation.
### MyList_Types
While it is possible to just use the functions provided in MyList.h to achieve all functionality, I figured it would be more convenient if I set up a few core types to have their own "implementation", ex. IntList, DoubleList, CharList, etc. This way, you don't have to convert to/from void* when using the functions, and it can simply return/use the specified type itself.

## MyVector
This is my C++ implementation, and uses a template class so that there's much less of a hassle to use it. It also supports more functionality than the C implementation, such as iterators and some operator overloads. However, the core functionality is similar, except storing the data as a T* instead of void* since we are allowed to use templates.