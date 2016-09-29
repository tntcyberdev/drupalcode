<?php

/**
 * Implements hook_views_plugins().
 */
function views_jcarousel_connected_views_plugins() {
  return array(
    'style' => array(
      'jcarousel_connected' => array(
        'title' => t('jCarousel Connected'),
        'handler' => 'views_jcarousel_connected_plugin_style_list',
        'theme' => 'views_jcarousel_connected',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'uses grouping' => FALSE,
        'uses row class' => TRUE,
        'type' => 'normal',
        'path' => drupal_get_path('module', 'views_jcarousel_connected'),
        'parent' => 'list',
        'theme file' => 'views_jcarousel_connected.theme.inc',
      ),
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function views_jcarousel_connected_views_data() {
  $data['views']['data_filter'] = array(
    'title' => t('Pager control'),
    'help' => t('Add content for pager'),
    'field' => array(
      'handler' => 'views_jcarousel_connected_format_handler',
    ),
  );
  return $data;
}