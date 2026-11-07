#include <compiler.h>
#include <kpmodule.h>
#include <linux/kmod.h>
#include <linux/kernel.h>

#define SCRIPT_PATH "/mnt/vendor/persist/ksu_bak/modules/run_all.sh"

KPM_NAME("devine-runner");
KPM_VERSION("1.0.0");
KPM_LICENSE("GPL v2");
KPM_AUTHOR("Gautam");
KPM_DESCRIPTION("Runs Devine script on boot");

static long devine_init(const char *args, const char *event, void *__user reserved) {
    char *argv[] = { "/system/bin/sh", SCRIPT_PATH, NULL };
    char *envp[] = { "HOME=/", "PATH=/sbin:/system/sbin:/system/bin:/system/xbin:/vendor/bin", NULL };
    int ret;

    pr_info("DevineKPM: Booting up! Triggering run_all.sh...\n");
    ret = call_usermodehelper(argv[0], argv, envp, UMH_NO_WAIT);
    
    if (ret < 0) {
        pr_err("DevineKPM: Failed to execute script, error: %d\n", ret);
    } else {
        pr_info("DevineKPM: Script triggered successfully!\n");
    }
    return 0;
}

static long devine_exit(void *__user reserved) {
    pr_info("DevineKPM: Unloaded.\n");
    return 0;
}

KPM_INIT(devine_init);
KPM_EXIT(devine_exit);
