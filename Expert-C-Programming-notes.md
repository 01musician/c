# Notes from reading book "Expert C Programming: Deep C Secrets"

## Chapter 3: Unscrambling Declaration in C

There is the C philosophy that the declaration of an object should look like its use.

```C
const int * grape;
int const * grape; //both make the object that it points at read-only;
int * const grape; //make the pointer read-only
```
## Chapter 4

