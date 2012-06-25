<?php

/**
 * @file
 * Include file for report query.
 */  

/**
 * Function to display the type report info.
 */
function polaris_report_generate($entity, $view_mode = 'view') {
  $entity->content = array(
    '#view_mode' => $view_mode,
  );
  $entity->content['header'] = array(
    '#type' => 'item',
    '#title' => t('Header'),
    '#markup' => t('New type report form.'),
  );
  $entity->content['uid'] = array(
    '#type' => 'item',
    '#title' => t('User ID'),
    '#markup' => $entity->uid,
  );
//  $entity->content['created'] = array(
//    '#type' => 'item',
//    '#title' => t('Created date'),
//    '#markup' => format_date($entity->created),
//  );
  $entity->content['report_type'] = array(
    '#type' => 'item',
    '#title' => t('Report Type'),
    '#markup' => $entity->report_type,
  );
  $entity->content['score_type'] = array(
    '#type' => 'item',
    '#title' => t('Score Format'),
    '#markup' => $entity->score_type,
  );
// Subject 1 basic info -------------------------------------------
  $entity->content['fname1'] = array(
    '#type' => 'item',
    '#title' => t('First name'),
    '#markup' => $entity->fname1,
  );  
  $entity->content['lname1'] = array(
    '#type' => 'item',
    '#title' => t('Last name'),
    '#markup' => $entity->lname1,
  );
  $entity->content['org1'] = array(
    '#type' => 'item',
    '#title' => t('Organization'),
    '#markup' => $entity->org1,
  ); 
  $entity->content['p_type1'] = array(
    '#type' => 'item',
    '#title' => t('Personality type'),
    '#markup' => $entity->p_type1,
  );
  $entity->content['ei_score1'] = array(
    '#type' => 'item',
    '#title' => t('ei_score1'),
    '#markup' => $entity->ei_score1,
  );
  $entity->content['ns_score1'] = array(
    '#type' => 'item',
    '#title' => t('ns_score1'),
    '#markup' => $entity->ns_score1,
  );
  $entity->content['ft_score1'] = array(
    '#type' => 'item',
    '#title' => t('ft_score1'),
    '#markup' => $entity->ft_score1,
  );
  $entity->content['jp_score1'] = array(
    '#type' => 'item',
    '#title' => t('jp_score1'),
    '#markup' => $entity->jp_score1,
  );
// Subject 1 text fields --------------------------------------
// Narrative
  if ($entity->narrative == 1) {
    $conditional = $entity->p_type1;
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
      $entity->content['narrative_intro_1'] = array(
        '#type' => 'item',
        '#title' => t('narrative intro 1'),
        '#markup' => $text,
      );
// Narrative text
      $selected = 'field_nar_text';
      $arry = $obj->$selected;
      $text = $arry['und'][0]['safe_value'];
      $entity->content['narrative_text_1'] = array(
        '#type' => 'item',
        '#title' => t('narrative text 1'),
        '#markup' => $text,
      );
    }
  } 
// Temperament field  
  $entity->content['temperament'] = array(
    '#type' => 'item',
    '#title' => t('temperament'),
    '#markup' => $entity->temperament,
  );
// Temperament query
  // find temp code from narrative table
  if ($entity->temperament == 1) {
    $bundle = 'Narrative';
    $column = 'field_p_type';
    $conditional = $entity->p_type1;
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
      $entity->content['temp_code_1'] = array(
        '#type' => 'item',
        '#title' => t('temp code 1'),
        '#markup' => $t_code,
      );
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
        $entity->content['temperament_intro_1'] = array(
          '#type' => 'item',
          '#title' => t('temperament intro 1'),
          '#markup' => $text,
        );
// Temperament text
        $selected = 'field_temp_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        $entity->content['temperament_text_1'] = array(
          '#type' => 'item',
          '#title' => t('temperament text 1'),
          '#markup' => $text,
        );
      }
    }
  }  

// Subject 2 basic info ------------------------------------------- 
  if ($entity->report_type == '121') {
    $entity->content['fname2'] = array(
      '#type' => 'item',
      '#title' => t('fname2'),
      '#markup' => $entity->fname2,
    );
    $entity->content['lname2'] = array(
      '#type' => 'item',
      '#title' => t('lname2'),
      '#markup' => $entity->lname2,
    );
    $entity->content['org2'] = array(
      '#type' => 'item',
      '#title' => t('org2'),
      '#markup' => $entity->org2,
    );
    $entity->content['p_type2'] = array(
      '#type' => 'item',
      '#title' => t('Personality type 2'),
      '#markup' => $entity->p_type2,
    );
    $entity->content['ei_score2'] = array(
      '#type' => 'item',
      '#title' => t('ei_score2'),
      '#markup' => $entity->ei_score2,
    );
    $entity->content['ns_score2'] = array(
      '#type' => 'item',
      '#title' => t('ns_score2'),
      '#markup' => $entity->ns_score2,
    );
    $entity->content['ft_score2'] = array(
      '#type' => 'item',
      '#title' => t('ft_score2'),
      '#markup' => $entity->ft_score2,
    );
    $entity->content['jp_score2'] = array(
      '#type' => 'item',
      '#title' => t('jp_score2'),
      '#markup' => $entity->jp_score2,
    );
  }
// Subject 2 text fields --------------------------------------
if ($entity->report_type == '121') {
  // Narrative
  if ($entity->narrative == 1) {
    $conditional = $entity->p_type2;
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
      $entity->content['narrative_intro_2'] = array(
        '#type' => 'item',
        '#title' => t('narrative intro 2'),
        '#markup' => $text,
      );
// Narrative text
      $selected = 'field_nar_text';
      $arry = $obj->$selected;
      $text = $arry['und'][0]['safe_value'];
      $entity->content['narrative_text_2'] = array(
        '#type' => 'item',
        '#title' => t('narrative text 2'),
        '#markup' => $text,
      );
    }
  } 
// Temperament field  
  $entity->content['temperament'] = array(
    '#type' => 'item',
    '#title' => t('temperament'),
    '#markup' => $entity->temperament,
  );
// Temperament query
  // find temp code from narrative table
  if ($entity->temperament == 1) {
    $bundle = 'Narrative';
    $column = 'field_p_type';
    $conditional = $entity->p_type2;
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
      $entity->content['temp_code_2'] = array(
        '#type' => 'item',
        '#title' => t('temp code 2'),
        '#markup' => $t_code,
      );
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
        $entity->content['temperament_intro_2'] = array(
          '#type' => 'item',
          '#title' => t('temperament intro 2'),
          '#markup' => $text,
        );
// Temperament text
        $selected = 'field_temp_text';
        $arry = $obj->$selected;
        $text = $arry['und'][0]['safe_value'];
        $entity->content['temperament_text_2'] = array(
          '#type' => 'item',
          '#title' => t('temperament text 2'),
          '#markup' => $text,
        );
      }
    }
  }  
}
// Category query ("org" id=1) -----------------------------
  // Test if category type is selected
  if ($entity->cat_org == 1) {
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
      $entity->content['cat_name_1'] = array(
        '#type' => 'item',
        '#markup' => $cat_name,
      );
    // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $entity->content['cat_desc_1'] = array(
        '#type' => 'item',
        '#markup' => $desc,
      );
    }
  // Category data query - subject 1  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 1;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $entity->p_type1;
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
        $entity->content[$value] = array(
          '#type' => 'item',
          '#markup' => $text,
        );
      }  
    }
  // Category data query - subject 2  -----------------------------
    if ($entity->report_type == '121') {
      $bundle = 'category_data';
      $column1 = 'field_cat_id';
      $conditional1 = 1; //Category ID value
      $column2 = 'field_p_type';
      $conditional2 = $entity->p_type2;
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
          $entity->content[$value] = array(
            '#type' => 'item',
            '#markup' => $text,
          );
        }  
      }   
    }
  }
// Category query ("lead" id=2) ---------------------------
  // Test if category type is selected
  if ($entity->cat_lead == 1) {
    $bundle = 'category';
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
      $entity->content['cat_name_2'] = array(
        '#type' => 'item',
        '#markup' => $cat_name,
      );
 // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $entity->content['cat_desc_2'] = array(
        '#type' => 'item',
        '#markup' => $desc,
      );     
    }
  // Category data query - subject 1  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 2;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $entity->p_type1;
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
        $id = '$value' . '-1';
        $entity->content[$id] = array(
          '#type' => 'item',
          '#markup' => $text,
        );
      }  
    }
  // Category data query - subject 2  -----------------------------
    if ($entity->report_type == '121') {
      $bundle = 'category_data';
      $column1 = 'field_cat_id';
      $conditional1 = 2; //Category ID value
      $column2 = 'field_p_type';
      $conditional2 = $entity->p_type2;
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
          $entity->content[$value] = array(
            '#type' => 'item',
            '#markup' => $text,
          );
        }  
      }   
    }
  }
// Category query ("com" id=3) ---------------------------
  // Test if category type is selected
  if ($entity->cat_com == 1) {
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
      $entity->content['cat_name_3'] = array(
        '#type' => 'item',
        '#markup' => $cat_name,
      );
 // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $entity->content['cat_desc_3'] = array(
        '#type' => 'item',
        '#markup' => $desc,
      );     
    }
 // Category data query - subject 1  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 3;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $entity->p_type1;
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
        $entity->content[$value] = array(
          '#type' => 'item',
          '#markup' => $text,
        );
      }  
    }
  // Category data query - subject 2  -----------------------------
    if ($entity->report_type == '121') {
      $bundle = 'category_data';
      $column1 = 'field_cat_id';
      $conditional1 = 3; //Category ID value
      $column2 = 'field_p_type';
      $conditional2 = $entity->p_type2;
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
          $entity->content[$value] = array(
            '#type' => 'item',
            '#markup' => $text,
          );
        }  
      }   
    }
  }
// Category query ("prob" id=4) ---------------------------
  // Test if category type is selected
  if ($entity->cat_prob == 1) {
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
      $entity->content['cat_name_4'] = array(
        '#type' => 'item',
        '#markup' => $cat_name,
      );
 // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $entity->content['cat_desc_4'] = array(
        '#type' => 'item',
        '#markup' => $desc,
      );     
    }
 // Category data query - subject 1  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 4;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $entity->p_type1;
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
        $entity->content[$value] = array(
          '#type' => 'item',
          '#markup' => $text,
        );
      }  
    }
  // Category data query - subject 2  -----------------------------
    if ($entity->report_type == '121') {
      $bundle = 'category_data';
      $column1 = 'field_cat_id';
      $conditional1 = 4; //Category ID value
      $column2 = 'field_p_type';
      $conditional2 = $entity->p_type2;
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
          $entity->content[$value] = array(
            '#type' => 'item',
            '#markup' => $text,
          );
        }  
      }   
    }
  }
// Category query ("stress" id=5) ---------------------------
  // Test if category type is selected
  if ($entity->cat_stress == 1) {
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
      $entity->content['cat_name_5'] = array(
        '#type' => 'item',
        '#markup' => $cat_name,
      );
 // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $entity->content['cat_desc_5'] = array(
        '#type' => 'item',
        '#markup' => $desc,
      );     
    }
 // Category data query - subject 1  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 5;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $entity->p_type1;
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
        $entity->content[$value] = array(
          '#type' => 'item',
          '#markup' => $text,
        );
      }  
    }
  // Category data query - subject 2  -----------------------------
    if ($entity->report_type == '121') {
      $bundle = 'category_data';
      $column1 = 'field_cat_id';
      $conditional1 = 5; //Category ID value
      $column2 = 'field_p_type';
      $conditional2 = $entity->p_type2;
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
          $entity->content[$value] = array(
            '#type' => 'item',
            '#markup' => $text,
          );
        }  
      }   
    }
  }
// Category query ("motive" id=6) ---------------------------
  // Test if category type is selected
  if ($entity->cat_motive == 1) {
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
      $entity->content['cat_name_6'] = array(
        '#type' => 'item',
        '#markup' => $cat_name,
      );
 // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $entity->content['cat_desc_6'] = array(
        '#type' => 'item',
        '#markup' => $desc,
      );     
    }
 // Category data query - subject 1  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 6;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $entity->p_type1;
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
        $entity->content[$value] = array(
          '#type' => 'item',
          '#markup' => $text,
        );
      }  
    }
  // Category data query - subject 2  -----------------------------
    if ($entity->report_type == '121') {
      $bundle = 'category_data';
      $column1 = 'field_cat_id';
      $conditional1 = 6; //Category ID value
      $column2 = 'field_p_type';
      $conditional2 = $entity->p_type2;
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
          $entity->content[$value] = array(
            '#type' => 'item',
            '#markup' => $text,
          );
        }  
      }   
    }
  }
// Category query ("team" id=7) ---------------------------
  // Test if category type is selected
  if ($entity->cat_team == 1) {
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
      $entity->content['cat_name_7'] = array(
        '#type' => 'item',
        '#markup' => $cat_name,
      );
 // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $entity->content['cat_desc_7'] = array(
        '#type' => 'item',
        '#markup' => $desc,
      );     
    }
 // Category data query - subject 1  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 7;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $entity->p_type1;
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
        $entity->content[$value] = array(
          '#type' => 'item',
          '#markup' => $text,
        );
      }  
    }
  // Category data query - subject 2  -----------------------------
    if ($entity->report_type == '121') {
      $bundle = 'category_data';
      $column1 = 'field_cat_id';
      $conditional1 = 7; //Category ID value
      $column2 = 'field_p_type';
      $conditional2 = $entity->p_type2;
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
          $entity->content[$value] = array(
            '#type' => 'item',
            '#markup' => $text,
          );
        }  
      }   
    }
  }
// Category query ("learn" id=8) ---------------------------
  // Test if category type is selected
  if ($entity->cat_learn == 1) {
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
      $entity->content['cat_name_8'] = array(
        '#type' => 'item',
        '#markup' => $cat_name,
      );
 // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $entity->content['cat_desc_8'] = array(
        '#type' => 'item',
        '#markup' => $desc,
      );     
    }
 // Category data query - subject 1  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 8;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $entity->p_type1;
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
        $entity->content[$value] = array(
          '#type' => 'item',
          '#markup' => $text,
        );
      }  
    }
  // Category data query - subject 2  -----------------------------
    if ($entity->report_type == '121') {
      $bundle = 'category_data';
      $column1 = 'field_cat_id';
      $conditional1 = 8; //Category ID value
      $column2 = 'field_p_type';
      $conditional2 = $entity->p_type2;
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
          $entity->content[$value] = array(
            '#type' => 'item',
            '#markup' => $text,
          );
        }  
      }   
    }
  }
// Category query ("growth" id=9) ---------------------------
  // Test if category type is selected
  if ($entity->cat_growth == 1) {
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
      $entity->content['cat_name_9'] = array(
        '#type' => 'item',
        '#markup' => $cat_name,
      );
 // Category description
      $selected = 'field_cat_desc';
      $arry = $obj->$selected;
      $desc = $arry['und'][0]['safe_value'];
      $entity->content['cat_desc_9'] = array(
        '#type' => 'item',
        '#markup' => $desc,
      );     
    }
 // Category data query - subject 1  -----------------------------
    $bundle = 'category_data';
    $column1 = 'field_cat_id';
    $conditional1 = 9;  // Category ID value
    $column2 = 'field_p_type';
    $conditional2 = $entity->p_type1;
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
        $entity->content[$value] = array(
          '#type' => 'item',
          '#markup' => $text,
        );
      }  
    }
  // Category data query - subject 2  -----------------------------
    if ($entity->report_type == '121') {
      $bundle = 'category_data';
      $column1 = 'field_cat_id';
      $conditional1 = 9; //Category ID value
      $column2 = 'field_p_type';
      $conditional2 = $entity->p_type2;
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
          $entity->content[$value] = array(
            '#type' => 'item',
            '#markup' => $text,
          );
        }  
      }   
    }
   }  
 // $type = 'polaris_report';
 // drupal_alter(array('polaris_report_view', 'entity_view'), $entity->content, $type); 
  
  return $entity->content;
}