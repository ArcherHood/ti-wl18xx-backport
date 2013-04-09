#include <linux/module.h>
#include "compat-2.6.34.h"

MODULE_AUTHOR("Luis R. Rodriguez");
MODULE_DESCRIPTION("Kernel backport module");
MODULE_LICENSE("GPL");

#ifndef BACKPORTED_KERNEL_NAME
#error "You need a BACKPORTED_KERNEL_NAME"
#endif

#ifndef BACKPORTED_KERNEL_VERSION
#error "You need a BACKPORTED_KERNEL_VERSION"
#endif

#ifndef BACKPORTS_VERSION
#error "You need a BACKPORTS_VERSION"
#endif

static char *backported_kernel_name = BACKPORTED_KERNEL_NAME;

module_param(backported_kernel_name, charp, 0400);
MODULE_PARM_DESC(backported_kernel_name,
		 "The kernel tree name that was used for this backport (" BACKPORTED_KERNEL_NAME ")");

#ifdef BACKPORTS_GIT_TRACKED 
static char *backports_tracker_id = BACKPORTS_GIT_TRACKED;
module_param(backports_tracker_id, charp, 0400);
MODULE_PARM_DESC(backports_tracker_id,
		 "The version of the tree containing this backport (" BACKPORTS_GIT_TRACKED ")");
#else
static char *backported_kernel_version = BACKPORTED_KERNEL_VERSION;
static char *backports_version = BACKPORTS_VERSION;

module_param(backported_kernel_version, charp, 0400);
MODULE_PARM_DESC(backported_kernel_version,
		 "The kernel version that was used for this backport (" BACKPORTED_KERNEL_VERSION ")");

module_param(backports_version, charp, 0400);
MODULE_PARM_DESC(backports_version,
		 "The git version of the backports tree used to generate this backport (" BACKPORTS_VERSION ")");

#endif

void backport_dependency_symbol(void)
{
}
EXPORT_SYMBOL_GPL(backport_dependency_symbol);


static int __init backport_init(void)
{
	backport_pm_qos_power_init();
	backport_system_workqueue_create();
	backport_init_mmc_pm_flags();

	printk(KERN_INFO "Loading modules backported from " BACKPORTED_KERNEL_NAME
#ifndef BACKPORTS_GIT_TRACKED
		" version " BACKPORTED_KERNEL_VERSION
#endif
		"\n");
#ifdef BACKPORTS_GIT_TRACKED
	printk(KERN_INFO BACKPORTS_GIT_TRACKED "\n");
#else
	printk(KERN_INFO "Backport generated by backports.git " BACKPORTS_VERSION "\n");
#endif

        return 0;
}
module_init(backport_init);

static void __exit backport_exit(void)
{
	backport_pm_qos_power_deinit();
	backport_system_workqueue_destroy();

        return;
}
module_exit(backport_exit);

