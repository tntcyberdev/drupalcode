<?php
/**
 * Function Build Form Edit T-Shirt Info
 */
function gp_add_product_edit_form($form,&$form_state) {
  global $base_url;
  $library_path = libraries_get_path('plupload');
  drupal_add_js(drupal_get_path('module', 'gp_add_product').'/js/gp_add_product.js',array('weight' => 0));
  drupal_add_js(drupal_get_path('module', 'gp_add_product').'/js/jquery.validationEngine.js', array('weight' => 4));
  drupal_add_js(drupal_get_path('module', 'gp_add_product').'/js/jquery.validationEngine-en.js', array('weight' => 3 ));
  drupal_add_css(drupal_get_path('module', 'gp_add_product').'/validationEngine.jquery.css');
  drupal_add_css(drupal_get_path('module', 'gp_add_product').'/css/gp_add_product.css');
  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'] = array('custom-form-product');
  if (is_numeric(arg(2))) {
    $nid = arg(2);
    $node = node_load($nid);
    if (!empty($node->body)) {
      $body = $node->body[LANGUAGE_NONE][0]['value']; // LS BODY
    }
    $list_category = $node->field_categories[LANGUAGE_NONE]; // LS CATEGORIES
    $category = array();
    for ($i=0; $i < count($list_category); $i++) { 
      $category[] = $list_category[$i]['tid'];
    } 

    if (!empty($node->field_product_tags)) {
      $ls_tag = $node->field_product_tags[LANGUAGE_NONE]; // LS TAGS
    }
    if (!empty($node->field_product_reference)) {
      $ls_pid = $node->field_product_reference[LANGUAGE_NONE]; // LIST PRODUCT ID
    }

    $ls_color_edit = array(); // LS COLOR
    for ($i=0; $i < count($ls_pid); $i++) { 
      $product = commerce_product_load($ls_pid[$i]);
      $ls_color_edit[] = $product->field_type_color[LANGUAGE_NONE][0]['tid'];
    }
    $form['link_add_item'] = array(
      '#markup' => '<a class = "button" href = "'.$base_url.'/node/'.$nid.'/add-item" target = "_blank">'.t('Edit "items you might like"').'</a>',
    );
  }
  // Title
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#attributes' => array(
      'class' => array('validate[required]'),
    ),
  );
  if ($node && $node->title) {
    $form['title']['#default_value'] = $node->title;
  }

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
  if ($node->language) {
    $form['language']['#default_value'] = $node->language;
  }

  // Body
  $form['body'] = array(
    '#type' => 'text_format',
    '#title' => t('Body'),
  );
  if (isset($body)) {
    $form['body']['#default_value'] = $body;
  }

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
  if ($node->field_new_arrivals[LANGUAGE_NONE][0]['value']) {
    $form['catalog_']['new_arrival']['#attributes']['checked'] = 'checked';
  }

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
  if ($category) {
    $form['catalog_']['category']['#default_value'] = $category;
  }

  // Fabric
  $ls_fabric = taxonomy_get_tree(9);
  $ls_fabric_tmp = $node->field_fabric[LANGUAGE_NONE];
  $ls_fabric_default = array();
  for ($i=0; $i <count($ls_fabric_tmp) ; $i++) { 
    $ls_fabric_default[] = $ls_fabric_tmp[$i]['tid'];
  }
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
  if (!empty($ls_fabric_default)) {
    $form['catalog_']['fabric']['#default_value'] = $ls_fabric_default;
  }

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
  if ($node->field_discount[LANGUAGE_NONE][0]['tid']) {
    $form['catalog_']['discount']['#default_value'] = $node->field_discount[LANGUAGE_NONE][0]['tid'];
  }

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
  if ($ls_pid) {
    $summary_info = commerce_product_load($ls_pid[0]['product_id']);
    $price = $summary_info->commerce_price[LANGUAGE_NONE][0]['amount'];
    if ($price) {
      $form['catalog_']['price']['#default_value'] = $price/100;
    }
  }

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
    if (in_array($key, $ls_color_edit)) {
      $form['ck_color'.$key] = array(
        '#markup' => '<input type = "checkbox" value = '.$key.' name = "color[]" class = "ck-color" checked = "checked"> '.$term_info->name.' <div style = "background:'.$value.'; width:100px; height:10px; margin-bottom: 15px;"></div>',
      );
    } else {
      $form['ck_color'.$key] = array(
        '#markup' => '<input type = "checkbox" value = '.$key.' name = "color[]" class = "ck-color"> '.$term_info->name.' <div style = "background:'.$value.'; width:100px; height:10px; margin-bottom: 15px;"></div>',
      );
    }

    $form['sl_color'.$key] = array(
      '#type' => 'fieldset',
      '#title' => 'Setting',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    if (in_array($key, $ls_color_edit)) {
      $form['sl_color'.$key]['#attributes'] = array('class' => array('element-visible'));
    } else {
      $form['sl_color'.$key]['#attributes'] = array('class' => array('element-invisible'));
    }
    // RENDER IMAGE
    $ls_size_edit = array(); // LS SIZE
    $ls_quantity_edit = array(); // LS QUANTITY
    for ($i=0; $i < count($ls_pid); $i++) { 
      $product = commerce_product_load($ls_pid[$i]);
      $tmp_color = $product->field_type_color[LANGUAGE_NONE][0]['tid'];
      if ($key == $tmp_color) {
        $size_key = $product->field_type_size[LANGUAGE_NONE][0]['tid'];
        $ls_size_edit[] = $size_key; // GET TERM ID SIZE
        $ls_image = $product->field_product_images[LANGUAGE_NONE];
        $ls_quantity_edit[$size_key] = $product->commerce_stock[LANGUAGE_NONE][0]['value'];
        for ($j=0; $j < count($ls_image); $j++) {
          $uri = $ls_image[$j]['uri'];
          $url = image_style_url('thumbnail',$uri);
          $form['sl_color'.$key]['image_default'.$j] = array(
            '#markup' => '<div class = "image-defaut" style = "display:inline-block;"><img src = '.$url.'><span class = "remove-img" title = "Remove"> <i class = "icon-remove"></i>x</span><input type= "hidden" value = "'.$ls_image[$j]['fid'].'" class = "hidden-fid" name = "image-id['.$key.'][]"></div> ',
          );
        }
      }
    }
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
      '#markup' => '<table><table><thead><tr><td>Size</td><td>Quantity</td></tr></thead>',
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
      if (in_array($ls_size[$j]->tid, $ls_size_edit) && in_array($key, $ls_color_edit)) {
        $form['sl_color'.$key]['size'.$j]['#attributes']['checked'] = 'checked';
        $form['sl_color'.$key]['size'.$j]['#prefix'] = '<tr><td><input type = "hidden" value = "'.$ls_size[$j]->tid.'" name = "hd_size['.$key.'][]" class = "hidden-size">';
      }

      $quantity_edit = 0;
      if (in_array($ls_size[$j]->tid, $ls_size_edit)) {
        $quantity_edit = $ls_quantity_edit[$ls_size[$j]->tid];
      }

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
      if (in_array($ls_size[$j]->tid, $ls_size_edit)) {
        $form['sl_color'.$key]['quantity'.$j]['#default_value'] = intval($quantity_edit);
      }
    }
    $form['sl_color'.$key]['end_tbl'] = array(
      '#markup' => '</table>',
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#submit' => array('gp_add_product_edit_save'),
  );

  return $form;
}

/**
 * Function Save Product When Edit Product
 */
function gp_add_product_edit_save($form,&$form_state) {
  global $user,$base_url;
  if (is_numeric(arg(2))) {
    $nid = arg(2);
    $node = node_load($nid);
  }
  $ls_color = $_POST['color']; // COLOR
  $ls_categories = $_POST['catalog_']['category'];
  $ls_categories_tmp = array();
  foreach ($ls_categories as $key => $value) {
    $ls_categories_tmp[] = $value;
  }
  $path = generate_directory_by_tid(end($ls_categories_tmp));
  $price = intval($_POST['catalog_']['price']);
  $price = $price*100;
  $node->title = $_POST['title'];
  if ($_POST['body']['value']) {
    $node->body[LANGUAGE_NONE][0]['value'] = $_POST['body']['value'];
    $node->body[LANGUAGE_NONE][0]['format'] = 'full_html';
  }
  if ($_POST['catalog_']['fabric']) {
    $node->field_fabric[LANGUAGE_NONE][0]['tid'] = $_POST['catalog_']['fabric'];
  }
  if ($_POST['catalog_']['new_arrival']) {
    $node->field_new_arrivals[LANGUAGE_NONE][0]['value'] = $_POST['catalog_']['new_arrival'];
  } else {
    $node->field_new_arrivals[LANGUAGE_NONE][0]['value'] = 0;
  }
  if ($_POST['catalog_']['discount']) {
    $node->field_discount[LANGUAGE_NONE][0]['tid'] = $_POST['catalog_']['discount'];
  } else {
    $node->field_discount = array();
  }
  $node->field_categories = array();
  if (!empty($ls_categories_tmp)) {
    for ($i=0; $i < count($ls_categories_tmp); $i++) { 
      $node->field_categories[LANGUAGE_NONE][$i]['tid'] = $ls_categories_tmp[$i];
    }
  }
  $ls_pid = $node->field_product_reference[LANGUAGE_NONE];// LIST PID
  
  // DELETE PROUDCT WHEN UNSELECT COLOR
  $ls_old_color = array(); // LIST OLD COLOR
  $ls_old_size = array();
  for ($i=0; $i < count($ls_pid); $i++) {
    $pid = $ls_pid[$i]['product_id'];
    $product = commerce_product_load($pid);
    $color_old = $product->field_type_color[LANGUAGE_NONE][0]['tid'];
    $size_old = $product->field_type_size[LANGUAGE_NONE][0]['tid'];
    if (in_array($color_old, $ls_color)) {
      $ls_old_size[] = $size_old;
      $ls_old_color[] = $color_old;
    } else{
      unset($ls_pid[$i]['product_id']);
      commerce_product_delete($pid);
    }
  }
  $ls_old_color = array_unique($ls_old_color);
  $ls_old_size = array_unique($ls_old_size);
  // CREATE AND UPDATE PRODUCT
  $ls_new_pid = array(); // LS NEW PID
  for ($j=0; $j < count($ls_color); $j++) {
    $color = $ls_color[$j];
    $color_info = taxonomy_term_load($color);
    $ls_size = $_POST['hd_size'][$color]; // LS SIZE
    $quantity = $_POST['quantity'][$color]; //LS QUANTITY
    $ls_fid = $_POST['image-id'][$color]; // LS FID
    
    // IMAGE
    $saved_files = array();
    $ls_image = $form_state['values']['sl_color'.$color]['image']; // LS IMAGE NEW
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
    $arr_image = array();
    if (in_array($color, $ls_old_color)) {
      for ($n=0; $n < count($ls_fid); $n++) {
        $file_info = file_load($ls_fid[$n]);
        $arr_image[] = array(
          'fid' => $file_info->fid,
          'filename' => $file_info->filename,
          'filesize' => $file_info->filesize,
          'uri' => $file_info->filename,
          'uid' => $file_info->uid,
        );
      }
    }
    for ($l=0; $l < count($saved_files); $l++) { 
      $arr_image[] = array(
        'fid' => $saved_files[$l]->fid,
        'filename' => $saved_files[$l]->filename,
        'filesize' => $saved_files[$l]->filesize,
        'uri' => $saved_files[$l]->uri,
        'uid' => $saved_files[$l]->uid,
      );
    }

    // LOOP SIZE
    for ($k=0; $k < count($ls_size) ; $k++) {
      // If size not null
      if ($ls_size[$k]) {
        $size_info = taxonomy_term_load($ls_size[$k]);
        // Update Product
        if (in_array($color, $ls_old_color)) {
          for ($i=0; $i < count($ls_pid); $i++) {
            $pid = $ls_pid[$i]['product_id'];
            $product = commerce_product_load($pid);
            $size_item = $product->field_type_size[LANGUAGE_NONE][0]['tid'];
            $color_item = $product->field_type_color[LANGUAGE_NONE][0]['tid'];
            if (in_array($ls_size[$k], $ls_old_size) && ($color_item == $color)) {
              if ($size_item == $ls_size[$k]) {
                $product->commerce_price[LANGUAGE_NONE][0]['amount'] = $price;
                $product->commerce_price[LANGUAGE_NONE][0]['currency_code'] = 'USD';
                
                if ($quantity[$k]) {
                  $product->commerce_stock[LANGUAGE_NONE][0]['value'] = $quantity[$k];
                } else {
                  $product->commerce_stock[LANGUAGE_NONE][0]['value'] = 0;
                }
                if (!empty($arr_image)) {
                  $product->field_product_images[LANGUAGE_NONE] = $arr_image;
                }
                commerce_product_save($product);
                $ls_new_pid[] = array('product_id' => $pid);
              }
            }
          }
          if (!in_array($ls_size[$k], $ls_old_size)) {
            $new_product = commerce_product_new('products');
            $new_product->uid = $user->uid;
            $new_product->status = 1;
            $new_product->title = $_POST['title'].' ('.$color_info->name.' '.$size_info->name.')';
            $new_product->sku = 'SKU'.rand();
            $new_product->title_field[LANGUAGE_NONE][0]['value'] = $_POST['title'].' ('.$color_info->name.' '.$size_info->name.')';
            $new_product->commerce_price[LANGUAGE_NONE][0]['amount'] = $price;
            $new_product->commerce_price[LANGUAGE_NONE][0]['currency_code'] = 'USD';
            $new_product->field_type_color[LANGUAGE_NONE][0]['tid'] = $color;
            $new_product->field_type_size[LANGUAGE_NONE][0]['tid'] = $ls_size[$k];
            if ($quantity[$k]) {
              $new_product->commerce_stock[LANGUAGE_NONE][0]['value'] = $quantity[$k];
            } else {
              $new_product->commerce_stock[LANGUAGE_NONE][0]['value'] = 0;
            }
            //Save Image for Product
            if (!empty($arr_image)) {
              $new_product->field_product_images[LANGUAGE_NONE] = $arr_image;
            }
            commerce_product_save($new_product);
            $ls_new_pid[] = array('product_id' => $new_product->product_id);
          }
        } else { // Create New Product
          $new_product = commerce_product_new('products');
          $new_product->uid = $user->uid;
          $new_product->status = 1;
          $new_product->title = $_POST['title'].' ('.$color_info->name.' '.$size_info->name.')';
          $new_product->sku = 'SKU'.rand();
          $new_product->title_field[LANGUAGE_NONE][0]['value'] = $_POST['title'].' ('.$color_info->name.' '.$size_info->name.')';
          $new_product->commerce_price[LANGUAGE_NONE][0]['amount'] = $price;
          $new_product->commerce_price[LANGUAGE_NONE][0]['currency_code'] = 'USD';
          $new_product->field_type_color[LANGUAGE_NONE][0]['tid'] = $color;
          $new_product->field_type_size[LANGUAGE_NONE][0]['tid'] = $ls_size[$k];
          
          if ($quantity[$k]) {
            $new_product->commerce_stock[LANGUAGE_NONE][0]['value'] = $quantity[$k];
          } else {
            $new_product->commerce_stock[LANGUAGE_NONE][0]['value'] = 0;
          }
          //Save Image for Product
          if (!empty($arr_image)) {
            $new_product->field_product_images[LANGUAGE_NONE] = $arr_image;
          }
          commerce_product_save($new_product);
          $ls_new_pid[] = array('product_id' => $new_product->product_id);
        }  
      }
    }
  }
  // SAVE PRODUCT
  $node->field_product_reference[LANGUAGE_NONE] = NULL;
  if (!empty($ls_new_pid)) {
    $node->field_product_reference[LANGUAGE_NONE] = $ls_new_pid;
  }
  node_save($node);
  drupal_set_message(t('Edit successful!'),'status');
  drupal_goto($base_url.'/node/'.$node->nid);
}
