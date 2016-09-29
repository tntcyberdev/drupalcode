<?php

/**
 * Funtion Build Form Create New T-shirt
 */
function gp_add_product_form($form,&$form_state){
  drupal_add_js(drupal_get_path('module', 'gp_add_product').'/js/gp_add_product.js',array('weight' => 0));
  drupal_add_js(drupal_get_path('module', 'gp_add_product').'/js/jquery.validationEngine.js', array('weight' => 4));
  drupal_add_js(drupal_get_path('module', 'gp_add_product').'/js/jquery.validationEngine-en.js', array('weight' => 3 ));
  drupal_add_css(drupal_get_path('module', 'gp_add_product').'/validationEngine.jquery.css');
	$form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'] = array('custom-form-product');
  // Title
  $form['title'] = array(
  	'#type' => 'textfield',
  	'#title' => t('Title'),
  	'#required' => TRUE,
    '#attributes' => array(
      'class' => array('validate[required]'),
    ),
  );

  $languages = language_list('enabled');
  $option_language = array();
  foreach ($languages as $key => $value) {
  	foreach ($value as $language) {
  		$option_language[$language->language] = $language->name;
  	}
  }

  $form['language'] = array(
  	'#type' => 'select',
  	'#title' => t('Language'),
  	'#options' => $option_language,
  );

  // Body
  $form['body'] = array(
    '#type' => 'text_format',
    '#title' => t('Body'),
  );

  //Render Product Attribute
  $form['catalog_'] = array(
    '#type' => 'fieldset',
    '#title' => t('Product Settings'),
  );

  $form['catalog_']['new_arrival'] = array(
    '#type' => 'checkbox',
    '#title' => t('New Arrival ?'),
    '#group' => 'catalog',
  );

  // Category
  $ls_categories = taxonomy_get_tree(1);
  $option_category = array();
  foreach ($ls_categories as $key => $value) {
    $term_parent = taxonomy_get_parents_all($value->tid);
    if (empty($term_parent) || count($term_parent) == 1) {
      $option_category[$value->tid] = $value->name;
    } else {
      $name = '';
      for ($i= (count($term_parent) -1); $i >= 0; $i-- ) {
        if ($i != 0 ) {
          $name .= $term_parent[$i]->name.' > ';
        } else {
          $name .= $term_parent[$i]->name;
        }
      }
      $option_category[$value->tid] = $name;
    }
  }
  $form['catalog_']['category'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Gender'),
    '#options' => $option_category,
    '#required' => TRUE,
    /*'#attributes' => array(
      'class' => array('validate[required]'),
    ),*/
  );

  // Fabric
  $ls_fabric = taxonomy_get_tree(9);
  $option_fabric = array();
  foreach ($ls_fabric as $key => $value) {
    $option_fabric[$value->tid] = $value->name;
  }

  $form['catalog_']['fabric'] = array(
    '#type' => 'select',
    '#title' => t('Fabric'),
    '#options' => $option_fabric,
    '#group' => 'catalog',
    '#size' > 60,
  );


  // Discount
  $ls_discount = taxonomy_get_tree(13);
  $option_discount = array(''=>t('- None -'));
  foreach ($ls_discount as $key => $value) {
    $option_discount[$value->tid] = $value->name;
  }

  $form['catalog_']['discount'] = array(
    '#type' => 'select',
    '#title' => t('Discount'),
    '#options' => $option_discount,
    '#group' => 'catalog',
  );

  // Product Price
  $form['catalog_']['price'] = array(
  	'#type' => 'textfield',
  	'#title' => t('Price (USD)'),
  	'#required' => TRUE,
    '#attributes' => array(
      'class' => array('validate[required,custom[onlyNumberSp]]'),
    ),
    '#size' => 10,
  );

  // Generate Attributes of product
  $ls_color = taxonomy_get_tree(2);
  $ls_color_code = array();
  foreach ($ls_color as $key => $value) {
  	$term_info = taxonomy_term_load($value->tid);
  	$ls_color_code[$value->tid] = $term_info->field_color[LANGUAGE_NONE][0]['value'];
  }

  // List Color
  foreach ($ls_color_code as $key => $value) {
    $term_info = taxonomy_term_load($key);
    $form['ck_color'.$key] = array(
      '#markup' => '<input type = "checkbox" value = '.$key.' name = "color[]" class = "ck-color"> '.$term_info->name.' <div style = "background:'.$value.'; width:100px; height:10px; margin-bottom: 15px;"></div>',
    );
    $form['sl_color'.$key] = array(
      '#type' => 'fieldset',
      '#title' => 'Setting',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#attributes' => array(
        'class' => array('element-invisible'),
      ),
    );

    $form['sl_color'.$key]['image'] = array(
      '#type' => 'plupload',
      '#title' => t('Upload files'),
      '#description' => t('This multi-upload widget uses Plupload library.'),
      '#upload_validators' => array(
        'file_validate_extensions' => array('jpg jpeg gif png'),
        'my_custom_file_validator' => array('some validation criteria'),
      ),
      '#plupload_settings' => array(
        'url' => url('plupload-handle-uploads', array('query' => array('plupload_token' => drupal_get_token('plupload-handle-uploads')))),
        'max_file_size' => file_upload_max_size() . 'b',
        'chunk_size' => parse_size(ini_get('post_max_size')) . 'b',
        'unique_names' => TRUE,
        'flash_swf_url' => file_create_url($library_path . '/js/plupload.flash.swf'),
        'silverlight_xap_url' => file_create_url($library_path . '/js/plupload.silverlight.xap'),
      ),
    );

    // List Size
    $ls_size = taxonomy_get_tree(3);
    $form['sl_color'.$key]['tbl_start'] = array(
      '#markup' => '<table><thead><tr><td>Size</td><td>Quantity</td></tr></thead>',
    );
    for ($j=0; $j < count($ls_size); $j++) {
      $form['sl_color'.$key]['size'.$j] = array(
        '#type' => 'checkbox',
        '#title' => $ls_size[$j]->name,
        '#value' => $ls_size[$j]->tid,
        '#name' => 'size['.$key.'][]',
        '#prefix' => '<tr><td><input type = "hidden" value = "" name = "hd_size['.$key.'][]" class = "hidden-size">',
        '#suffix' => '<input type = "hidden" value = "'.$ls_size[$j]->tid.'" class = "current-size"></td>',
        '#attributes' => array(
          'class' => array('ck-size'),
        ),
      );

      $form['sl_color'.$key]['quantity'.$j] = array(
        '#type' => 'textfield',
        '#name' => 'quantity['.$key.'][]',
        '#size' => 10,
        '#prefix' => '<td>',
        '#suffix' => '</td></tr>',
        '#default_value' => 0,
        '#attributes' => array(
          'class' => array('validate[custom[onlyNumberSp]]'),
        ),
      );
    }
    $form['sl_color'.$key]['end_tbl'] = array(
      '#markup' => '</table>',
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#submit' => array('gp_add_product_save'),
  );

  return $form;
}

/**
 * Save Product Info
 */
function gp_add_product_save($form,&$form_state) {
  global $user;
  $ls_fabric = $_POST['catalog_']['fabric'];
  $ls_color = $_POST['color'];
  $ls_size = $_POST['hd_size'];
  $ls_quantity = $_POST['quantity'];
  $price = intval($_POST['catalog_']['price']);
  $price = $price*100;
  $ls_size_tmp = array();
  $ls_categories = $_POST['catalog_']['category'];
  $ls_categories_tmp = array();
  foreach ($ls_categories as $key => $value) {
    $ls_categories_tmp[] = $value;
  }
  $path = generate_directory_by_tid(end($ls_categories_tmp));
  $ls_quantity_tmp = array();
  foreach ($ls_size as $key => $value) {
    $size_tmp = array();
    foreach ($value as $result) {
      if ($result != 0) {
        $size_tmp[] = $result;
      }
    }
    $ls_size_tmp[$key] = $size_tmp;
  }

  $ls_quantity_tmp = array();
  foreach ($ls_quantity as $key => $value) {
    $qty = array();
    foreach ($value as $result) {
      if ($result != 0) {
        $qty[] = $result;
      }
    }
    $ls_quantity_tmp[$key] = $qty;
  }

  // Save Node
  $new_product  = new stdClass();
  $new_product->uid = $user->uid;
  $new_product->name = $user->name;
  $new_product->language = $_POST['language'];
  $new_product->type = 'products';
  $new_product->title = $_POST['title'];
  // Save Product
  $ls_pid = array();
  for ($j=0; $j < count($ls_color); $j++) {
    $color = $ls_color[$j];
    $color_info = taxonomy_term_load($color);
    // Save Image
    $ls_image = $form_state['values']['sl_color'.$color]['image'];
    foreach ($ls_image as $uploaded_file) {
      if ($uploaded_file['status'] == 'done') {
        $source = $uploaded_file['tmppath'];
        $destination = $path.file_stream_wrapper_uri_normalize($scheme . $uploaded_file['name']);
        $destination = file_unmanaged_move($source, $destination, FILE_EXISTS_RENAME);
        $file = plupload_file_uri_to_object($destination);
        file_save($file);
        $saved_files[] = $file;
      }
    }

    $size = $ls_size_tmp[$color];
    $quantity = $ls_quantity_tmp[$color];
    for ($i=0; $i < count($size); $i++) {
      $size_info = taxonomy_term_load($size[$i]);
      $product = commerce_product_new('products');
      $product->uid = $user->uid;
      $product->status = 1;
      $product->title = $_POST['title'].' ('.$color_info->name.' '.$size_info->name.')';
      $product->sku = 'SKU'.rand();
      $product->title_field[LANGUAGE_NONE][0]['value'] = $_POST['title'].' ('.$color_info->name.' '.$size_info->name.')';
      $product->commerce_price[LANGUAGE_NONE][0]['amount'] = $price;
      $product->commerce_price[LANGUAGE_NONE][0]['currency_code'] = 'USD';
      $product->field_type_color[LANGUAGE_NONE][0]['tid'] = $color;
      $product->field_type_size[LANGUAGE_NONE][0]['tid'] = $size[$i];
      if ($quantity[$i]) {
        $product->commerce_stock[LANGUAGE_NONE][0]['value'] = $quantity[$i];
      } else {
        $product->commerce_stock[LANGUAGE_NONE][0]['value'] = 0;
      }
      //Save Image for Product
      for ($k=0; $k < count($saved_files); $k++) { 
        $file_info = $saved_files[$k];
        $product->field_product_images[LANGUAGE_NONE][$k]['fid'] = $file_info->fid;
        $product->field_product_images[LANGUAGE_NONE][$k]['filename'] = $file_info->filename;
        $product->field_product_images[LANGUAGE_NONE][$k]['filesize'] = $file_info->filesize;
        $product->field_product_images[LANGUAGE_NONE][$k]['uri'] = $file_info->uri;
        $product->field_product_images[LANGUAGE_NONE][$k]['uid'] = $file_info->uid;
      }
      commerce_product_save($product);
      $ls_pid[] = $product->product_id;
    }
    $saved_files = array();
  }
  for ($i=0; $i < count($ls_pid); $i++) { 
    $new_product->field_product_reference[LANGUAGE_NONE][$i]['product_id'] = $ls_pid[$i];
  }
  if ($_POST['body']['value']) {
    $new_product->body[LANGUAGE_NONE][0]['value'] = $_POST['body']['value'];
    $new_product->body[LANGUAGE_NONE][0]['format'] = 'full_html';
  }
  if (!empty($ls_categories_tmp)) {
    for ($i=0; $i < count($ls_categories_tmp); $i++) { 
      $new_product->field_categories[LANGUAGE_NONE][$i]['tid'] = $ls_categories_tmp[$i];
    }
  }
  if ($_POST['catalog_']['fabric']) {
    $new_product->field_fabric[LANGUAGE_NONE][0]['tid'] = $_POST['catalog_']['fabric'];
  }
  if ($_POST['catalog_']['new_arrival']) {
    $new_product->field_new_arrivals[LANGUAGE_NONE][0]['value'] = $_POST['catalog_']['new_arrival'];
  }
  if ($_POST['catalog_']['discount']) {
    $new_product->field_discount[LANGUAGE_NONE][0]['tid'] = $_POST['catalog_']['discount'];
  }

  node_save($new_product);
  drupal_set_message(t("Save successful!"), 'status');
}
