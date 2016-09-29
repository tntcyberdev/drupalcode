<?php

/**
 * Implements hook_views_plugins().
 */
function tk_views_isotope_views_plugins() {
  return array(
    'style' => array(
      'tk_views_isotop' => array(
        'title' => t('Themeski Isotope'),
        'handler' => 'tk_views_isotope_plugin_style_list',
        'theme' => 'tk_views_isotope',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'uses grouping' => FALSE,
        'uses row class' => TRUE,
        'type' => 'normal',
        'path' => drupal_get_path('module', 'tk_views_isotope'),
        'parent' => 'list',
        'theme file' => 'tk_views_isotope.theme.inc',
      ),
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function tk_views_isotope_views_data() {
  $data['views']['data_filter'] = array(
    'title' => t('Isotope data filter'),
    'help' => t('Format data input to machine name.'),
    'field' => array(
      'handler' => 'tk_views_isotope_format_handler',
    ),
  );
  return $data;
}