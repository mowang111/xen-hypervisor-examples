#ifndef __HYPERCALL_X86_64_H__
#define __HYPERCALL_X86_64_H__

#include <xen.h>

#define __STR(x) #x
#define STR(x) __STR(x)

#define _hypercall3(type, name, a1, a2, a3)                     \
({                                                              \
        long __res, __ign1, __ign2, __ign3;                     \
        __asm__ volatile (                                              \
                "call hypercall_page + ("STR(__HYPERVISOR_##name)" * 32)"\
                : "=a" (__res), "=D" (__ign1), "=S" (__ign2),   \
                "=d" (__ign3)                                   \
                : "1" ((long)(a1)), "2" ((long)(a2)),           \
                "3" ((long)(a3))                                \
                : "memory" );                                   \
        (type)__res;                                            \
})

static inline int HYPERVISOR_console_io(int cmd, int count, char *str)
{
        return _hypercall3(int, console_io, cmd, count, str);
}

#endif
