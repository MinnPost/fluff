<?php
/**
 * @file
 * File to hold admin logic.
 */

/**
 * Menu callback; displays the fluff module settings page.
 *
 * @see system_settings_form()
 */
function fluff_admin_settings(&$form_state) {

  // Define Form
  $form['fluff_option'] = array(
    '#type' => 'textfield',
    '#title' => t('Fluff'),
    '#description' => t('This doesnt do anything.'),
    '#default_value' => variable_get('fluff_option', ''),
  );

  // Make a system setting form and return
  return system_settings_form($form);
}

/**
 * Manage puffs interface.
 */
function fluff_admin_puffs(&$form_state) {
  $form = array();
  $puffs = fluff_get_puffs(TRUE);
  
  // Build options list
  $puffs_options = array();
  foreach ($puffs as $p) {
    $puffs_options[$p->machine_name] = $p->title;
  }
  
  $form['puffs_select'] = array(
    '#title' => t('Select'),
    '#type' => 'checkboxes',
    '#options' => $puffs_options,
  );
  
  // Theme
  $form['#puffs'] = $puffs;
  $form['#theme'] = 'fluff_puffs_table_form';

  return $form;
}

/**
 * View puff.
 */
function fluff_admin_view_puff(&$form_state, $puff = array()) {
  $form = array();
  
  $form['title'] = array(
    '#type' => 'item',
    '#title' => t('Title'),
    '#value' => check_plain($puff->title),
  );
  
  $form['debug'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debug'),
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
  );
  $form['debug']['debug_output'] = array(
    '#type' => 'item',
    '#value' => '<code><pre>' . var_export($puff, TRUE) . '</pre></code>',
  );
  
  $form['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );
  
  $form['puff'] = array(
    '#type' => 'value',
    '#value' => $puff,
  );
  
  return $form;
}

/**
 * Submit view puff
 */
function fluff_admin_view_puff_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Update')) {
    $updated = fluff_update_puff($form_state['values']['puff']);
    
    if ($updated === TRUE) {
      drupal_set_message(t('Puff, %puff_name, updated successfully.', array(
        '%puff_name' => $form_state['values']['puff']->title,
      )));
    }
    else {
      drupal_set_message(t('Error updating puff, %puff_name.  %error', array(
        '%puff_name' => $form_state['values']['puff']->title,
        '%error' => ($updated === FALSE) ? t('Unknown error') : $updated,
      )));
    }
  }
}

/**
 * Add puffs interface.
 */
function fluff_admin_add_puff(&$form_state) {
  $form = array();
  
  $form['puff_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('Puff URI'),
    '#description' => t('The Git uri for the puff.  This will probably be an address ending in .git.  If using Github, you should use the Read-Only version.'),
    '#default_value' => isset($form_state['puff_uri']) ? $form_state['puff_uri'] : '',
    '#required' => TRUE,
  );
  
  $form['puff_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );

  return $form;
}

/**
 * Add puffs submit.
 */
function fluff_admin_add_puff_submit($form, &$form_state) {
  $success = fluff_add_puff($form_state['values']['puff_uri']);
  if ($success !== TRUE) {
    form_set_error('puff_uri', t('Error when trying to clone Puff.  %error', array('%error' => $success)));
  }
  else {
    drupal_set_message(t('Puff project cloned and added.'));
    drupal_goto('admin/build/fluff/puffs');
  }
}