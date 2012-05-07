<?php
/**
 * @file
 * Main theme file for the Fluff moduel.
 */

function theme_fluff_puffs_table_form($form) {
  $output = '';
  $puffs = array();

  // Easy index puffs
  foreach ($form['#puffs'] as $k => $p) {
    $puffs[$form['#puffs'][$k]->machine_name] = $form['#puffs'][$k];
  }
  
  // Unset any high level elements.
  unset($form['puffs_select']['#title']);
  unset($form['puffs_select']['#description']);
  
  // Create table
  $header = array(t('Select'), t('Puff'), t('Branch'), t('Puffs'), t('Actions'));
  $rows = array();
  foreach (element_children($form['puffs_select']) as $element) {

    // Remove unneeded items
    unset($form['puffs_select'][$element]['#title']);
    unset($form['puffs_select'][$element]['#description']);
    
    // Get puffs
    $puff_output = '<ul>';
    foreach ($puffs[$element]->config['puffs'] as $k => $p) {
      $puff_output .= '<li><strong>' . filter_xss_admin($p['title']) . '</strong> ' . filter_xss_admin($p['description']) . '</li>';
    }
    $puff_output .= '<ul>';

    // Creat row
    $row = array(
      'select' => array('data' => drupal_render($form['puffs_select'][$element]), 'class' => 'select'),
      'title' => array('data' => check_plain($puffs[$element]->title), 'class' => 'title'),
      'branch' => array('data' => check_plain($puffs[$element]->branch), 'class' => 'branch'),
      'puffs' => array('data' => $puff_output, 'class' => 'puffs'),
      'actions' => array('data' => '', 'class' => 'sign'),
    );
    $rows[] = array('data' => $row);
  }
  $output .= theme('table', $header, $rows);
  
  $output .= drupal_render($form['buttons']);
  $output .= drupal_render($form);

  return $output;
}