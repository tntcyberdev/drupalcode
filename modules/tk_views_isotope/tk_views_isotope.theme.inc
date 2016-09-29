<?php
// $Id:

/**
 * Preprocess function to build the tk_views_isotop
 */
function template_preprocess_tk_views_isotope(&$vars) {
  // Extract useful data from view object.
  $view = $vars['view'];
  $fields = $view->field;
  $handler = $view->style_plugin;
  $result = $view->result;

  $list_filter = array();
  foreach ($fields as $field => $data) {
    if (strpos($field, 'data_filter') !== false) {
      $list_filter[] = $field;
    }
  }

  $filters = array();
  $data_filter = array();

  if ($list_filter && !empty($handler->rendered_fields)){     
    foreach ($handler->rendered_fields as $index => $row) {
      $row_filter = array();
      foreach ($list_filter as $filter) {
        $tmp = $row[$filter];
        $elements = explode(',', $tmp);

        foreach ($elements as $element) {
          $e_format = trim($element);
          if (empty($e_format))  continue;
          $e_format = strtolower(str_replace(' ', '-', $e_format));
          $machine_name = unicode_str_filter($e_format);
          $filters[$filter][$e_format] = trim($element);
          $row_filter[] = $machine_name;
        }
      }
      $data_filter[$index] = implode(' ', $row_filter);
    }

  } else {
    $list_filter = array();
  }
  $vars['data_filter'] = $data_filter;
  $vars['list_filter'] = $list_filter;
  $vars['filters'] = array();
  foreach ($filters as $key => $value) {
    natsort($value);
    $vars['filters'][$key] = $value;
  }

  $options = $vars['options'];
  $vars['ul_class'] = $options['ul_class'];
  $vars['row_class'] = $options['row_class'];
  $vars['classes_array'] = array();
  $vars['classes'] = array();
  $width_item = $options['width_item'];

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
      $vars['classes'][$id][] = 'views-row-' . $count;
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
  drupal_add_js(drupal_get_path('module', 'tk_views_isotope') . '/js/jquery.isotope.js');
  drupal_add_js(drupal_get_path('module', 'tk_views_isotope') . '/js/jquery.masonry.min.js');
  drupal_add_js(drupal_get_path('module', 'tk_views_isotope') . '/js/script.js');
  drupal_add_js(array('tk_views_isotope' => array('width_item' => $width_item)), 'setting');

  // Add stylesheets.
  drupal_add_css(drupal_get_path('module', 'tk_views_isotope') . '/css/isotope_style.css');
  drupal_add_css(drupal_get_path('module', 'tk_views_isotope') . '/css/tk_views_isotope.css');
}

function unicode_str_filter ($str){
  $unicode = array(
    'a'=>'á|à|ả|ã|ạ|ă|ắ|ặ|ằ|ẳ|ẵ|â|ấ|ầ|ẩ|ẫ|ậ',
    'd'=>'đ',
    'e'=>'é|è|ẻ|ẽ|ẹ|ê|ế|ề|ể|ễ|ệ',
    'i'=>'í|ì|ỉ|ĩ|ị',
    'o'=>'ó|ò|ỏ|õ|ọ|ô|ố|ồ|ổ|ỗ|ộ|ơ|ớ|ờ|ở|ỡ|ợ',
    'u'=>'ú|ù|ủ|ũ|ụ|ư|ứ|ừ|ử|ữ|ự',
    'y'=>'ý|ỳ|ỷ|ỹ|ỵ',
    'A'=>'Á|À|Ả|Ã|Ạ|Ă|Ắ|Ặ|Ằ|Ẳ|Ẵ|Â|Ấ|Ầ|Ẩ|Ẫ|Ậ',
    'D'=>'Đ',
    'E'=>'É|È|Ẻ|Ẽ|Ẹ|Ê|Ế|Ề|Ể|Ễ|Ệ',
    'I'=>'Í|Ì|Ỉ|Ĩ|Ị',
    'O'=>'Ó|Ò|Ỏ|Õ|Ọ|Ô|Ố|Ồ|Ổ|Ỗ|Ộ|Ơ|Ớ|Ờ|Ở|Ỡ|Ợ',
    'U'=>'Ú|Ù|Ủ|Ũ|Ụ|Ư|Ứ|Ừ|Ử|Ữ|Ự',
    'Y'=>'Ý|Ỳ|Ỷ|Ỹ|Ỵ',
  );
    
  foreach($unicode as $nonUnicode=>$uni){
    $str = preg_replace("/($uni)/i", $nonUnicode, $str);
  }
  return $str;
}