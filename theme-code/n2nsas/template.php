<?php
/**
 * @file
 * Contains theme override functions and process & preprocess functions for n2nsas
 

function n2nsas_preprocess_page(&$variables) {
  if (isset($variables['node'])) {
  // Add node type template suggestions,  
  // If the node type is "blog" template suggestion is "page--blog.tpl.php".
   $variables['theme_hook_suggestions'][] = 'page__'. str_replace('_', '--', $variables['node']->type);
  }
  // Next two ifs remove unwanted tabs on blog pages.
  if (!empty($variables['node']) && $variables['node']->type == 'blog') { 
    n2nsas_removetab('Add child page', $variables); 
  }
  if (!empty($variables['node']) && $variables['node']->type == 'blog') { 
    n2nsas_removetab('View folio contents', $variables);
  }
  // Same to remove unwanted tabs on dashboard.
  if (!empty($variables['node']) && $variables['node']->type == 'dashboard') { 
    n2nsas_removetab('Add child page', $variables); 
  }
  if (!empty($variables['node']) && $variables['node']->type == 'dashboard') { 
    n2nsas_removetab('View folio contents', $variables);
  }
  // Finally on page.
  if (!empty($variables['node']) && $variables['node']->type == 'page') { 
    n2nsas_removetab('Add child page', $variables); 
  }
  if (!empty($variables['node']) && $variables['node']->type == 'page') { 
    n2nsas_removetab('View folio contents', $variables);
  }
}
*/

// Remove undesired local task tabs from primary tabs.
// See above in n2nsas_preprocess_page().
function n2nsas_removetab($label, &$variables) {
$i = 0;
if (is_array($variables['tabs']['#primary'])) {
foreach ($variables['tabs']['#primary'] as $primary_tab) {
if ($primary_tab['#link']['title'] == $label) {
unset($variables['tabs']['#primary'][$i]);
}
++$i;
}
}
	
}
