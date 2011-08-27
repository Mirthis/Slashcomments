<?php
/**
 * @file
 * A handler to provide proper displays for the comment score
 */
class views_handler_field_slashcomments_score extends views_handler_field_numeric {
  function render($values) {
    if($score = $values->slashcomments_contents_rating_score) {
      return $score;
    }
    else {
      return $values->comments_uid ? _slashcomments_get_default_score() : _slashcomments_get_default_score_anonymous();
    }
  }
}
