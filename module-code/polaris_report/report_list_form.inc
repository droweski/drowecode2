<?php

/**
 * @file
 * Include file for report listing form.
 */

/**
 * Returns list of users polaris_report entities.
 */
function polaris_report_list() {
  global $user;
  $uid = $user->uid;
  $query = new PolarisEntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'polaris_report')
    ->entityCondition('bundle', 'polaris_report')
    ->propertyCondition('uid', $uid)
    ->propertyOrderBy('date', 'DESC');   
  $result = $query->execute();
  if (empty($result)) {
    $content[] = array(
      '#type' => 'item',
      '#markup' => t('You currently have no reports.'),
    );
    $content[] = array(
      '#type' => 'item',
      '#markup' => l(t('Add a report'), "reports/add"),
    );
    return $content;
  }
  $keys = array_keys($result['polaris_report']);
  $reports = entity_load('polaris_report', $keys);
  $header = array(
    'report' => array (
      'data' => t('Report'),
      'field' => 'report',
    ),
    'Date' => array (
      'data' => t('Date'),
      'field' => 'date',
      'sort' => 'DESC',
    ),
  );
  if(user_access('administer reports')) {
    $header[] = t('Administer');
  }
 
  $rows = array();
  foreach($reports as $report_id => $report) {
    $row = array();
    $row[] = $report->report_name;
    $row[] = $report->date;

    if(user_access('administer reports')) {
      $act = l(t('edit'), "reports/$report_id/edit", array('query' => drupal_get_destination()));
      $act .= ' | ';
      $act .= l(t('delete'), "reports/$report_id/delete", array('query' => drupal_get_destination()));
      $act .= ' | ';
      $act .= l(t('print'), "reports/$report_id/generate" );
      $row[] = $act;
    }

    $rows[] = $row;
  }
  $content['reports'] = array(
    '#theme' => 'table',
    '#title' => t('Polaris reports'),
    '#header' => $header,
    '#rows' => $rows,
  );
  
  $content['pager_pager'] = array('#theme' => 'pager');

  return $content;
}
