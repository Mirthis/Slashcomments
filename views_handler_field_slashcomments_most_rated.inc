<?php
// $Id$
/**
 * @file
 * A handler to provide proper displays for user badges.
 *
 * @author Heine Deelstra (Heine), http://drupal.org/user/17943
 * @author Richard Skinner (Likeless), http://drupal.org/user/310635
 *
 * @ingroup views_field_handlers
 */

  //Get the additional fields we need

class views_handler_field_slashcomments_most_rated extends views_handler_field {

  function render($values) {
    return slashcomments_rating2description($values->slashcomments_ratings_most_rated);
  }
}
