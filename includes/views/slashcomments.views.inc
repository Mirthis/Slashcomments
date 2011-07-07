<?php
// $Id$

/**
 * @file
 * This defines views hooks for the slashcomments module.
 * It will be loaded automatically as needed by the Views module.
 */


/**
 * Implementation of hook_views_handlers().
 */
function slashcomments_views_handlers() {
  return array(
    'handlers' => array(
      'views_handler_field_slashcomments_most_rated' => array(
        'parent' => 'views_handler_field',
        'path' => drupal_get_path('module', 'slashcomments') . '/includes/views',
        'file' => 'views_handler_field_slashcomments_most_rated.inc'
      ),
    ),
  );
}


/**
 * Implementation of hook_views_data().
 */
function slashcomments_views_data() {

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['slashcomments_ratings']['table']['group'] = t('Slashcomments');

  // How to join this table to the comments table
  $data['slashcomments_ratings']['table']['join']['comments'] = array(
    'left_field' => 'cid',
    'field' => 'cid',
    'type' => 'INNER'
  );

  // How to join this table to the node table
  $data['slashcomments_ratings']['table']['join']['node'] = array(
    'left_table' => 'comments',
    'left_field' => 'cid',
    'field' => 'cid',
    'type' => 'INNER'
  );

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['slashcomments_karma']['table']['group'] = t('Slashcomments');

  // How to join this table to the comments table
  $data['slashcomments_karma']['table']['join']['comments'] = array(
    'left_field' => 'uid',
    'field' => 'uid'
  );

  // How to join this table to the node table
  $data['slashcomments_karma']['table']['join']['node'] = array(
    'left_field' => 'uid',
    'field' => 'uid'
  );

   // How to join this table to the node table
  $data['slashcomments_karma']['table']['join']['users'] = array(
    'left_field' => 'uid',
    'field' => 'uid'
  );

  // Definition for score field
  $data['slashcomments_ratings']['score'] = array(
    'title' => t('Score'),
    'help' => t('Comment score'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      //'handler' =>  'views_handler_field_slashcomments_rating',
      'click sortable' => TRUE,
      //'default' => 1,
    ),
    // Information for accepting a rating as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Comment score'),
      'numeric' => TRUE,
    ),
    //Info for filtering by rating
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on rating
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Definition for score_karma field
  $data['slashcomments_ratings']['score_karma'] = array(
    'title' => t('Comment score with Karma'),
    'help' => t('Comment score with karma modifier applied'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      //'handler' =>  'views_handler_field_slashcomments_rating',
      'click sortable' => TRUE,
      //'default' => 1,
    ),
    // Information for accepting a rating as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Comment score with karma'),
      'numeric' => TRUE,
    ),
    //Info for filtering by rating
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on rating
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );


 // Definition for karma field
  $data['slashcomments_ratings']['karma'] = array(
    'title' => t('Comment User Karma'),
    'help' => t('User karma when the comment was posted'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      //'handler' =>  'views_handler_field_slashcomments_rating',
      'click sortable' => TRUE,
      //'default' => 1,
    ),
    // Information for accepting a rating as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Comment User Karma'),
      'numeric' => TRUE,
    ),
    //Info for filtering by rating
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on rating
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Definition for score_karma field
  $data['slashcomments_ratings']['nums_rating'] = array(
    'title' => t('Number of ratings'),
    'help' => t('Number of time the comment has been moderated'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      //'handler' =>  'views_handler_field_slashcomments_rating',
      'click sortable' => TRUE,
      //'default' => 1,
    ),
    // Information for accepting a rating as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Numbers of rating'),
      'numeric' => TRUE,
    ),
    //Info for filtering by rating
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on rating
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Definition for most_rated field
  $data['slashcomments_ratings']['most_rated'] = array(
    'title' => t('Rating'),
    'help' => t('Comment Rating'),
    'field' => array(
      //'handler' => 'views_handler_field_numeric',
      'handler' =>  'views_handler_field_slashcomments_most_rated',
      'click sortable' => TRUE,
    ),
    // Information for accepting a rating as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => t('Comment Rating'),
      'numeric' => TRUE,
    ),
    //Info for filtering by rating
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    // Information for sorting on rating
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

   // Definition for karma field
  $data['slashcomments_karma']['karma'] = array(
    'title' => 'Karma',
    'help' => 'User karma',
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE
    ),
    // Information for accepting a rating as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'User karmae',
      'numeric' => TRUE,
    ),
    //Info for filtering by rating
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on rating
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;

}
