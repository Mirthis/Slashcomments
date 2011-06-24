<?php

/**
 * @file
 */

/**
 * Implementation of hook_admin_settings().
 */
function slashcomments_admin_general_form() {

  drupal_add_js(drupal_get_path('module', 'slashcomments') .'/scripts/slashcomments-settings.js');

  $form['slashcomments_general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['slashcomments_general']['slashcomments_default_score'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial score for new comments from registered users'),
    '#size' => 5,
    '#default_value' => variable_get('slashcomments_default_score', SLASHCOMMENTS_DEFAULT_SCORE),
    '#description' => t('Score assigned to new comments posted by registered users. The actual value
                        can be affected by other factors as the user karma.'),
  );
 
  $form['slashcomments_general']['slashcomments_default_score_anonymous'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial score for new comments from anonymous users'),
    '#size' => 5,
    '#default_value' => variable_get('slashcomments_default_score_anonymous', SLASHCOMMENTS_DEFAULT_SCORE_ANONYMOUS),
    '#description' => t('Score assigned to new comments posted by anonymous users. The actual value
                        can be affected by other factors as the user karma.'),
  )
  ;

  $form['slashcomments_general']['slashcomments_limit_newbie'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of days before a new user can moderate'),
    '#size' => 5,
    '#default_value' => variable_get('slashcomments_limit_newbie', SLASHCOMMENTS_LIMIT_NEWBIE),
    '#description' => t('Number of days needed before a new registered user is allowed to moderate'),
  );

  $form['slashcomments_general']['slashcomments_mod_per_day'] = array(
    '#type' => 'textfield',
    '#title' => t('Daily moderation per user'),
    '#size' => 5,
    '#default_value' => _slashcomments_get_mod_per_day(),
    '#description' => t('Number of comments that a single moderator can moderate during the same day. 
    A 0 value imply that user can\'t moderate. A !infinite value imply that users has infinite mod points',
    array('!infinite' => SLASHCOMMENTS_INFINITE_MOD_POINTS)),
  );

  $form['slashcomments_general']['slashcomments_limit_takepart'] = array(
    '#type' => 'checkbox',
    '#title' => t("Users who commented a content can't moderate it"),
    '#default_value' => variable_get('slashcomments_limit_takepart', SLASHCOMMENTS_LIMIT_TAKEPART),
    '#description' => t("If set user who had left comment for a node can't moderate others comments on that same node."),
    '#attributes' => array(
      'onclick' => "slashcomments_toggle_takepart()",
    )
  );

  $form['slashcomments_general']['slashcomments_help_page_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Help page path'),
    '#size' => 30,
    '#default_value' => _slashcomments_get_help_page_path(),
    '#description' => t('Help page linked by the question mark close to each comment score.
           The default value point to the module built-in help page. If left blank the help link is not displayed.'),
  );

   // $form['#submit'][] = 'slaschomments_admin_general_submit';
  return system_settings_form($form);
}


function slashcomments_admin_karma_form() {

  drupal_add_js(drupal_get_path('module', 'slashcomments') .'/scripts/slashcomments-settings.js');

  $form['slashcomments_karma'] = array(
    '#type' => 'fieldset',
    '#title' => t('Karma'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['slashcomments_karma']['slashcomments_enable_karma'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable karma'),
    '#default_value' => variable_get('slashcomments_enable_karma', SLASHCOMMENTS_ENABLE_KARMA),
    '#description' => t('Karma for each user will be calculated based on their comment score and will affect their ability to moderate others and the initial rating of their new comments.'),
    '#attributes' => array(
      'onclick' => "slashcomments_toggle_karma(this)",
    )
  );


  $form['slashcomments_karma']['slashcomments_default_karma'] = array(
    '#type' => 'textfield',
    '#title' => t('Default karma value'),
    '#size' => 5,
    '#default_value' => variable_get('slashcomments_default_karma', SLASHCOMMENTS_DEFAULT_KARMA),
    '#description' => t("Karma value of a user who doesn't meet the criteria to have his own karma
                        cakculated"),
  );

  $form['slashcomments_karma']['slashcomments_ratings_for_karma'] = array(
    '#type' => 'textfield',
    '#title' => t('Moderated comment before karma is calculated'),
    '#size' => 5,
    '#default_value' => variable_get('slashcomments_ratings_for_karma', SLASHCOMMENTS_RATINGS_FOR_KARMA),
    '#description' => t("Karma for a user is computed only when a certain number of his comments have been
                        moderated at least one"),
  );

  $form['slashcomments_karma']['slashcomments_limit_karma'] = array(
    '#type' => 'textfield',
    '#title' => t('Karma value user need to be able to moderate'),
    '#size' => 5,
    '#default_value' => _slashcomments_get_limit_karma(),
    '#description' => t('Karma value a user must have to be able to moderate'),
  );

  $form['#submit'][] = 'slashcomments_admin_karma_form_submit';

  return system_settings_form($form);
}


function slashcomments_admin_ratings_form() {
  $form['options']['#tree'] = TRUE;

  $options = _slashcomments_settings_get_options();

  foreach($options as $opt) {
    $form['options'][$opt['rating_id']] = array(
      'rating_id' => array (
        '#type' => 'hidden',
        '#value' => $opt['rating_id'],
      ),
      'rating' => array (
        '#type' => 'textfield',
        '#size' => 15,
        '#required' => TRUE,
        '#default_value' => $opt['rating']
      ),
      'score' => array (
        '#type' => 'textfield',
        '#size' => 15,
        '#required' => TRUE,
        '#default_value' => $opt['score']
      ), 
      'enabled' => array (
        '#type' => 'checkbox',
        '#default_value' => $opt['enabled']
      ), 
      'weight' => array (
        '#type' => 'weight',
        '#delta' => 10,
        '#default_value' => $opt['weight'],
        '#attributes' => array('class' => 'weight'),
      )
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Changes'),
  );

  return $form;
}

function slashcomments_admin_mantain_form() {

  $form['calculate_karma'] = array(
    '#type' => 'submit',
    '#value' => t('Re-calculate karma'),
  );
  
  $form['calculate ratings'] = array(
    '#type' => 'submit',
    '#value' => t('Re-calculate ratings'),
  );

  $form['migrate_data'] = array(
    '#type' => 'submit',
    '#value' => t('Migrate data'),
  );

  return $form;
}

function slashcomments_admin_ratings_form_validate($form, &$form_state) {
    $score_error = FALSE;
    foreach($form_state['values']['options'] as $v) {
      if(!(_slashcomments_is_integet($v['score']))) {
        if($score_error) {
          form_set_error('options][' . $v['rating_id'] . '][score');
        }
        else {
          form_set_error('options][' . $v['rating_id'] . '][score', t('Score must be a number'));
          $score_error = TRUE;
        }
      }
    }
}

function slashcomments_admin_mantain_form_submit($form, &$form_state) {
  switch ($form_state['values']['op']) {
    case 'Re-calculate karma';
    slashcomments_update_all_karma();
    break;
  case 'Re-calculate ratings':
    slashcomments_update_all_ratings();
    break;
  case 'Migrate data':
    slashcomments_migrate_old_data();
    break;
  }
}


function slashcomments_admin_ratings_form_submit($form, &$form_state) {
  $posted_options = $form_state['values']['options'];
  $stored_options = _slashcomments_settings_get_options();

  $ids = array_keys(array_intersect_assoc($posted_options, $stored_options));
  $posted_only = array_diff_assoc($posted_options, $stored_options);
  $stored_only = array_diff_assoc($stored_options, $posted_options);

  foreach($ids as $id) {
    $posted_options[$id]['enable'] = '' . $posted_options['enable'];
    if(array_diff($posted_options[$id], $stored_options[$id])) {
      $sql = "UPDATE {slashcomments_rating_options}
        SET rating = '%s', score = %d, enabled = %d, weight = %d
        WHERE rating_id = %d";

      $item = $posted_options[$id];
      db_query($sql, $item['rating'], $item['score'], $item['enabled'], $item['weight'], $id);
    }
  }
}


/**
 * Get available ratings
 */
function _slashcomments_settings_get_options() {

  /* extract enabled ratings from the db */
  $sql = "SELECT rating_id, rating, score, weight, enabled
    FROM {slashcomments_rating_options}
    ORDER BY weight
    ";

  $db_ratings = db_query($sql);

  $rating_options = array();
  while($rating = db_fetch_array($db_ratings)) {
    $rating_options[$rating['rating_id']] = $rating;
  }

  return $rating_options;
}

function _slashcomments_is_integet($value) {
  return is_numeric($value) AND (int)$value == $value;
}

function _slashcomments_is_non_negative_integet($value) {
  return is_numeric($value) AND (int)$value == $value AND (int)$value >= 0;
}

function slashcomments_admin_general_form_validate($form, &$form_state) {

  if(!_slashcomments_is_integet($form_state['values']['slashcomments_default_score'])) {
    form_set_error('slashcomments_default_score',t('Initial score for registered users must be an integer'));
  }
  if(!_slashcomments_is_integet($form_state['values']['slashcomments_default_score_anonymous'])) {
    form_set_error('slashcomments_default_score_anonymous',t('Initial score for anonymous users must be an integer'));
  }
  if(!_slashcomments_is_non_negative_integet($form_state['values']['slashcomments_limit_newbie'])) {
    form_set_error('slashcomments_limit_newbie',t('Numbers of days before a new user can moderate must be a non-negative number'));
  }
  if(!_slashcomments_is_non_negative_integet($form_state['values']['slashcomments_mod_per_day'])) {
    form_set_error('slashcomments_mod_per_day',t('Daily moderation per user must be greater or equal to 0'));
  }
}

function slashcomments_admin_karma_form_validate($form, &$form_state) {
  if(!$form_state['values']['slashcomments_enable_karma']) {
    return;
  }
  if(!_slashcomments_is_integet($form_state['values']['slashcomments_default_karma'])) {
    form_set_error('slashcomments_default_karma',t('Default karma value must be an integer'));
  }
  if(!_slashcomments_is_non_negative_integet($form_state['values']['slashcomments_ratings_for_karma'])) {
    form_set_error('slashcomments_ratings_for_karma',t('Moderated comments before karma is calculated must be greater or equal to 0'));
  }
  if(!_slashcomments_is_integet($form_state['values']['slashcomments_limit_karma'])) {
    form_set_error('slashcomments_limit_karma',t('Karma required for moderation must be greater or equal to 0'));
  }
}

/**
 * Implementation of admin setting  form submit function
 */
function slashcomments_admin_karma_form_submit($form, &$form_state) {
  if ($form_state['values']['slashcomments_enable_karma'] == 1) {
    if (!_slashcomments_karma_enabled() 
      || $form_state['values']['slashcomments_ratings_for_karma'] <> _slashcomments_get_ratings_for_karma()) {
        variable_set('slashcomments_ratings_for_karma', $form_state['values']['slashcomments_ratings_for_karma']);
        slashcomments_update_all_karma();
      }
  }
  else {
    $form_state['values']['slashcomments_limit_karma'] = _slashcomments_get_limit_karma();
    $form_state['values']['slashcomments_default_karma'] = _slashcomments_get_default_karma();
    $form_state['values']['slashcomments_ratings_for_karma'] = _slashcomments_get_ratings_for_karma();
  }
}

function theme_slashcomments_admin_ratings_form($form) {

  // the variable that will hold our form HTML output
  $output = '';

  // loop through each "row" in the table array
  foreach($form['options'] as $id => $row) {
    // if $id is not a number skip this row in the data structure
    if (!is_numeric($id))
      continue;

    // this array will hold the table cells for a row
    $this_row = array();

    // first, add the "name" markup
    $this_row[] = drupal_render($row['rating']);
    $this_row[] = drupal_render($row['score']);
    $this_row[] = drupal_render($row['enabled']);

    // Add the weight field to the row
    // the Javascript to make our table drag and drop will end up hiding this cell
    $this_row[] = drupal_render($row['weight']);

    //Add the row to the array of rows
    $table_rows[] = array('data' => $this_row, 'class'=>'draggable');
  }

  // Make sure the header count matches the column count
  $header = array(
    'Rating',
    'Score',
    'Enabled',
    'Weight',
  );

  $table_id = 'options';

  // this function is what brings in the javascript to make our table drag-and-droppable
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'weight');   

  // over-write the 'my_items' form element with the markup generated from our table
  $form['options'] = array(
    '#type' => 'markup',
    '#value' => theme('table', $header, $table_rows, array('id' => $table_id)),
    '#weight' => '1',
  );

  // render the form
  // note, this approach to theming the form allows you to add other elements in the method
  // that generates the form, and they will automatically be rendered correctly
  $output = drupal_render($form);

  return $output;
}

function slashcomments_update_all_karma() {
  $batch  = array(
    'operations' => array(array('slashcomments_batch_update_karma',array())),
    'finished' => 'slashcomments_batch_update_karma_finished',
    'title' => t('Updating users karma'),
    'init_message' => t('Karma update is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Karma update has encountered an error.'),
    'file' => drupal_get_path('module', 'slashcomments') . '/includes/batch.inc',
  );

  batch_set($batch);
}

function slashcomments_update_all_ratings() {
  $batch  = array(
    'operations' => array(array('slashcomments_batch_update_ratings',array())),
    'finished' => 'slashcomments_batch_update_ratings_finished',
    'title' => t('Updating comments rating'),
    'init_message' => t('Ratings update is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Rating update has encountered an error.'),
    'file' => drupal_get_path('module', 'slashcomments') . '/includes/batch.inc',
  );

  batch_set($batch);
}

function slashcomments_migrate_old_data() {
  $batch  = array(
    'operations' => array(array('slashcomments_batch_migrate_old_data',array())),
    'finished' => 'slashcomments_batch_migrate_old_data_finished',
    'title' => t('Migrating v1.0 data to current version'),
    'init_message' => t('Data migration is starting.'),
    'progress_message' => t('Processed @current out of @total.'),
    'error_message' => t('Data migration has encountered an error.'),
    'file' => drupal_get_path('module', 'slashcomments') . '/includes/batch.inc',
  );

  batch_set($batch);
}
