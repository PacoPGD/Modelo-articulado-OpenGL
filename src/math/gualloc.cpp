#include "gualloc.h"
#include <cassert>
 
   
bool gu_free( void* ptr ,int __alignment )
{
    if( ((size_t)ptr & (__alignment-1)) != 0 )     return false;
    free( *((char**)ptr - 1) );
    return true;
}

bool gu_isaligned(void *ptr,int __alignment  )
{
  long int add=(long int)ptr;
  return (add%__alignment==0);
  
}

void* gu_alloc( size_t size  ,int __alignment )
{
    char *ptr, *ptr0 = (char*)malloc(
        (size_t)(size + __alignment*((size >= 4096) + 1) + sizeof(char*)));

    if( !ptr0 )
        return 0;

    // align the pointer
    ptr = (char*)gu_alignPtr(ptr0 + sizeof(char*) + 1, __alignment);
    *(char**)(ptr - sizeof(char*)) = ptr0;

    return ptr;
}

/**Returns the offset of a pointer from the boundaries indicated (2^n)
*/
uintptr_t gu_ptr_offset(void *x, uintptr_t n)
{
return ((uintptr_t)x) & (n-1);
}

void* gu_alignPtr( const void* ptr, int align )
{
    assert( (align & (align-1)) == 0 );
    return (void*)( ((size_t)ptr + align - 1) & ~(size_t)(align-1) );
}

 
