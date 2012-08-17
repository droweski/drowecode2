<?php

/**
 * @file
 * Include file for report queries and generation.
 */

/**
 * Function to assemble the type report info.
 */ 
function polarisreport_generate($report) {
// Field processing

  //score type marker
  switch ($report->score_type) {
    case "raw":
      $report->score_mark = '';
      break;
    case "percent":
      $report->score_mark = '%';
      break;
    case "tdi":
      $report->score_mark = '';
      break;
    case "ear":
      $report->score_mark = '';
      break;
  }
  //report author
  global $user;
  $report->author = $user->name;
  
// Subject One report info --------------------------------------
  // Narrative
  if ($report->narrative == 1) {
    $conditional = $report->p_type1;
    $column = 'field_p_type';
    $bundle = 'Narrative';
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Narrative intro
      $selected = 'field_nar_intro';
      $arry = $obj->$selected;
      $text = $arry['und'][0]['safe_value'];
      $report->narintro1 = $text;
      // Narrative text
      $selected = 'field_nar_text';
      $arry = $obj->$selected;
      $text = $arry['und'][0]['safe_value'];
      $report->nartext1 = $text;
    }
  } 
  // Temperament
  // find temp code from narrative table
  if ($report->temperament == 1) {
    $bundle = 'Narrative';
    $column = 'field_p_type';
    $conditional = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Temperament code
      $selected = 'field_temp_code';
      $arry = $obj->$selected;
      $t_code = $arry['und'][0]['safe_value'];
      $report->tempcode1 = $t_code;
      // Temperament text fields
      // Use t-code to find temperament values
      $bundle = 'Temperament';
      $column = 'field_temp_code';
      $conditional = $t_code;
      $query = new EntityFieldQuery();
        $query
        ->entityCondition('entity_type', 'tr_data')
        ->entityCondition('bundle', $bundle)
        ->fieldCondition($column, 'value', $conditional);
      $result = $query->execute();
      if (!empty($result['tr_data'])) {
        $key = array_keys($result['tr_data']);
        $index = $key[0];
        $ent = entity_load('tr_data', $key);
        $obj = $ent[$index];
        // Temperament intro
        $selected = 'field_temp_intro';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        $report->tempintro1 = $text;
        // Temperament text
        $selected = 'field_temp_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        $report->temptext1 = $text;
      }
    }
  }  
  // Category query ("org" id=1) -----------------------------
  // Test if category type is selected
  if ($report->cat_org == 1) {
    $bundle = 'Category';
    $column = 'field_cat_id';
    // Select for category id
    $conditional = 1;  // Category ID value
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Category name
      $selected = 'field_cat_name';
      $arry = $obj->$selected;
      $cat_name = $arry['und'][0]['safe_value'];
      $report->catname1 = $cat_name;
      // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $report->catdesc1 = $desc;
    }
    // Category data query -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 1;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line items
        $report->$value = $text;
      }  
    }
  }  
  // Category query ("lead" id=2) -----------------------------
  if ($report->cat_lead == 1) {
    $bundle = 'Category';
    $column = 'field_cat_id';
    // Select for category id
    $conditional = 2;  // Category ID value
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Category name
      $selected = 'field_cat_name';
      $arry = $obj->$selected;
      $cat_name = $arry['und'][0]['safe_value'];
      $report->catname2 = $cat_name;
      // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $report->catdesc2 = $desc;
    }
    // Category data query -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 2;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line items
        $report->$value = $text;
      }  
    }
  }   
  // Category query ("com" id=3) -----------------------------
  if ($report->cat_com == 1) {
    $bundle = 'Category';
    $column = 'field_cat_id';
    // Select for category id
    $conditional = 3;  // Category ID value
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Category name
      $selected = 'field_cat_name';
      $arry = $obj->$selected;
      $cat_name = $arry['und'][0]['safe_value'];
      $report->catname3 = $cat_name;
      // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $report->catdesc3 = $desc;
    }
    // Category data query  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 3;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line items
        $report->$value = $text;
      }  
    }
  }    
  // Category query ("prob" id=4) -----------------------------
  if ($report->cat_prob == 1) {
    $bundle = 'Category';
    $column = 'field_cat_id';
    // Select for category id
    $conditional = 4;  // Category ID value
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Category name
      $selected = 'field_cat_name';
      $arry = $obj->$selected;
      $cat_name = $arry['und'][0]['safe_value'];
      $report->catname4 = $cat_name;
      // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $report->catdesc4 = $desc;
    }
    // Category data query  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 4;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line items
        $report->$value = $text;
      }  
    }
  }    
  // Category query ("stress" id=5) -----------------------------
  if ($report->cat_stress == 1) {
    $bundle = 'Category';
    $column = 'field_cat_id';
    // Select for category id
    $conditional = 5;  // Category ID value
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Category name
      $selected = 'field_cat_name';
      $arry = $obj->$selected;
      $cat_name = $arry['und'][0]['safe_value'];
      $report->catname5 = $cat_name;
      // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $report->catdesc5 = $desc;
    }
    // Category data query  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 5;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line items
        $report->$value = $text;
      }  
    }
  }
  // Category query ("motive" id=6) -----------------------------
  if ($report->cat_motive == 1) {
    $bundle = 'Category';
    $column = 'field_cat_id';
    // Select for category id
    $conditional = 6;  // Category ID value
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Category name
      $selected = 'field_cat_name';
      $arry = $obj->$selected;
      $cat_name = $arry['und'][0]['safe_value'];
      $report->catname6 = $cat_name;
      // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $report->catdesc6 = $desc;
    }
    // Category data query  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 6;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line items
        $report->$value = $text;
      }  
    }
  }    
  // Category query ("team" id=7) -----------------------------
  if ($report->cat_team == 1) {
    $bundle = 'Category';
    $column = 'field_cat_id';
    // Select for category id
    $conditional = 7;  // Category ID value
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Category name
      $selected = 'field_cat_name';
      $arry = $obj->$selected;
      $cat_name = $arry['und'][0]['safe_value'];
      $report->catname7 = $cat_name;
      // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $report->catdesc7 = $desc;
    }
    // Category data query  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 7;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line items
        $report->$value = $text;
      }  
    }
  }    
  // Category query ("learn" id=8) -----------------------------
  if ($report->cat_learn == 1) {
    $bundle = 'Category';
    $column = 'field_cat_id';
    // Select for category id
    $conditional = 8;  // Category ID value
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Category name
      $selected = 'field_cat_name';
      $arry = $obj->$selected;
      $cat_name = $arry['und'][0]['safe_value'];
      $report->catname8 = $cat_name;
      // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $report->catdesc8 = $desc;
    }
    // Category data query  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 8;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line items
        $report->$value = $text;
      }  
    }
  }  
  // Category query ("growth" id=9) -----------------------------
  if ($report->cat_growth == 1) {
    $bundle = 'Category';
    $column = 'field_cat_id';
    // Select for category id
    $conditional = 9;  // Category ID value
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Category name
      $selected = 'field_cat_name';
      $arry = $obj->$selected;
      $cat_name = $arry['und'][0]['safe_value'];
      $report->catname9 = $cat_name;
      // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $report->catdesc9 = $desc;
    }
    // Category data query  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 9;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type1;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line items
        $report->$value = $text;
      }  
    }
  }  
  
  /**
  * Type One Report node creation.
  */
  if ($report->report_type == '1') {
    $report->report_type = 'Single subject';
    $report->name1 = $report->fname1 . ' ' . $report->lname1;
    
    $node = new stdClass();
    $node->type = 'reportview1';
    $node->title = 'Polaris Report Title Area';
    $node->language = LANGUAGE_NONE;

    $path = 'reports/print/' . $report->uuid;
    $node->path = array('alias' => $path);

    node_object_prepare($node);

    $node->field_report_name[$node->language][0]['value'] = $report->report_name;
    $node->field_report_name[$node->language][0]['format'] = 'full_html';

    $node->field_report_type[$node->language][0]['value'] = $report->report_type;
    $node->field_report_type[$node->language][0]['format'] = 'full_html';  
  
    $node->field_report_date[$node->language][0]['value'] = $report->date;
    $node->field_report_date[$node->language][0]['format'] = 'full_html';
  
    $node->field_report_org[$node->language][0]['value'] = $report->org1;
    $node->field_report_org[$node->language][0]['format'] = 'full_html';
    
    $node->field_report_scoretype[$node->language][0]['value'] = $report->score_type;
    $node->field_report_scoretype[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_fname1[$node->language][0]['value'] = $report->fname1;
    $node->field_report_fname1[$node->language][0]['format'] = 'full_html';
    
    if (isset($report->lname1))  {
      $node->field_report_lname1[$node->language][0]['value'] = $report->lname1;
      $node->field_report_lname1[$node->language][0]['format'] = 'full_html';
    }  
    
    $node->field_report_ptype1[$node->language][0]['value'] = $report->p_type1;
    $node->field_report_ptype1[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_ei1[$node->language][0]['value'] = $report->ei_score1;
    $node->field_report_ei1[$node->language][0]['format'] = 'full_html';  
      
    $node->field_report_ns1[$node->language][0]['value'] = $report->ns_score1;
    $node->field_report_ns1[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_ft1[$node->language][0]['value'] = $report->ft_score1;
    $node->field_report_ft1[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_jp1[$node->language][0]['value'] = $report->jp_score1;
    $node->field_report_jp1[$node->language][0]['format'] = 'full_html';  
      
    if (isset($report->narintro1))  {
      $node->field_report_narintro1[$node->language][0]['value'] = $report->narintro1;
      $node->field_report_narintro1[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->nartext1))  {
      $node->field_report_nartext1[$node->language][0]['value'] = $report->nartext1;
      $node->field_report_nartext1[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->tempintro1))  {
      $node->field_report_tempintro1[$node->language][0]['value'] = $report->tempintro1;
      $node->field_report_tempintro1[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->temptext1))  {
      $node->field_report_temptext1[$node->language][0]['value'] = $report->temptext1;
      $node->field_report_temptext1[$node->language][0]['format'] = 'full_html';
    }
    
    if (isset($report->catdesc1))  {
      $node->field_report_catdesc1[$node->language][0]['value'] = $report->catdesc1;
      $node->field_report_catdesc1[$node->language][0]['format'] = 'full_html';  
    }
    
    if (isset($report->catdesc2))  {
      $node->field_report_catdesc2[$node->language][0]['value'] = $report->catdesc2;
      $node->field_report_catdesc2[$node->language][0]['format'] = 'full_html';       
    }
    
    if (isset($report->catdesc3))  {
      $node->field_report_catdesc3[$node->language][0]['value'] = $report->catdesc3;
      $node->field_report_catdesc3[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc4))  {
      $node->field_report_catdesc4[$node->language][0]['value'] = $report->catdesc4;
      $node->field_report_catdesc4[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->catdesc5))  {
      $node->field_report_catdesc5[$node->language][0]['value'] = $report->catdesc5;
      $node->field_report_catdesc5[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc6))  {
      $node->field_report_catdesc6[$node->language][0]['value'] = $report->catdesc6;
      $node->field_report_catdesc6[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc7))  {
      $node->field_report_catdesc7[$node->language][0]['value'] = $report->catdesc7;
      $node->field_report_catdesc7[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc8))  {
      $node->field_report_catdesc8[$node->language][0]['value'] = $report->catdesc8;
      $node->field_report_catdesc8[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc9))  {
      $node->field_report_catdesc9[$node->language][0]['value'] = $report->catdesc9;
      $node->field_report_catdesc9[$node->language][0]['format'] = 'full_html';
    }
  
    node_save($node);

    $report->nid = $node->nid;
  
    drupal_goto($path); 

  }
  
  /**
  * Type Two report generation
  */
  
  // Subject 2 report info --------------------------------------
  // Narrative
  if ($report->narrative == 1) {
    $conditional = $report->p_type2;
    $column = 'field_p_type';
    $bundle = 'Narrative';
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Narrative intro
      $selected = 'field_nar_intro';
      $arry = $obj->$selected;
      $text = $arry['und'][0]['safe_value'];
      $report->narintro2 = $text;
      // Narrative text
      $selected = 'field_nar_text';
      $arry = $obj->$selected;
      $text = $arry['und'][0]['safe_value'];
      $report->nartext2 = $text;
    }
  } 
  // Temperament
  // find temp code from narrative table
  if ($report->temperament == 1) {
    $bundle = 'Narrative';
    $column = 'field_p_type';
    $conditional = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column, 'value', $conditional);
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $key = array_keys($result['tr_data']);
      $index = $key[0];
      $ent = entity_load('tr_data', $key);
      $obj = $ent[$index];
      // Temperament code
      $selected = 'field_temp_code';
      $arry = $obj->$selected;
      $t_code = $arry['und'][0]['safe_value'];
      $report->tempcode2 = $t_code;
      // Temperament text fields
      // Use t-code to find temperament values
      $bundle = 'Temperament';
      $column = 'field_temp_code';
      $conditional = $t_code;
      $query = new EntityFieldQuery();
        $query
        ->entityCondition('entity_type', 'tr_data')
        ->entityCondition('bundle', $bundle)
        ->fieldCondition($column, 'value', $conditional);
      $result = $query->execute();
      if (!empty($result['tr_data'])) {
        $key = array_keys($result['tr_data']);
        $index = $key[0];
        $ent = entity_load('tr_data', $key);
        $obj = $ent[$index];
        // Temperament intro
        $selected = 'field_temp_intro';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        $report->tempintro2 = $text;
        // Temperament text
        $selected = 'field_temp_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        $report->temptext2 = $text;
      }
    }
  }  
  // Category data query ("org" id=1) -----------------------------
  if ($report->cat_org == 1) {
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 1; //Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line item
        $report->$value = $text;
      }  
    }   
  }
  // Category data query ("lead" id=2) -----------------------------
  if ($report->cat_lead == 1) {
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 2; //Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line item
        $report->$value = $text;
      }  
    }   
  }
  // Category data query ("com" id=3) -----------------------------
  if ($report->cat_com == 1) {
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 3; //Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line item
        $report->$value = $text;
      }  
    }   
  } 
  // Category data query ("prob" id=4) -----------------------------
  if ($report->cat_prob == 1) {
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 4; //Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line item
        $report->$value = $text;
      }  
    }   
  }
  // Category data query ("stress" id=5) -----------------------------
  if ($report->cat_stress == 1) {
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 5; //Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line item
        $report->$value = $text;
      }  
    }   
  }
  // Category data query ("motive" id=6) -----------------------------
  if ($report->cat_motive == 1) {
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 6; //Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line item
        $report->$value = $text;
      }  
    }   
  }
  // Category data query ("team" id=7) -----------------------------
  if ($report->cat_team == 1) {
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 7; //Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line item
        $report->$value = $text;
      }  
    }
  }  
  // Category data query ("learn" id=8) -----------------------------
  if ($report->cat_learn == 1) {
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 8; //Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line item
        $report->$value = $text;
      }  
    }   
  }
  // Category query ("growth" id=9) -----------------------------
  if ($report->cat_growth == 1) {
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 9; //Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $report->p_type2;
    $query = new EntityFieldQuery();
      $query
      ->entityCondition('entity_type', 'tr_data')
      ->entityCondition('bundle', $bundle)
      ->fieldCondition($column1, 'value', $conditional1)
      ->fieldCondition($column2, 'value', $conditional2)
      ->fieldOrderBy('field_cat_data_so','value', 'ASC');
    $result = $query->execute();
    if (!empty($result['tr_data'])) {
      $keys = array_keys($result['tr_data']);
      // Iterate thru values  
      foreach($keys as $key => $value) {
        $ent = entity_load('tr_data', $keys);
        $obj = $ent[$value];
        $selected = 'field_cat_data_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        // Category line item
        $report->$value = $text;
      }  
    }   
  }

  /**
  * Type TWO report node creation
  */
  if ($report->report_type == '121') {
    
    $report->report_type = 'One to One';
    $report->name1 = $report->fname1 . ' ' . $report->lname1;
    $report->name2 = $report->fname2 . ' ' . $report->lname2;
    
    $node = new stdClass();
    $node->type = 'reportview2';
    $node->title = 'Polaris Report Title Area';
    $node->language = LANGUAGE_NONE;

    $path = 'reports/print/' . $report->uuid;
    $node->path = array('alias' => $path);

    node_object_prepare($node);

    $node->field_report_name[$node->language][0]['value'] = $report->report_name;
    $node->field_report_name[$node->language][0]['format'] = 'full_html';

    $node->field_report_type[$node->language][0]['value'] = $report->report_type;
    $node->field_report_type[$node->language][0]['format'] = 'full_html';  
  
    $node->field_report_date[$node->language][0]['value'] = $report->date;
    $node->field_report_date[$node->language][0]['format'] = 'full_html';
  
    $node->field_report_org[$node->language][0]['value'] = $report->org1;
    $node->field_report_org[$node->language][0]['format'] = 'full_html';
    
    $node->field_report_scoretype[$node->language][0]['value'] = $report->score_type;
    $node->field_report_scoretype[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_fname1[$node->language][0]['value'] = $report->fname1;
    $node->field_report_fname1[$node->language][0]['format'] = 'full_html';
    
    if (isset($report->lname1))  {
      $node->field_report_lname1[$node->language][0]['value'] = $report->lname1;
      $node->field_report_lname1[$node->language][0]['format'] = 'full_html';
    }  
    
    $node->field_report_ptype1[$node->language][0]['value'] = $report->p_type1;
    $node->field_report_ptype1[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_ei1[$node->language][0]['value'] = $report->ei_score1;
    $node->field_report_ei1[$node->language][0]['format'] = 'full_html';  
      
    $node->field_report_ns1[$node->language][0]['value'] = $report->ns_score1;
    $node->field_report_ns1[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_ft1[$node->language][0]['value'] = $report->ft_score1;
    $node->field_report_ft1[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_jp1[$node->language][0]['value'] = $report->jp_score1;
    $node->field_report_jp1[$node->language][0]['format'] = 'full_html';  
   
    if (isset($report->narintro1))  {
      $node->field_report_narintro1[$node->language][0]['value'] = $report->narintro1;
      $node->field_report_narintro1[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->nartext1))  {
      $node->field_report_nartext1[$node->language][0]['value'] = $report->nartext1;
      $node->field_report_nartext1[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->tempintro1))  {
      $node->field_report_tempintro1[$node->language][0]['value'] = $report->tempintro1;
      $node->field_report_tempintro1[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->temptext1))  {
      $node->field_report_temptext1[$node->language][0]['value'] = $report->temptext1;
      $node->field_report_temptext1[$node->language][0]['format'] = 'full_html';
    }
    
    // second subject -------------------------
    $node->field_report_fname2[$node->language][0]['value'] = $report->fname2;
    $node->field_report_fname2[$node->language][0]['format'] = 'full_html';
    
    if (isset($report->lname2))  {
      $node->field_report_lname2[$node->language][0]['value'] = $report->lname2;
      $node->field_report_lname2[$node->language][0]['format'] = 'full_html';
    } 
    
    $node->field_report_ptype2[$node->language][0]['value'] = $report->p_type2;
    $node->field_report_ptype2[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_ei2[$node->language][0]['value'] = $report->ei_score2;
    $node->field_report_ei2[$node->language][0]['format'] = 'full_html';  
      
    $node->field_report_ns2[$node->language][0]['value'] = $report->ns_score2;
    $node->field_report_ns2[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_ft2[$node->language][0]['value'] = $report->ft_score2;
    $node->field_report_ft2[$node->language][0]['format'] = 'full_html';
      
    $node->field_report_jp2[$node->language][0]['value'] = $report->jp_score2;
    $node->field_report_jp2[$node->language][0]['format'] = 'full_html'; 
        
    if (isset($report->narintro2))  {
      $node->field_report_narintro2[$node->language][0]['value'] = $report->narintro2;
      $node->field_report_narintro2[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->nartext2))  {
      $node->field_report_nartext2[$node->language][0]['value'] = $report->nartext2;
      $node->field_report_nartext2[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->tempintro2))  {
      $node->field_report_tempintro2[$node->language][0]['value'] = $report->tempintro2;
      $node->field_report_tempintro2[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->temptext2))  {
      $node->field_report_temptext1[$node->language][0]['value'] = $report->temptext2;
      $node->field_report_temptext1[$node->language][0]['format'] = 'full_html';
    }
    // ---------------------------------------

    if (isset($report->catdesc1))  {
      $node->field_report_catdesc1[$node->language][0]['value'] = $report->catdesc1;
      $node->field_report_catdesc1[$node->language][0]['format'] = 'full_html';  
    }
    
    if (isset($report->catdesc2))  {
      $node->field_report_catdesc2[$node->language][0]['value'] = $report->catdesc2;
      $node->field_report_catdesc2[$node->language][0]['format'] = 'full_html';       
    }
    
    if (isset($report->catdesc3))  {
      $node->field_report_catdesc3[$node->language][0]['value'] = $report->catdesc3;
      $node->field_report_catdesc3[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc4))  {
      $node->field_report_catdesc4[$node->language][0]['value'] = $report->catdesc4;
      $node->field_report_catdesc4[$node->language][0]['format'] = 'full_html';
    }
      
    if (isset($report->catdesc5))  {
      $node->field_report_catdesc5[$node->language][0]['value'] = $report->catdesc5;
      $node->field_report_catdesc5[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc6))  {
      $node->field_report_catdesc6[$node->language][0]['value'] = $report->catdesc6;
      $node->field_report_catdesc6[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc7))  {
      $node->field_report_catdesc7[$node->language][0]['value'] = $report->catdesc7;
      $node->field_report_catdesc7[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc8))  {
      $node->field_report_catdesc8[$node->language][0]['value'] = $report->catdesc8;
      $node->field_report_catdesc8[$node->language][0]['format'] = 'full_html';
    }

    if (isset($report->catdesc9))  {
      $node->field_report_catdesc9[$node->language][0]['value'] = $report->catdesc9;
      $node->field_report_catdesc9[$node->language][0]['format'] = 'full_html';
    }
  
    node_save($node);

    $report->nid = $node->nid;
  
    drupal_goto($path); 
  }
}

