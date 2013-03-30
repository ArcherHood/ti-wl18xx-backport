--- a/net/wireless/nl80211.c
+++ b/net/wireless/nl80211.c
@@ -6740,7 +6740,9 @@
 	if (!net_eq(wiphy_net(&rdev->wiphy), net))
 		err = cfg80211_switch_netns(rdev, net);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
 	put_net(net);
+#endif
 	return err;
 }
 