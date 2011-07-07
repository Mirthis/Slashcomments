<?php
//  $Id$

//
/**
 * @file
 */

// numbers of user processed by the update karma batch
define('SLASHCOMMENTS_BATCH_SIZE_UPDATE_KARMA', 100);
// numbers of user processed by the update rating batch
define('SLASHCOMMENTS_BATCH_SIZE_UPDATE_RATINGS', 100);
// numbers of user processed by the update rating batch
define('SLASHCOMMENTS_BATCH_SIZE_MIGRATE_OLD_DATA', 100);

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

function slashcomments_batch_update_ratings(&$context) {
  if (!isset($context['sandbox']['progress'])) {
    $sql = "SELECT count(DISTINCT content_id) FROM {votingapi_vote}
            WHERE content_type = 'comment' AND tag = 'slashcomments'";

    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_item'] = 0;
    $context['sandbox']['max'] = db_result(db_query($sql));
  }

  // user to be processed for each call
  $limit = SLASHCOMMENTS_BATCH_SIZE_UPDATE_RATINGS;

  // With each pass through the callback, retrieve the next group of nids.
  $sql = "SELECT DISTINCT content_id FROM {votingapi_vote}
    WHERE content_type = 'comment' AND tag = 'slashcomments'
      AND content_id > %d ORDER BY content_id";

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
        FROM {slashcomments_ratings}
        WHERE nums_rating = 0";

    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_item'] = 0;
    $context['sandbox']['max'] = db_result(db_query($sql));
  }

  // user to be processed for each call
  $limit = SLASHCOMMENTS_BATCH_SIZE_MIGRATE_OLD_DATA;
  sleep(2);

  // With each pass through the callback, retrieve the next group of nids.
  $sql = "SELECT cid content_id, karma
      FROM slashcomments_ratings
      WHERE nums_rating = 0 AND cid > %d
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
