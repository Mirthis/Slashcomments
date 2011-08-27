<?php
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
      'views_handler_field_slashcomments_user_karma' => array(
        'parent' => 'views_handler_field_numeric',
        'path' => drupal_get_path('module','slashcomments') . '/includes/views',
        'file' => 'views_handler_field_slashcomments_user_karma.inc'
      )
    ),
  );
}


/**
 * Implementation of hook_views_data().
 */
function slashcomments_views_data() {

  $data['slashcomments_contents_rating']['table']['group'] = t('Slashcomments');

  $data['slashcomments_contents_rating']['table']['join']['comments'] = array(
    'left_field' => 'cid',
    'field' => 'content_id',
    'type' => 'INNER',
  );

  $data['slashcomments_contents_rating']['table']['join']['node'] = array(
    'left_table' => 'comments',
    'left_field' => 'cid',
    'field' => 'content_id',
  );

  $data['slashcomments_contents_rating']['score'] = array(
    'title' => t('Comment score'),
    'help' => t('Comment score w/o karma modifier.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Comment score'),
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['slashcomments_contents_rating']['num_ratings'] = array(
    'title' => t('Number of ratings'),
    'help' => t('Number of times the comment has been moderated.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Numbers of ratings'),
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['slashcomments_contents_rating']['last_rated'] = array(
    'title' => t('Last rated'),
    'help' => t('Date when comment was last rated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
      'name field' => t('Numbers of ratings'),
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['slashcomments_contents_karma']['table']['group'] = t('Slashcomments');

  $data['slashcomments_contents_karma']['table']['join']['comments'] = array(
    'left_field' => 'cid',
    'field' => 'content_id',
  );

  $data['slashcomments_contents_karma']['table']['join']['node'] = array(
    'left_table' => 'comments',
    'left_field' => 'cid',
    'field' => 'content_id',
  );

  $data['slashcomments_contents_karma']['score'] = array(
    'title' => t('Comment score with karma'),
    'help' => t('Comment score with karma modifier.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Comment score with karma.'),
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['slashcomments_contents_karma']['karma'] = array(
    'title' => t('Author karma'),
    'help' => t('Comment score with karma modifier.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Author karma'),
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['slashcomments_rating_options']['table']['group'] = t('Slashcomments');

  // How to join this table to the comments table
  $data['slashcomments_rating_options']['table']['join']['comments'] = array(
    'left_table' => 'slashcomments_contents_rating',
    'left_field' => 'most_rated_id',
    'field' => 'rating_id',
  );

  // How to join this table to the node table
  $data['slashcomments_rating_options']['table']['join']['node'] = array(
    'left_table' => 'slashcomments_contents_rating',
    'left_field' => 'most_rated_id',
    'field' => 'rating_id',
  );

  // Definition for most_rated field
  $data['slashcomments_rating_options']['rating'] = array(
    'title' => t('Comment rating'),
    'help' => t('Comment rating'),
    'field' => array(
      'handler' =>  'views_handler_field',
      'click sortable' => TRUE,
    ),
    // Information for accepting a rating as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'name field' => t('Comment rating'),
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

  $data['slashcomments_users_karma']['table']['group'] = t('Slashcomments');

  $data['slashcomments_users_karma']['table']['join']['comments'] = array(
    'left_field' => 'uid',
    'field' => 'uid'
  );

  $data['slashcomments_users_karma']['table']['join']['node'] = array(
    'left_field' => 'uid',
    'field' => 'uid'
  );

  $data['slashcomments_users_karma']['table']['join']['users'] = array(
    'left_field' => 'uid',
    'field' => 'uid'
  );

  $data['slashcomments_users_karma']['karma'] = array(
    'title' => t('User karma'),
    'help' => t('User karma'),
    'field' => array(
      'handler' => 'views_handler_field_slashcomments_user_karma',
      'click sortable' => TRUE
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'User karma',
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['slashcomments_users_karma']['total'] = array(
    'title' => t('Rated comments'),
    'help' => t('Total number of comments that contributed to karma'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Total comments for karma'),
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['slashcomments_users_karma']['positive'] = array(
    'title' => t('Positive rated comments'),
    'help' => t('Positive comments that contributed to karma'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Positive comments for karma'),
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['slashcomments_users_karma']['negative'] = array(
    'title' => t('Negative rated comments'),
    'help' => t('Negative of comments that contributed to karma'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Negative comments for karma'),
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['slashcomments_users_karma']['neutral'] = array(
    'title' => t('Neutral rated comments'),
    'help' => t('Neutral comments that contributed to karma'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => t('Neutral comments for karma'),
      'numeric' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}
