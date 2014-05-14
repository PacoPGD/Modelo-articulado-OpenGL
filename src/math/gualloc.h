/*******************
* Routines for aligned allocation
**********************/
#ifndef _GU_ALLOC_H_
#define _GU_ALLOC_H_
#include <cstdlib>
#include <stdint.h>

using namespace std;
 
/**Allocates a memory block with the specified alignment
*/
void* gu_alloc( size_t size,int __alignment=16  );
/**Indicates if a pointer is aligned
*/
bool gu_isaligned(void *ptr,int __alignment=16  );
/**Frees an aligned memory block allocted with gu_alloc
*/
bool gu_free( void* ptr ,int __alignment=16); 


/**Returns the offset of a pointer from the boundaries indicated (2^n)
*/
uintptr_t gu_ptr_offset(void *x, uintptr_t n);
void* gu_alignPtr( const void* ptr, int align  );
 
#endif
