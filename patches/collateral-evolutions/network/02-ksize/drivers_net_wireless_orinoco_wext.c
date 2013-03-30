--- a/drivers/net/wireless/orinoco/wext.c
+++ b/drivers/net/wireless/orinoco/wext.c
@@ -31,8 +31,22 @@
 			   enum orinoco_alg alg, const u8 *key, int key_len,
 			   const u8 *seq, int seq_len)
 {
+#if LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,28)
+	int len;
+	if (!unlikely(ZERO_OR_NULL_PTR(priv->keys[index].key))) {
+		len = priv->keys[index].key_len;
+		memset(priv->keys[index].key, 0, len);
+		kfree(priv->keys[index].key);
+	}
+	if (!unlikely(ZERO_OR_NULL_PTR(priv->keys[index].seq))) {
+		len = priv->keys[index].seq_len;
+		memset(priv->keys[index].seq, 0, len);
+		kfree(priv->keys[index].seq);
+	}
+#else
 	kzfree(priv->keys[index].key);
 	kzfree(priv->keys[index].seq);
+#endif
 
 	if (key_len) {
 		priv->keys[index].key = kzalloc(key_len, GFP_ATOMIC);