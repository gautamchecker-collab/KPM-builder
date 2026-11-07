#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kmod.h>
#include <linux/init.h>

#define SCRIPT_PATH "/mnt/vendor/persist/ksu_bak/modules/run_all.sh"

static int __init devine_runner_init(void)
{
    char *argv[] = { "/system/bin/sh", SCRIPT_PATH, NULL };
    char *envp[] = { "HOME=/", "PATH=/sbin:/system/sbin:/system/bin:/system/xbin:/vendor/bin", NULL };
    int ret;
    pr_info("DevineKPM: Triggering run_all.sh...\n");
    ret = call_usermodehelper(argv[0], argv, envp, UMH_NO_WAIT);
    if (ret < 0) pr_err("DevineKPM: Failed, error: %d\n", ret);
    return 0;
}
static void __exit devine_runner_exit(void) { pr_info("DevineKPM: Unloaded.\n"); }
module_init(devine_runner_init);
module_exit(devine_runner_exit);
MODULE_LICENSE("GPL");
