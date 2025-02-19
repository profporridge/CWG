#ifndef PLATFORM_WINDOWS_LIBKERN_OSATOMIC__H
#define PLATFORM_WINDOWS_LIBKERN_OSATOMIC__H
#define OS_SPINLOCK_INIT    0
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
#define FORCE_INLINE __attribute__((always_inline)) inline
#elif _MSC_VER
#define FORCE_INLINE __forceinline
#endif

#include <Windows.h>
#include <intrin.h>
#include "../stdbool.h"

typedef volatile LONG OSSpinLock;

FORCE_INLINE bool OSSpinLockTry(OSSpinLock* lock)
{
	return InterlockedCompareExchange(lock, ~0, 0) == 0;
}

FORCE_INLINE void OSSpinLockLock(OSSpinLock* lock)
{
	while(!OSSpinLockTry(lock))
	{
		Yield();
	}
}

FORCE_INLINE void OSSpinLockUnlock(OSSpinLock* lock)
{
	MemoryBarrier();
	*lock = 0;
}

#undef FORCE_INLINE

#ifdef __cplusplus
}
#endif

#endif
