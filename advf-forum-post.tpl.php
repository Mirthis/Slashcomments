<?php

/**
 * @file
 *
 * Theme implementation: Template for each forum post whether node or comment.
 *
 * All variables available in node.tpl.php and comment.tpl.php for your theme
 * are available here. In addition, Advanced Forum makes available the following
 * variables:
 *
 * - $top_post: TRUE if we are formatting the main post (ie, not a comment)
 * - $reply_link: Text link / button to reply to topic.
 * - %total_posts: Number of posts in topic (not counting first post).
 * - $new_posts: Number of new posts in topic, and link to first new.
 * - $links_array: Unformatted array of links.
 * - $account: User object of the post author.
 * - $name: User name of post author.
 * - $author_pane: Entire contents of advf-author-pane.tpl.php.

 */
?>

<?php
 

  $threshold = _slashcomments_get_display_setting('threshold', $node);
  $threshold = $threshold ? $threshold : 0;

  if($top_post) {
      $collapsed = '';
      $toggle_label = '';
      $toggle_area = '';
  }
  else {
     if (!$comment->name) {
        $comment->name = t('Anonymous');
      }

      $collapsed = ($comment->score >= $threshold) ? '' : 'collapsed' ;
      $toggle_label = ($comment->score >= $threshold) ? 'non_toggle_label' : 'toggle_label' ;
      $toggle_label .= ' '. $comment->own;
      $toggle_area = ($comment->score >= $threshold) ? 'non_toggle_area' : 'toggle_area' ;
      $toggle_area .= ' ' . $comment->own;
  }
?>

<?php if ($top_post): ?>

  <?php print $topic_header ?>

  <?php $classes .= $node_classes; ?>
  <div id="node-<?php print $node->nid; ?>" class="top-post forum-post <?php print $classes; ?> clear-block">

<?php else: ?>
  <?php $classes .= $comment_classes; ?>
  <div id="comment-<?php print $comment->cid; ?>" class="forum-post <?php print $classes; ?> clear-block <?php print $toggle_area ?>">
<?php endif; ?>

  <div class="post-info clear-block <?php print $toggle_label ?>">
    <div class="posted-on">
      <?php print $date ?>
      <span class="sdot_rating"><b><?php print $comment->rating ?></b></span>
      <?php if (!$top_post && !empty($comment->new)): ?>
        <a id="new"><span class="new">(<?php print $new ?>)</span></a>
      <?php endif; ?>
    </div>

    <?php if (!$top_post): ?>
      <span class="post-num"><?php print $comment_link . ' ' . $page_link; ?></span>
    <?php endif; ?>
  </div>
  <div class="<?php if (arg(0) != 'comment'): print $collapsed; endif; ?>">
  <div class="forum-post-wrapper">

    <div class="forum-post-panel-sub">
      <?php print $author_pane; ?>
    </div>

    <div class="forum-post-panel-main clear-block">
      <?php if ($title && !$top_post): ?>
        <div class="post-title">
          <?php print $title ?>
        </div>
      <?php endif; ?>

      <div class="content">
        <?php print $content ?>
      </div>

      <?php if ($signature): ?>
        <div class="author-signature">
          <?php print $signature ?>
        </div>
      <?php endif; ?>
    </div>
  </div>

  <div class="forum-post-footer clear-block">
    <div class="forum-jump-links">
      <a href="#top" title="Jump to top of page"><?php print t("Top"); ?></a>
    </div>

    <?php if (!empty($links)): ?>
      <div class="forum-post-links">
        <?php print $links ?>
      </div>
    <?php endif; ?>
  </div>
  </div>
</div>