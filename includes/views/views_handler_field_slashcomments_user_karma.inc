<?php
/**
 * @file
 * A handler to provide proper displays for the comment score
 */
class views_handler_field_slashcomments_user_karma extends views_handler_field_numeric {
  function render($values) {
    if(($karma = $values->slashcomments_users_karma_karma) !== null) {
      return $karma;
    }
    else {
      return _slashcomments_get_default_karma();
    }
  }
}
