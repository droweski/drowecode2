<?php

/**
 * @file
 * Controller definition file.
 */

/**
 * Polaris report controller
 */
class PolarisReportController extends DrupalDefaultEntityController {
  public function __construct($entityType) {
    parent::__construct('polaris_report');
  }

  // ---------------------------------------------------------------------------------

  public function create() {
    $report = new StdClass();
    $report->report_id = 0;
    $report->report_name = '';
    $report->uid = 0;
    $report->score_type = '';
    $report->report_type = '';
    $report->date = format_date(REQUEST_TIME, 'custom', 'Y-m-d H:i:s');
    $report->fname1 = '';
    $report->lname1 = '';
    $report->org1 = '';
    $report->p_type1 = '';
    $report->ei_score1 = 0;
    $report->ns_score1 = 0;
    $report->ft_score1 = 0;
    $report->jp_score1 = 0;
    $report->fname2 = '';
    $report->lname2 = '';
    $report->org2 = '';
    $report->p_type2 = '';
    $report->ei_score2 = 0;
    $report->ns_score2 = 0;
    $report->ft_score2 = 0;
    $report->jp_score2 = 0;
    $report->narrative = 0;
    $report->temperament = 0;
    $report->suggestions = 0;
    $report->cat_org = 0;
    $report->cat_lead = 0;
    $report->cat_com = 0;
    $report->cat_prob = 0;
    $report->cat_stress = 0;
    $report->cat_motive = 0;
    $report->cat_team = 0;
    $report->cat_learn = 0;
    $report->cat_growth = 0;
    
    return $report;
  }

  // Save() method.
  public function save($report) {
    if(empty($report->report_id)) {
      drupal_write_record('polaris_report', $report);
      // Make sure to invoke the insert hook.
      module_invoke_all('entity_insert', $report, 'polaris_report');
    }
    else {
      drupal_write_record('polaris_report', $report, 'report_id');
      // Make sure to invoke the update hook.
      module_invoke_all('entity_update', $report, 'polaris_report');
    }

    return $report;
  }

  // Delete() method.
  public function delete($report_ids) {
    if(empty($report_ids)) {
      return FALSE;
    }
    $reports = entity_load('polaris_report', $report_ids);
    db_delete('polaris_report')
      ->condition('report_id', $report_ids, 'IN')
      ->execute();
    // Invoke delete hook for each report.
    foreach($reports as $report) {
      module_invoke_all('entity_delete', $report, 'polaris_report');
    }
    // Clear caches when an entity is deleted.
    cache_clear_all();
    $this->resetCache();
    return TRUE;
  }
}

/**
 * @todo Implement the uri callback.

function polaris_report_uri($report) {
  return array(
    'path' => 'reports/' . $report->report_id,
  );
}
 * 
 */