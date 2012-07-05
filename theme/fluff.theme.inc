<?php
/**
 * @file
 * Main theme file for the Fluff moduel.
 */

function theme_fluff_puffs_table_form($form = array()) {
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
  $header = array(t('Select'), t('Puff'), t('Branch'), t('Embeddables'), t('Actions'));
  $rows = array();
  foreach (element_children($form['puffs_select']) as $element) {

    // Remove unneeded items
    unset($form['puffs_select'][$element]['#title']);
    unset($form['puffs_select'][$element]['#description']);
    
    // Get puffs
    $puff_output = '<ul>';
    foreach ($puffs[$element]->config['puffs'] as $k => $p) {
      $puff_output .= '<li><strong>' . filter_xss_admin($p['title']) . '</strong>: ' . filter_xss_admin($p['description']) . '</li>';
    }
    $puff_output .= '<ul>';

    // Creat row
    $row = array(
      'select' => array('data' => drupal_render($form['puffs_select'][$element]), 'class' => 'select'),
      'title' => array('data' => l($puffs[$element]->title, 'admin/build/fluff/puffs/' . $element . '/view'), 'class' => 'title'),
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

/**
 * Theme function for puff info in forms.
 */
function theme_fluff_form_puff_info($puffs = array()) {
  $output = '';
  
  $output .= '<div class="fluff-form-puff-info">';
  foreach ($puffs as $k => $p) {
    $output .= '<div class="' . $k . ' fluff-form-info-item">';
    $output .= '<h3>' . check_plain($p->config['title']) . ' ' . t('(enabled)') . '</h3>';
    $output .= '<p>' . check_plain($p->config['description']) . '</p>';
    $output .= '<ul>';
    foreach ($p->config['puffs'] as $t => $g) {
      $output .= '<li>';
      $output .= '<strong>' . check_plain($g['title']) . '</strong><br />';
      $output .= check_plain($g['description']) . '<br />';
      $output .= t('Embed') . ': <code>[' . $k . ' ' . $t . ']</code>';
      $output .= '</li>';
    }
    $output .= '</ul>';
    $output .= '</div>';
  }
  $output .= '</div>';
  
  return $output;
}