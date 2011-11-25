diff --git a/slashcomments.module b/slashcomments.module
index 124350b..621bd06 100755
--- a/slashcomments.module
+++ b/slashcomments.module
@@ -198,7 +198,8 @@ function slashcomments_theme() {
  * Implementation of hook_perm().
  */
 function slashcomments_perm() {
-  return array('moderate comments', 'administer slashcomments', 'bypass moderation restriction');
+  return array('moderate comments', 'administer slashcomments', 
+               'bypass moderation restriction');
 }
 
 /**
@@ -229,10 +230,12 @@ function slashcomments_moderate_access() {
  */
 function slashcomments_user_can_moderate($uid, $cid) {
   /* skip controls for the super user */
-  if (user_access('bypass moderation restriction') || $uid == 1) {
+  if (user_access('administer slashcomments') && $uid == 1) {
     return array('result' => 1, 'message' => '');
   }
 
+  $bypass = user_access('bypass moderation restriction');
+
   // keeps the status for checks which are comment independent
   // to avoid executing them multiple times during comment rendering
   static $result = array('result' => 0, 'message' => '', 'step' => 0);
@@ -252,20 +255,21 @@ function slashcomments_user_can_moderate($uid, $cid) {
     }
 
     // check if user is still a new bie
-    if (strtotime("-" . _slashcomments_get_limit_newbie() . " day") < $user->created) {
+    if (!$bypass && strtotime("-" . _slashcomments_get_limit_newbie() . " day") < $user->created) {
       $result['message'] = _slashcomments_get_moderation_message(-5, $uid);
       return $result;
     }
 
     // check if user has the needed karma
     if (_slashcomments_karma_enabled()
-      && slashcomments_get_user_karma($uid) < _slashcomments_get_limit_karma()) {
+      && !$bypass && slashcomments_get_user_karma($uid) < _slashcomments_get_limit_karma()) {
         $result['message'] = _slashcomments_get_moderation_message(-2, $uid);
         return $result;
       }
 
     // check if the user has enough moderation points
-    if (_slashcomments_get_mod_per_day() != SLASHCOMMENTS_INFINITE_MOD_POINTS && !_slashcomments_user_has_mod_points($uid)) {
+    if (!$bypass && _slashcomments_get_mod_per_day() != SLASHCOMMENTS_INFINITE_MOD_POINTS 
+                 && !_slashcomments_user_has_mod_points($uid)) {
       $result['message'] = _slashcomments_get_moderation_message(-3, $uid);
       return $result;
     }
@@ -287,7 +291,7 @@ function slashcomments_user_can_moderate($uid, $cid) {
   }
 
   // check if user is participating in the discussion
-  return slashcomments_user_participating_in_discussion($uid, $cid);
+  return slashcomments_user_participating_in_discussion($uid, $cid, $bypass);
 }
 
 
@@ -308,7 +312,7 @@ function slashcomments_user_can_moderate($uid, $cid) {
  *  - result: 1 if user can moderate, 0 if user can't moderate
  *  - message: when result is 0 the reason why the user can't moderate
  */
-function slashcomments_user_participating_in_discussion($uid, $cid) {
+function slashcomments_user_participating_in_discussion($uid, $cid, $bypass = FALSE) {
   // keeps this variable to avoid executing unecessary checks during
   // multiple comments rendering
   static $participating = -1;
@@ -319,7 +323,7 @@ function slashcomments_user_participating_in_discussion($uid, $cid) {
   }
 
   // When the option is set check if the user has already commented the node
-  if (_slashcomments_get_limit_takepart()) {
+  if (!$bypass && _slashcomments_get_limit_takepart()) {
     $sql = "SELECT count(*) cnt FROM {comments} c WHERE uid = %d AND nid
       = (SELECT t.nid FROM {comments} t WHERE t.cid = %d)";
 
