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
  
  fluff_build_puff_index();

  return $form;
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