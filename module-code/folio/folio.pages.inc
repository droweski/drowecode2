<?php

/**
 * @file
 * User page callbacks for the folio module.
 */

/**
 * Menu callback; prints a listing of all folios.
 */
function folio_render() {
  $folio_list = array();
  foreach (folio_get_folios() as $folio) {
    $folio_list[] = l($folio['title'], $folio['href'], $folio['options']);
  }

  return theme('item_list', array('items' => $folio_list));
}

/**
 * Menu callback; Generates various representation of a folio page and its children.
 *
 * The function delegates the generation of output to helper functions.
 * The function name is derived by prepending 'folio_export_' to the
 * given output type. So, e.g., a type of 'html' results in a call to
 * the function folio_export_html().
 *
 * @param $type
 *   A string encoding the type of output requested. The following
 *   types are currently supported in folio module:
 *
 *   - html: HTML (printer friendly output)
 *
 *   Other types may be supported in contributed modules.
 * @param $nid
 *   An integer representing the node id (nid) of the node to export
 * @return
 *   A string representing the node and its children in the folio hierarchy
 *   in a format determined by the $type parameter.
 */
function folio_export($type, $nid) {
  $type = drupal_strtolower($type);

  $export_function = 'folio_export_' . $type;

  if (function_exists($export_function)) {
    print call_user_func($export_function, $nid);
  }
  else {
    drupal_set_message(t('Unknown export format.'));
    drupal_not_found();
  }
}

/**
 * This function is called by folio_export() to generate HTML for export.
 *
 * The given node is /embedded to its absolute depth in a top level
 * section/. For example, a child node with depth 2 in the hierarchy
 * is contained in (otherwise empty) &lt;div&gt; elements
 * corresponding to depth 0 and depth 1. This is intended to support
 * WYSIWYG output - e.g., level 3 sections always look like level 3
 * sections, no matter their depth relative to the node selected to be
 * exported as printer-friendly HTML.
 *
 * @param $nid
 *   An integer representing the node id (nid) of the node to export.
 * @return
 *   A string containing HTML representing the node and its children in
 *   the folio hierarchy.
 */
function folio_export_html($nid) {
  if (user_access('access printer-friendly version')) {
    $export_data = array();
    $node = node_load($nid);
    if (isset($node->folio)) {
      $tree = folio_menu_subtree_data($node->folio);
      $contents = folio_export_traverse($tree, 'folio_node_export');
      return theme('folio_export_html', array('title' => $node->title, 'contents' => $contents, 'depth' => $node->folio['depth']));
    }
    else {
      drupal_not_found();
    }
  }
  else {
    drupal_access_denied();
  }
}

/**
 * Menu callback; show the outline form for a single node.
 */
function folio_outline($node) {
  drupal_set_title($node->title);
  return drupal_get_form('folio_outline_form', $node);
}

/**
 * Build the form to handle all folio outline operations via the outline tab.
 *
 * @see folio_outline_form_submit()
 * @see folio_remove_button_submit()
 *
 * @ingroup forms
 */
function folio_outline_form($form, &$form_state, $node) {
  if (!isset($node->folio)) {
    // The node is not part of any folio yet - set default options.
    $node->folio = _folio_link_defaults($node->nid);
  }
  else {
    $node->folio['original_bid'] = $node->folio['bid'];
  }

  // Find the depth limit for the parent select.
  if (!isset($node->folio['parent_depth_limit'])) {
    $node->folio['parent_depth_limit'] = _folio_parent_depth_limit($node->folio);
  }
  $form['#node'] = $node;
  $form['#id'] = 'folio-outline';
  _folio_add_form_elements($form, $form_state, $node);

  $form['folio']['#collapsible'] = FALSE;

  $form['update'] = array(
    '#type' => 'submit',
    '#value' => $node->folio['original_bid'] ? t('Update folio outline') : t('Add to folio outline'),
    '#weight' => 15,
  );

  $form['remove'] = array(
    '#type' => 'submit',
    '#value' => t('Remove from folio outline'),
    '#access' => $node->nid != $node->folio['bid'] && $node->folio['bid'],
    '#weight' => 20,
    '#submit' => array('folio_remove_button_submit'),
  );

  return $form;
}

/**
 * Button submit function to redirect to removal confirm form.
 *
 * @see folio_outline_form()
 */
function folio_remove_button_submit($form, &$form_state) {
  $form_state['redirect'] = 'node/' . $form['#node']->nid . '/outline/remove';
}

/**
 * Handles folio outline form submissions from the outline tab.
 *
 * @see folio_outline_form()
 */
function folio_outline_form_submit($form, &$form_state) {
  $node = $form['#node'];
  $form_state['redirect'] = "node/" . $node->nid;
  $folio_link = $form_state['values']['folio'];
  if (!$folio_link['bid']) {
    drupal_set_message(t('No changes were made'));

    return;
  }

  $folio_link['menu_name'] = folio_menu_name($folio_link['bid']);
  $node->folio = $folio_link;
  if (_folio_update_outline($node)) {
    if ($node->folio['parent_mismatch']) {
      // This will usually only happen when JS is disabled.
      drupal_set_message(t('The post has been added to the selected folio. You may now position it relative to other pages.'));
      $form_state['redirect'] = "node/" . $node->nid . "/outline";
    }
    else {
      drupal_set_message(t('The folio outline has been updated.'));
    }
  }
  else {
    drupal_set_message(t('There was an error adding the post to the folio.'), 'error');
  }
}

/**
 * Menu callback; builds a form to confirm removal of a node from the folio.
 *
 * @see folio_remove_form_submit()
 *
 * @ingroup forms
 */
function folio_remove_form($form, &$form_state, $node) {
  $form['#node'] = $node;
  $title = array('%title' => $node->title);

  if ($node->folio['has_children']) {
    $description = t('%title has associated child pages, which will be relocated automatically to maintain their connection to the folio. To recreate the hierarchy (as it was before removing this page), %title may be added again using the Outline tab, and each of its former child pages will need to be relocated manually.', $title);
  }
  else {
    $description = t('%title may be added to hierarchy again using the Outline tab.', $title);
  }

  return confirm_form($form, t('Are you sure you want to remove %title from the folio hierarchy?', $title), 'node/' . $node->nid, $description, t('Remove'));
}

/**
 * Confirm form submit function to remove a node from the folio.
 *
 * @see folio_remove_form()
 */
function folio_remove_form_submit($form, &$form_state) {
  $node = $form['#node'];
  if ($node->nid != $node->folio['bid']) {
    // Only allowed when this is not a folio (top-level page).
    menu_link_delete($node->folio['mlid']);
    db_delete('folio')
      ->condition('nid', $node->nid)
      ->execute();
    drupal_set_message(t('The post has been removed from the folio.'));
  }
  $form_state['redirect'] = 'node/' . $node->nid;
}
