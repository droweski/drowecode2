<?php

/**
 * @file
 * Include file for report listing form.
 */

/**
 * Returns list of users polarisreport entities.
 */
function polarisreport_list() {
  global $user;
  $uid = $user->uid;
  $query = new PolarisReportEntityFieldQuery();
  $query
    ->entityCondition('entity_type', 'polarisreport')
    ->entityCondition('bundle', 'polarisreport')
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
  $keys = array_keys($result['polarisreport']);
  $reports = entity_load('polarisreport', $keys);
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
      $act .= l(t('view'), "reports/$report_id/view" );
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

/**
 * Report delete form callback.
 */
function polarisreport_delete_form($form, &$form_state, $report) {
  $form_state['report'] = $report;
  
  $form['#submit'][] = 'polarisreport_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete report @name?', array('@name' => $report->report_name)),
    'reports/list',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  dpm($report);
  return $form;
}

/**
 * Report delete submit callback.
 */
function polarisreport_delete_form_submit($form, &$form_state) {
  $report = $form_state['report'];

  polarisreport_delete($report);

  drupal_set_message(t('The report %name has been deleted.', array('%name' => $report->report_name)));
  watchdog('report', 'Deleted report %name.', array('%name' => $report->report_name));

  $form_state['redirect'] = 'reports/list';
}

