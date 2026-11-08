#include <compiler.h>
#include <kpmodule.h>

// Manually declare printk for minimal test
extern int printk(const char *fmt, ...);

KPM_NAME("test-kpm");
KPM_VERSION("1.0.0");
KPM_LICENSE("GPL v2");
KPM_AUTHOR("Gautam");
KPM_DESCRIPTION("Minimal KPM Test");

static long test_init(const char *args, const char *event, void *__user reserved) {
    printk("DevineKPM: HELLO WORLD! MINIMAL TEST SUCCESS\n");
    return 0;
}

static long test_exit(void *__user reserved) {
    printk("DevineKPM: MINIMAL TEST UNLOADED\n");
    return 0;
}

KPM_INIT(test_init);
KPM_EXIT(test_exit);
