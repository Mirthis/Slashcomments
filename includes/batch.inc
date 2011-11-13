<?php
//  $Id$

//
/**
 * @file
 */

// numbers of user processed by the update karma batch
define('SLASHCOMMENTS_BATCH_SIZE_UPDATE_KARMA', 10000);
// numbers of user processed by the update rating batch
define('SLASHCOMMENTS_BATCH_SIZE_UPDATE_RATINGS', 10000);
// numbers of user processed by the update rating batch
define('SLASHCOMMENTS_BATCH_SIZE_MIGRATE_OLD_DATA', 10000);
// numbers of user processed by the update rating batch
define('SLASHCOMMENTS_BATCH_SIZE_CONTENT_KARMA', 10000);
// numbers of user processed by the init ratings batch
define('SLASHCOMMENTS_BATCH_SIZE_INIT_RATINGS', 10000);

function slashcomments_batch_update_karma(&$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_user'] = 0;
    $context['sandbox']['max'] = db_result(db_query('SELECT COUNT(DISTINCT uid) FROM {slashcomments_contents_rating} WHERE uid <> 0'));
  }

  // user to be processed for each call
  $limit = SLASHCOMMENTS_BATCH_SIZE_UPDATE_KARMA;
  // With each pass through the callback, retrieve the next group of nids.
  $sql =  "SELECT DISTINCT uid FROM {slashcomments_contents_rating} WHERE uid > %d ORDER BY uid ASC";
  $result = db_query_range($sql, $context['sandbox']['current_user'], 0, $limit);

  while ($row = db_fetch_array($result)) {
    slashcomments_update_karma($row['uid']);

    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_user'] = $row['uid'];
    $context['message'] = t('Now calculating karna for user %uid (%current of %total)',
        array('%uid' => $row['uid'], '%current' => $context['sandbox']['progress'], '%total' => $context['sandbox']['max']));
  }
  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/*
  Batch 'finished' callback
 */
function slashcomments_batch_update_karma_finished($success, $results, $operations) {
  if ($success) {
    $message = t("Karma for all users has been updated");
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments',
      array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
  drupal_set_message($message);
}

function slashcomments_batch_update_content_karma(&$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_cid'] = 0;
    $context['sandbox']['max'] = db_result(db_query('SELECT COUNT(*) FROM {slashcomments_contents_rating} WHERE content_id > 0'));
  }

  // user to be processed for each call
  $limit = SLASHCOMMENTS_BATCH_SIZE_CONTENT_KARMA;

  // With each pass through the callback, retrieve the next group of nids.
  $sql =  "SELECT r.content_id cid, r.uid, k.content_id k_cid
    FROM {slashcomments_contents_rating} r
    LEFT JOIN {slashcomments_contents_karma} k
    ON r.content_id = k.content_id
    WHERE r.content_id > %d 
    ORDER BY cid ASC";

  $result = db_query_range($sql, $context['sandbox']['current_cid'], 0, $limit);

  while ($row = db_fetch_array($result)) {
    if($row['k_cid'] === null) {
      slashcomments_init_contents_karma($row['cid'], $row['uid'],TRUE);
    }
    slashcomments_update_contents_karma($row['cid']);

    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_cid'] = $row['cid'];
    $context['message'] = t('Now updating karma value for content %cid (%current of %total)',
      array('%cid' => $row['cid'], '%current' => $context['sandbox']['progress'], '%total' => $context['sandbox']['max']));
  }
  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}
/*
  Batch 'finished' callback
 */
function slashcomments_batch_update_content_karma_finished($success, $results, $operations) {
  if ($success) {
    $message = t("Karma for all contents has been updated");
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments',
      array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
  drupal_set_message($message);
}

function slashcomments_batch_init_ratings(&$context) {

  $sql = "SELECT count(*)
    FROM {comments} c 
    LEFT JOIN {slashcomments_contents_rating} r
    ON c.cid = r.content_id
    WHERE r.content_id is null";


  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_cid'] = 0;
    $context['sandbox']['max'] = db_result(db_query($sql));
  }

  // user to be processed for each call
  $limit = SLASHCOMMENTS_BATCH_SIZE_INIT_RATINGS;

  // With each pass through the callback, retrieve the next group of nids.
  $sql = "SELECT c.cid, c.uid, k.content_id k_cid 
    FROM {comments} c 
    LEFT JOIN {slashcomments_contents_rating} r
    ON c.cid = r.content_id
    LEFT JOIN {slashcomments_contents_karma} k
    ON c.cid = k.content_id
    WHERE r.content_id is null and c.cid > %d";

  $result = db_query_range($sql, $context['sandbox']['current_cid'], 0, $limit);

  while ($row = db_fetch_array($result)) {
    slashcomments_update_rating($row['cid']);

    if(_slashcomments_karma_enabled()) {
      if($row['k_cid'] === null) {
        slashcomments_init_contents_karma($row['cid'], $row['uid'],TRUE);
      }
      slashcomments_update_contents_karma($row['cid']);
    }

    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_cid'] = $row['cid'];
    $context['message'] = t('Now initializing rating for content %cid (%current of %total)',
      array('%cid' => $row['cid'], '%current' => $context['sandbox']['progress'], '%total' => $context['sandbox']['max']));
  }
  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

function slashcomments_batch_init_ratings_finished($success, $results, $operations) {
  if ($success) {
    $message = t("Data for all contents has been updated");
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments',
      array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
  drupal_set_message($message);
}

function slashcomments_batch_update_ratings(&$context) {
  if (!isset($context['sandbox']['progress'])) {
    $sql = "SELECT count(DISTINCT content_id) FROM {votingapi_vote} v, {comments} c
      WHERE content_type = 'comment' AND tag = 'slashcomments' AND v.content_id = c.cid";

    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_item'] = 0;
    $context['sandbox']['max'] = db_result(db_query($sql));
  }

  // user to be processed for each call
  $limit = SLASHCOMMENTS_BATCH_SIZE_UPDATE_RATINGS;

  // With each pass through the callback, retrieve the next group of nids.
  $sql = "SELECT DISTINCT content_id FROM {votingapi_vote} v, {comments} c
    WHERE content_type = 'comment' AND tag = 'slashcomments'
    AND content_id > %d AND v.content_id = c.cid ORDER BY content_id
    ";

  $result = db_query_range($sql, $context['sandbox']['current_item'], 0, $limit);

  while ($row = db_fetch_array($result)) {
    slashcomments_update_rating($row['content_id']);

    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_item'] = $row['content_id'];
    $context['message'] = t('Now calculating rating for comment %cid (%current of %total)',
      array('%cid' => $row['content_id'], '%current' => $context['sandbox']['progress'], '%total' => $context['sandbox']['max']));
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/*
  Batch 'finished' callback
 */
function slashcomments_batch_update_ratings_finished($success, $results, $operations) {
  if ($success) {
    $message = t("Rating for all comments has been updated");
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments',
      array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
  drupal_set_message($message);
}

function slashcomments_batch_migrate_old_data(&$context) {
  if (!isset($context['sandbox']['progress'])) {
    $sql = "SELECT count(DISTINCT cid)
      FROM {slashcomments_ratings}";

    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_item'] = 0;
    $context['sandbox']['max'] = db_result(db_query($sql));
  }
  // user to be processed for each call
  $limit = SLASHCOMMENTS_BATCH_SIZE_MIGRATE_OLD_DATA;

  // With each pass through the callback, retrieve the next group of nids.
  $sql = "SELECT cid content_id, karma
    FROM {slashcomments_ratings}
    WHERE cid > %d
    ORDER BY cid ASC";

  $result = db_query_range($sql, $context['sandbox']['current_item'], 0, $limit);

  while ($row = db_fetch_array($result)) {
    $record = array();
    $record['content_id'] = $row['content_id'];
    $record['karma'] = $row['karma'];
    $record['created'] = $record['modified'] = time();

    drupal_write_record('slashcomments_contents_karma', $record);

    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_item'] = $row['content_id'];
    $context['message'] = t('Now migrating data for comment %cid (%current of %total)',
      array('%cid' => $row['content_id'], '%current' => $context['sandbox']['progress'], '%total' => $context['sandbox']['max']));
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/*
  Batch 'finished' callback
 */
function slashcomments_batch_migrate_old_data_finished($success, $results, $operations) {
  if ($success) {
    $message = t("Rating for all comments has been updated");
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments',
      array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
  drupal_set_message($message);
}
