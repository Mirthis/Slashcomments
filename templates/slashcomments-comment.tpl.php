<?php

/**
 * @file
 * Default theme implementation for comments.
 *
 * Available variables:
 * - $author: Comment author. Can be link or plain text.
 * - $content: Body of the post.
 * - $date: Date and time of posting.
 * - $links: Various operational links.
 * - $new: New comment marker.
 * - $picture: Authors picture.
 * - $signature: Authors signature.
 * - $status: Comment status. Possible values are:
 *   comment-unpublished, comment-published or comment-review.
 * - $submitted: By line with date and time.
 * - $title: Linked title.
 *
 * These two variables are provided for context.
 * - $comment: Full comment object.
 * - $node: Node object the comments are attached to.
 *
 */
?>

<?php 
  if (!$comment->name) {
    $comment->name = t('Anonymous');
  }
?>

<div class="comment <?php print $toggle_area ?>" id="comment-<?php print $comment->cid; ?>">
  <div class=" <?php print $toggle_label ?>">
       <span class="scomments_info"><?php print $date . " | " . $comment_link . ' ' . $page_link; ?></span>

      <?php if ($new != '') : ?>
       <span class="new"><?php print $new; ?></span>
      <?php endif; ?>
      <b><?php print $comment->subject ?></b>
      <?php print $slashcomments_rating ?> 
   </div>
  
  <div class="toggle_content <?php if (arg(0) != 'comment'): print $collapsed; endif; ?>">
    <div class="author">
    <?php if ($picture) {
    print $picture;
    } ?>
    <?php print $author ?>
    </div>  

    <div class="comment-content">
     <?php print $content ?>
        <?php print $slashcomments_form ?>
        <?php // print $slashcomments_Status ?> 
      <div class="clear clear-block"></div>     
      <div class="meta">
        <div class="links"><?php print $links; ?></div>
      </div>
      <?php if ($signature): ?><div class="user-signature"><?php print $signature ?></div><?php endif; ?>
    </div>
    
  </div>
</div>
