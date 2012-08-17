<?php

/**
 * @file
 * Provides Entity metadata integration.
 */

/**
 * Extend the defaults.
 */
class PolarisReportMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['report_name'] = array(
      'label' => t("Report name"),
      'description' => t("The report name as supplied by the author."),
      'type' => 'text',
      'schema field' => 'report_name',
    );
    $properties['uid'] = array(
      'label' => t("User ID"),
      'description' => t("The owner of the profile."),
      'type' => 'user',
      'schema field' => 'uid',
    );
    $properties['date'] = array(
      'label' => t('Report date'),
      'description' => t("The date the profile was created."),
      'type' => 'text',
      'schema field' => 'date',
    );
    $properties['report_type'] = array(
      'label' => t("Report name"),
      'description' => t("The report type."),
      'type' => 'integer',
      'schema field' => 'report_type',
    );
    $properties['p_type1'] = array(
      'label' => t("Subject 1 p-type"),
      'description' => t("Subject 1 p-type."),
      'type' => 'text',
      'schema field' => 'p_type1',
    );
    $properties['narrative'] = array(
      'label' => t("Narrative flag"),
      'description' => t("Display narrative selection."),
      'type' => 'Narrative',
      'schema field' => 'narrative',
    );
    
    return $info;
  }
}
