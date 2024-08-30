#include <stdint.h>
#include <xen.h>

#if defined (__i686__)
#include "hypercall-x86_32.h"
#elif defined (__x86_64__)
#include "hypercall-x86_64.h"
#else
#error "Unsupported architecture"
#endif

/* Some static space for the stack */
char stack[8192];

void start_kernel(start_info_t *start_info)
{
    int ret; // 用于存储 hypercall 的返回值

    while (1)
    {
        // 调用 hypercall 并检查返回值
        ret = HYPERVISOR_console_io(CONSOLEIO_write, 12, "Hello world\n");

        // 检查返回值，如果返回非零值表示出现错误
        if (ret != 0)
        {
            break; // 退出循环，停止执行
        }

        // 简单的延时，避免占用过多 CPU 资源
        for (volatile int i = 0; i < 10000000; i++);
    }
}
