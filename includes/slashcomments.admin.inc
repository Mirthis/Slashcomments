<?php

/**
 * @file
 */

/**
 * Implementation of hook_admin_settings().
 */
function slashcomments_admin_general() {

  drupal_add_js(drupal_get_path('module', 'slashcomments') .'/scripts/slashcomments-settings.js');

  $form['slashcomments_general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['slashcomments_general']['slashcomments_limit_newbie'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of days before a new user can moderate'),
    '#size' => 5,
    '#default_value' => variable_get('slashcomments_limit_newbie', SLASHCOMMENTS_LIMIT_NEWBIE),
    '#description' => t('Number of days needed before a new registered user is allowed to moderate'),
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

  $form['slashcomments_general']['slashcomments_delete_takepart'] = array(
    '#type' => 'checkbox',
    '#title' => t("Delete user moderation left before user participation"),
    '#default_value' => variable_get('slashcomments_delete_takepart', SLASHCOMMENTS_DELETE_TAKEPART),
    '#description' => t("Delete user modertion on node's comment if the user himself left a comment for the node participating to the discussion."),
    '#attributes' => array(
      'onclick' => "slashcomments_toggle_takepart(this)",
    )
  );

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


  $form['slashcomments_karma']['slashcomments_limit_karma'] = array(
    '#type' => 'textfield',
    '#title' => t('Karma value user need to be able to moderate'),
    '#size' => 5,
    '#default_value' => variable_get('slashcomments_limit_karma', SLASHCOMMENTS_LIMIT_KARMA),
    '#description' => t('Karma value a user must have to be able to moderate'),
  );

  $form['#submit'][] = 'slaschomments_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Implementation of admin setting  form submit function
 */
function slaschomments_admin_general_submit($form, &$form_state) {
  if ($form_state['values']['slashcomments_enable_karma'] == 1) {
    slashcomments_recalculate_karma();
  }
  else {
    $form_state['values']['slashcomments_limit_karma'] = variable_get('slashcomments_limit_karma', SLASHCOMMENTS_LIMIT_KARMA);
  }
}

/*
 * Calculate karma for all users when when the enable karma option is set
 */
function slashcomments_recalculate_karma() {

  // Erase all karma values previuosly stored
  db_query("TRUNCATE TABLE {slashcomments_karma}");

  // store current time
  $current_time = time();

  // insert new karma value for each users who meets required criteria
  $sql =  "INSERT INTO {slashcomments_karma}
  (uid, karma, total, positive, negative, neutral, timestamp)
  SELECT a.uid, karma, total, positive, negative, total-negative-positive, timestamp
  FROM
  (SELECT uid, AVG(CASE WHEN score < -3 THEN -3
  WHEN score > 5 THEN 5
  ELSE score END ) karma,
    SUM(CASE WHEN score < 1 THEN 1 ELSE 0 END) negative,
    SUM(CASE WHEN score > 1 THEN 1 ELSE 0 END) positive
    FROM {slashcomments_ratings} r
    WHERE r.nums_rating <> 0
    GROUP BY uid
    HAVING count(*) >= 5) a,
      (SELECT uid, count(*) total, max(%d) timestamp
      FROM {comments}
      GROUP BY uid
    ) b
    WHERE a.uid = b.uid
    AND a.uid <> 0";

  db_query($sql, $current_time);
}
