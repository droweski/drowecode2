<?php

/**
 * @file
 * Include file for polaris report form.
 */  

/**
 * Report add/edit page callback.
 */
function polarisreport_report_add() {
  // Create a new entity for use with form.
  $values = array();
  $report = entity_get_controller('polarisreport')->create($values);

  return drupal_get_form('polarisreport_report_form', $report);
}

/**
 * Report add/edit form.
 */
function polarisreport_report_form($form, &$form_state, $report) {
  $form['#report'] = $report;
  
  $form['#attributes']['class'] = array(
    'htab',
  );
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'polarisreport') . '/css/htab.css',
  );
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'polarisreport') . '/js/steps.js',
  );
  $form['tabs'] = array(
    '#type' => 'vertical_tabs'
  );
// Tab 1 --------------------------------------------------------------------
  $form['tab_1'] = array(
    '#type' => 'fieldset',
    '#title' => 'Report Format',
    '#group' => 'tabs',
  );
  $form['tab_1']['report_type'] = array(
    '#type' => 'radios',
    '#options' => array(
      '1'   => t('Single'),
      '121' => t('One to One'),
    ),
    '#title' => t('Select report type'),
    '#default_value' => !empty($report->report_type) ? $report->report_type : '1',
  );
  $form['tab_1']['score_type'] = array(
    '#type' => 'radios',
    '#options' => array(
      'raw'   => t('Scores'),
      'percent' => t('Percentages'),
      'tdi' => t('TDI Scores'),
      'ear' => t('EAR Scores'),
    ),
    '#title' => t('Select scoring system:'),
    '#default_value' => !empty($report->score_type) ? $report->score_type : 'raw',
  );
  $date = date_parse($report->date);
  $form['tab_1']['date'] = array(
    '#type' => 'value',
    '#title' => t('Report date'),
    '#default_value' => $date,
    '#required' => TRUE,
  );
// Tab 2 --------------------------------------------------------------------
  $form['tab_2'] = array(
    '#type' => 'fieldset',
    '#title' => 'Client Information',
    '#group' => 'tabs',
  );
    $form['tab_2']['first-type'] = array(
    '#type' => 'fieldset',
    '#description' => 'Info for first P type',
  );
  $form['tab_2']['first-type']['fname1'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#required' => FALSE,
    '#size' => 40, 
    '#maxlength' => 40,    
    '#attributes' => array( 
      'class' => array('text-box'),
    ),
    '#default_value' => $report->fname1,
  );
  $form['tab_2']['first-type']['lname1'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#title_display' => 'before',    
    '#required' => FALSE,
    '#size' => 40, 
    '#maxlength' => 40,
    '#attributes' => array( 
      'class' => array('text-box'),
    ),
    '#default_value' => $report->lname1,
  );
  $form['tab_2']['first-type']['org1'] = array(
    '#type' => 'textfield',
    '#title' => t('Company/Organization'),
    '#title_display' => 'before',
    '#required' => FALSE,
    '#size' => 40, 
    '#maxlength' => 40,
    '#attributes' => array( 
      'class' => array('text-box'),
    ),
    '#default_value' => $report->org1,
  );
  $form['tab_2']['first-type']['p_type1'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#multiple' => FALSE, 
    '#options' => array('ENFJ' => 'ENFJ', 'ENFP' => 'ENFP', 'ENTJ' => 'ENTJ', 'ENTP' => 'ENTP', 'ESFJ' => 'ESFJ', 'ESFP' => 'ESFP', 'ESTJ' => 'ESTJ', 'ESTP' => 'ESTP',
      'INFJ' => 'INFJ', 'INFP' => 'INFP', 'INTJ' => 'INTJ', 'INTP' => 'INTP', 'ISFJ' => 'ISFJ', 'ISFP' => 'ISFP', 'ISTJ' => 'ISTJ', 'ISTP' => 'ISTP'),
    '#attributes' => array( 
      'class' => array('select-box'),
    ),
    '#default_value' => $report->p_type1,
  );
  $form['tab_2']['first-type']['scores'] = array(
    '#type' => 'fieldset',
    '#attributes' => array( 
      'class' => array('scores'),
    ), 
  );  
  $form['tab_2']['first-type']['scores']['ENFJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> N-Value: </span><span class="label"> F-Value: </span><span class="label"> J-Value: </span>',
    '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ENFJ'),
      ),
    ),
  );
  $form['tab_2']['first-type']['scores']['ENFP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> N-Value: </span><span class="label"> F-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ENFP'),
      ),
    ),
  );  
  $form['tab_2']['first-type']['scores']['ENTJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> N-Value: </span><span class="label"> T-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ENTJ'),
      ),
    ),
  );
  $form['tab_2']['first-type']['scores']['ENTP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> N-Value: </span><span class="label"> T-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ENTP'),
      ),
    ),
  );  
  $form['tab_2']['first-type']['scores']['ESFJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> S-Value: </span><span class="label"> F-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ESFJ'),
      ),
    ),
  ); 
  $form['tab_2']['first-type']['scores']['ESFP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> S-Value: </span><span class="label"> F-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ESFP'),
      ),
    ),
  );   
  $form['tab_2']['first-type']['scores']['ESTJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> S-Value: </span><span class="label"> T-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ESTJ'),
      ),
    ),
  ); 
  $form['tab_2']['first-type']['scores']['ESTP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> S-Value: </span><span class="label"> T-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ESTP'),
      ),
    ),
  ); 
  $form['tab_2']['first-type']['scores']['INFJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> N-Value: </span><span class="label"> F-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'INFJ'),
      ),
    ),
  );
  $form['tab_2']['first-type']['scores']['INFP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> N-Value: </span><span class="label"> F-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'INFP'),
      ),
    ),
  );  
  $form['tab_2']['first-type']['scores']['INTJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> N-Value: </span><span class="label"> T-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'INTJ'),
      ),
    ),
  );
  $form['tab_2']['first-type']['scores']['INTP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> N-Value: </span><span class="label"> T-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'INTP'),
      ),
    ),
  );  
  $form['tab_2']['first-type']['scores']['ISFJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> S-Value: </span><span class="label"> F-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ISFJ'),
      ),
    ),
  ); 
  $form['tab_2']['first-type']['scores']['ISFP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> S-Value: </span><span class="label"> F-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ISFP'),
      ),
    ),
  );   
  $form['tab_2']['first-type']['scores']['ISTJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> S-Value: </span><span class="label"> T-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ISTJ'),
      ),
    ),
  ); 
  $form['tab_2']['first-type']['scores']['ISTP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> S-Value: </span><span class="label"> T-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type1"]' => array('value' => 'ISTP'),
      ),
    ),
  );   
  $form['tab_2']['first-type']['scores']['ei_score1'] = array(
    '#type' => 'textfield',
    '#size' => 4, 
    '#maxlength' => 4,
    '#default_value' => $report->ei_score1,
  );
  $form['tab_2']['first-type']['scores']['ns_score1'] = array(
    '#type' => 'textfield',
    '#size' => 4, 
    '#maxlength' => 4,
    '#default_value' => $report->ns_score1,
  );
  $form['tab_2']['first-type']['scores']['ft_score1'] = array(
    '#type' => 'textfield',
    '#size' => 4, 
    '#maxlength' => 4,
    '#default_value' => $report->ft_score1,
  );
  $form['tab_2']['first-type']['scores']['jp_score1'] = array(
    '#type' => 'textfield',
    '#size' => 4, 
    '#maxlength' => 4,
    '#default_value' => $report->jp_score1,
  );
// Second subject
  $form['tab_2']['second-type'] = array(
    '#type' => 'fieldset',
    '#description' => 'Info for second P type',
    '#states' => array(
      'visible' => array(
        ':input[name="report_type"]' => array('value' => '121'),
      ),  
    ),
  );
  $form['tab_2']['second-type']['fname2'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#required' => FALSE,
    '#size' => 40, 
    '#maxlength' => 40,    
    '#attributes' => array( 
      'class' => array('text-box'),
    ),
    '#default_value' => $report->fname2,
  );
  $form['tab_2']['second-type']['lname2'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#title_display' => 'before',    
    '#required' => FALSE,
    '#size' => 40, 
    '#maxlength' => 40,
    '#attributes' => array( 
      'class' => array('text-box'),
    ),
    '#default_value' => $report->lname2,
  );
  $form['tab_2']['second-type']['org2'] = array(
    '#type' => 'textfield',
    '#title' => t('Company/Organization'),
    '#title_display' => 'before',
    '#required' => FALSE,
    '#size' => 40, 
    '#maxlength' => 40,
    '#attributes' => array( 
      'class' => array('text-box'),
    ),
    '#default_value' => $report->org2,
  );
  $form['tab_2']['second-type']['p_type2'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#multiple' => FALSE, 
    '#options' => array('ENFJ' => 'ENFJ', 'ENFP' => 'ENFP', 'ENTJ' => 'ENTJ', 'ENTP' => 'ENTP', 'ESFJ' => 'ESFJ', 'ESFP' => 'ESFP', 'ESTJ' => 'ESTJ', 'ESTP' => 'ESTP',
      'INFJ' => 'INFJ', 'INFP' => 'INFP', 'INTJ' => 'INTJ', 'INTP' => 'INTP', 'ISFJ' => 'ISFJ', 'ISFP' => 'ISFP', 'ISTJ' => 'ISTJ', 'ISTP' => 'ISTP'),
    '#attributes' => array( 
      'class' => array('select-box'),
    ),
    '#default_value' => $report->p_type2,
  );
  $form['tab_2']['second-type']['scores'] = array(
    '#type' => 'fieldset',
    '#attributes' => array( 
      'class' => array('scores'),
    ), 
  );  
  $form['tab_2']['second-type']['scores']['ENFJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> N-Value: </span><span class="label"> F-Value: </span><span class="label"> J-Value: </span>',
    '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ENFJ'),
      ),
    ),
  );
  $form['tab_2']['second-type']['scores']['ENFP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> N-Value: </span><span class="label"> F-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ENFP'),
      ),
    ),
  );  
  $form['tab_2']['second-type']['scores']['ENTJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> N-Value: </span><span class="label"> T-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ENTJ'),
      ),
    ),
  );
  $form['tab_2']['second-type']['scores']['ENTP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> N-Value: </span><span class="label"> T-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ENTP'),
      ),
    ),
  );  
  $form['tab_2']['second-type']['scores']['ESFJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> S-Value: </span><span class="label"> F-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ESFJ'),
      ),
    ),
  ); 
  $form['tab_2']['second-type']['scores']['ESFP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> S-Value: </span><span class="label"> F-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ESFP'),
      ),
    ),
  );   
  $form['tab_2']['second-type']['scores']['ESTJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> S-Value: </span><span class="label"> T-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ESTJ'),
      ),
    ),
  ); 
  $form['tab_2']['second-type']['scores']['ESTP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> E-Value: </span><span class="label"> S-Value: </span><span class="label"> T-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ESTP'),
      ),
    ),
  ); 
  $form['tab_2']['second-type']['scores']['INFJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> N-Value: </span><span class="label"> F-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'INFJ'),
      ),
    ),
  );
  $form['tab_2']['second-type']['scores']['INFP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> N-Value: </span><span class="label"> F-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'INFP'),
      ),
    ),
  );  
  $form['tab_2']['second-type']['scores']['INTJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> N-Value: </span><span class="label"> T-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'INTJ'),
      ),
    ),
  );
  $form['tab_2']['second-type']['scores']['INTP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> N-Value: </span><span class="label"> T-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'INTP'),
      ),
    ),
  );  
  $form['tab_2']['second-type']['scores']['ISFJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> S-Value: </span><span class="label"> F-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ISFJ'),
      ),
    ),
  ); 
  $form['tab_2']['second-type']['scores']['ISFP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> S-Value: </span><span class="label"> F-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ISFP'),
      ),
    ),
  );   
  $form['tab_2']['second-type']['scores']['ISTJ'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> S-Value: </span><span class="label"> T-Value: </span><span class="label"> J-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ISTJ'),
      ),
    ),
  ); 
  $form['tab_2']['second-type']['scores']['ISTP'] = array(
    '#type' => 'item',
    '#markup' => '<span class="first-label"> I-Value: </span><span class="label"> S-Value: </span><span class="label"> T-Value: </span><span class="label"> P-Value: </span>',
     '#states' => array(
      'visible' => array(
        ':input[name="p_type2"]' => array('value' => 'ISTP'),
      ),
    ),
  );   
  $form['tab_2']['second-type']['scores']['ei_score2'] = array(
    '#type' => 'textfield',
    '#size' => 4, 
    '#maxlength' => 4,
    '#default_value' => $report->ei_score2,
  );
  $form['tab_2']['second-type']['scores']['ns_score2'] = array(
    '#type' => 'textfield',
    '#size' => 4, 
    '#maxlength' => 4,
    '#default_value' => $report->ns_score2,
  );
  $form['tab_2']['second-type']['scores']['ft_score2'] = array(
    '#type' => 'textfield',
    '#size' => 4, 
    '#maxlength' => 4,
    '#default_value' => $report->ft_score2,
  );
  $form['tab_2']['second-type']['scores']['jp_score2'] = array(
    '#type' => 'textfield',
    '#size' => 4, 
    '#maxlength' => 4,
    '#default_value' => $report->jp_score2,
  );   
// Tab 3 -------------------------------------------------------------------
  $form['tab_3'] = array(
    '#type' => 'fieldset',
    '#title' => 'Report Components',
    '#group' => 'tabs',
  );
  $form['tab_3']['components'] = array(
    '#type' => 'fieldset',
    '#title' => 'Select components',
  );
  $form['tab_3']['components']['both'] = array(
    '#type' => 'checkbox',
    '#title' => t('Both'),
    '#states' => array(
      'checked' => array(
        ':input[name="narrative"]' => array('checked' => TRUE),
        ':input[name="temperament"]' => array('checked' => TRUE),
      ),  
    ),
  );  
  $form['tab_3']['components']['narrative'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include narrative components'),
    '#states' => array(
      'checked' => array(
        array(':input[name="narrative"]' => array('checked' => TRUE)),
        array(':input[name="both"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->narrative,
  );
  $form['tab_3']['components']['temperament'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include temperament components'),
    '#states' => array(
      'checked' => array(
        array(':input[name="temperament"]' => array('checked' => TRUE)),
        array(':input[name="both"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->temperament,
  );  
  $form['tab_3']['categories'] = array(
    '#type' => 'fieldset',
    '#title' => 'Select Categories',
  );
  $form['tab_3']['categories']['all'] = array(
    '#type' => 'checkbox',
    '#title' => t('All'),
    '#states' => array(
      'checked' => array(
        ':input[name="cat_org"]' => array('checked' => TRUE),
        ':input[name="cat_lead"]' => array('checked' => TRUE),
        ':input[name="cat_com"]' => array('checked' => TRUE),
        ':input[name="cat_prob"]' => array('checked' => TRUE),
        ':input[name="cat_stress"]' => array('checked' => TRUE),
        ':input[name="cat_motive"]' => array('checked' => TRUE),
        ':input[name="cat_team"]' => array('checked' => TRUE),
        ':input[name="cat_learn"]' => array('checked' => TRUE),
        ':input[name="cat_growth"]' => array('checked' => TRUE),
      ),  
    ),
  );
  $form['tab_3']['categories']['cat_org'] = array(
    '#type' => 'checkbox',
    '#title' => t('Contributions to an organization'),
    '#states' => array(
      'checked' => array(
        array(':input[name="cat_org"]' => array('checked' => TRUE)),
        array(':input[name="all"]' => array('checked' => TRUE)),
      ),  
    ),  
    '#default_value' => $report->cat_org,
  );
  $form['tab_3']['categories']['cat_lead'] = array(
    '#type' => 'checkbox',
    '#title' => t('Leadership style'),
    '#states' => array(
      'checked' => array(
        array(':input[name="cat_lead"]' => array('checked' => TRUE)),
        array(':input[name="all"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->cat_lead,
  );
  $form['tab_3']['categories']['cat_com'] = array(
    '#type' => 'checkbox',
    '#title' => t('Communication style'),
    '#states' => array(
      'checked' => array(
        array(':input[name="cat_com"]' => array('checked' => TRUE)),
        array(':input[name="all"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->cat_com,
  );
  $form['tab_3']['categories']['cat_prob'] = array(
    '#type' => 'checkbox',
    '#title' => t('Problem solving & decision making'),
    '#states' => array(
      'checked' => array(
        array(':input[name="cat_prob"]' => array('checked' => TRUE)),
        array(':input[name="all"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->cat_prob,
  );
  $form['tab_3']['categories']['cat_stress'] = array(
    '#type' => 'checkbox',
    '#title' => t('Stress profile'),
    '#states' => array(
      'checked' => array(
        array(':input[name="cat_stress"]' => array('checked' => TRUE)),
        array(':input[name="all"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->cat_stress,
  );
  $form['tab_3']['categories']['cat_motive'] = array(
    '#type' => 'checkbox',
    '#title' => t('Motivators & demotivators'),
    '#states' => array(
      'checked' => array(
        array(':input[name="cat_motive"]' => array('checked' => TRUE)),
        array(':input[name="all"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->cat_motive,
  );
  $form['tab_3']['categories']['cat_team'] = array(
    '#type' => 'checkbox',
    '#title' => t('On a team'),
    '#states' => array(
      'checked' => array(
        array(':input[name="cat_team"]' => array('checked' => TRUE)),
        array(':input[name="all"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->cat_team,
  );
  $form['tab_3']['categories']['cat_learn'] = array(
    '#type' => 'checkbox',
    '#title' => t('Learning style'),
    '#states' => array(
      'checked' => array(
        array(':input[name="cat_learn"]' => array('checked' => TRUE)),
        array(':input[name="all"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->cat_learn,
  );
  $form['tab_3']['categories']['cat_growth'] = array(
    '#type' => 'checkbox',
    '#title' => t('Opportunities for growth'),
    '#states' => array(
      'checked' => array(
        array(':input[name="cat_growth"]' => array('checked' => TRUE)),
        array(':input[name="all"]' => array('checked' => TRUE)),
      ),  
    ),
    '#default_value' => $report->cat_growth,
  );  
// Tab 4  -------------------------------------------------------------------  
  $form['tab_4'] = array(
    '#type' => 'fieldset',
    '#title' => 'Review & Generate',
    '#group' => 'tabs',
  );

  // @todo Need current values display --------------------------------------
  $name = &$form_state['values']['fname1'];
  $form['tab_4']['complete_name'] = array(
    '#type' => 'item',
    '#title' => t('Name'),
    '#markup'=> $name,
  );

  $form['tab_4']['save_report'] = array(
    '#type' => 'checkbox',
    '#title' => t('Save this report to your History?'),
    '#default_value' => !empty($report->report_name) ? '1' : '0',
  );
  $form['tab_4']['report_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Unique name for this report'),
    '#states' => array(
      'visible' => array(
        ':input[name="save_report"]' => array('checked' => TRUE),
      ),  
    ),
    '#default_value' => check_plain($report->report_name),
    '#size' => 50,
    '#maxlength' => 255,
  );
  
  $form['tab_4']['actions'] = array('#type' => 'actions');
  $form['tab_4']['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('polaris_report_form_submit'),      
  );
  
  return $form;
}

/**
 * Form submit callback.
 */
function polaris_report_form_submit($form, &$form_state) {
  $report = $form['#report'];
  global $user;
  $date = $form_state['values']['date'];

  $report->report_name = $form_state['values']['report_name'];
  $report->uid = $user->uid;
  $report->score_type = $form_state['values']['score_type'];
  $report->report_type = $form_state['values']['report_type'];
  $report->date = sprintf('%4d-%02d-%02d', $date['year'], $date['month'], $date['day']);
  $report->fname1 = $form_state['values']['fname1'];
  $report->lname1 = $form_state['values']['lname1'];
  $report->org1 = $form_state['values']['org1'];
  $report->p_type1 = $form_state['values']['p_type1'];
  $report->ei_score1 = $form_state['values']['ei_score1'];
  $report->ns_score1 = $form_state['values']['ns_score1'];
  $report->ft_score1 = $form_state['values']['ft_score1'];
  $report->jp_score1 = $form_state['values']['jp_score1'];
  $report->fname2 = $form_state['values']['fname2'];
  $report->lname2 = $form_state['values']['lname2'];
  $report->org2 = $form_state['values']['org2'];
  $report->p_type2 = $form_state['values']['p_type2'];
  $report->ei_score2 = $form_state['values']['ei_score2'];
  $report->ns_score2 = $form_state['values']['ns_score2'];
  $report->ft_score2 = $form_state['values']['ft_score2'];
  $report->jp_score2 = $form_state['values']['jp_score2'];
  $report->narrative = $form_state['values']['narrative'];
  $report->temperament = $form_state['values']['temperament'];
  $report->cat_org = $form_state['values']['cat_org'];
  $report->cat_lead = $form_state['values']['cat_lead'];
  $report->cat_com = $form_state['values']['cat_com'];
  $report->cat_prob = $form_state['values']['cat_prob'];
  $report->cat_stress = $form_state['values']['cat_stress'];
  $report->cat_motive = $form_state['values']['cat_motive'];
  $report->cat_team = $form_state['values']['cat_team'];
  $report->cat_learn = $form_state['values']['cat_learn'];
  $report->cat_growth = $form_state['values']['cat_growth'];
    
  entity_get_controller('polarisreport')->save($report);
  
  $form_state['redirect'] = 'reports/list';
}
