<?php
// $Id:

/**
 * Preprocess function to build the tk_views_isotop
 */
function template_preprocess_views_jcarousel_connected(&$vars) {
  // Extract useful data from view object.
  $view = $vars['view'];
  $dom_id = $view->dom_id;
  $fields = $view->field;
  $handler = $view->style_plugin;
  $result = $view->result;

  $pager_control = array();
  if (!empty($handler->rendered_fields)){
    foreach ($handler->rendered_fields as $index => $row) {
      if (isset($row['data_filter'])) {
        $pager_control[] = $row['data_filter'];
      }
    }
  } else {
    $pager_control = array();
  }
  $vars['pager_control'] = $pager_control;
  $vars['dom_id'] = $dom_id;
  $options = $vars['options'];
  $vars['row_class'] = $options['row_class'];
  $vars['classes_array'] = array();
  $vars['classes'] = array();

  $default_row_class = isset($options['default_row_class']) ? $options['default_row_class'] : FALSE;
  $row_class_special = isset($options['row_class_special']) ? $options['row_class_special'] : FALSE;

  array_filter($options);

  $rows = $vars['rows'];
  $count = 0;
  $max = count($rows);
  foreach ($rows as $id => $row) {
    $count++;
    if ($default_row_class) {
      $vars['classes'][$id][] = 'views-row';
    }
    if ($row_class_special) {
      $vars['classes'][$id][] = 'views-row-' . ($count % 2 ? 'odd' : 'even');
      if ($count == 1) {
        $vars['classes'][$id][] = 'views-row-first';
      }
      if ($count == $max) {
        $vars['classes'][$id][] = 'views-row-last';
      }
    }

    if ($row_class = $view->style_plugin->get_row_class($id)) {
      $vars['classes'][$id][] = $row_class;
    }

    // Flatten the classes to a string for each row for the template file.
    $vars['classes_array'][$id] = isset($vars['classes'][$id]) ? implode(' ', $vars['classes'][$id]) : '';
  }

  // Define a reference ID for this isotope grid.
  $views_id = 'views-isotop-' . $view->name . '-' . $view->style_plugin->display->id;
  $vars['isotop_id'] = $views_id;
  
  // Add JavaScript files and settings.
  drupal_add_js(drupal_get_path('module', 'views_jcarousel_connected') . '/js/script.js');
  drupal_add_js(drupal_get_path('module', 'views_jcarousel_connected') . '/js/jquery.jcarousel.min.js');
  drupal_add_js(array('views_jcarousel_connected' => array('dom_id' => $dom_id)), 'setting');
  // Add stylesheets.
  drupal_add_css(drupal_get_path('module', 'views_jcarousel_connected') . '/css/jcarousel.connected-carousels.css');
}