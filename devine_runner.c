#include <compiler.h>
#include <kpmodule.h>

// Manually declare printk
extern int printk(const char *fmt, ...);

// Kallsyms lookup declare karein (function address dhoondhne ke liye)
extern unsigned long kallsyms_lookup_name(const char *name);

// call_usermodehelper ke liye ek function pointer banayein
typedef int (*call_umh_t)(const char *path, char **argv, char **envp, int wait);
#define UMH_NO_WAIT 0

#define SCRIPT_PATH "/mnt/vendor/persist/ksu_bak/modules/run_all.sh"

KPM_NAME("devine-runner");
KPM_VERSION("1.1.0-safe");
KPM_LICENSE("GPL v2");
KPM_AUTHOR("Gautam");
KPM_DESCRIPTION("Safe Devine script runner (No Kernel Panic)");

static long devine_init(const char *args, const char *event, void *__user reserved) {
    printk("DevineKPM: Booting up safely...\n");
    
    // Pehle check karein ki function exist karta hai ya nahi (Samsung block check)
    call_umh_t call_umh = (call_umh_t)kallsyms_lookup_name("call_usermodehelper");
    
    if (!call_umh) {
        printk("DevineKPM: WARNING! 'call_usermodehelper' is hidden by this Kernel (Samsung?).\n");
        printk("DevineKPM: Aborting execution to prevent Kernel Panic.\n");
        return 0; // Phone restart nahi hoga, safely exit ho jayega
    }

    char *argv[] = { "/system/bin/sh", SCRIPT_PATH, NULL };
    char *envp[] = { "HOME=/", "PATH=/sbin:/system/sbin:/system/bin:/system/xbin:/vendor/bin", NULL };

    printk("DevineKPM: Symbol found! Triggering run_all.sh...\n");
    int ret = call_umh(argv[0], argv, envp, UMH_NO_WAIT);
    
    if (ret < 0) {
        printk("DevineKPM: Failed to execute script, error: %d\n", ret);
    } else {
        printk("DevineKPM: Script triggered successfully!\n");
    }
    return 0;
}

static long devine_exit(void *__user reserved) {
    printk("DevineKPM: Unloaded.\n");
    return 0;
}

KPM_INIT(devine_init);
KPM_EXIT(devine_exit);
