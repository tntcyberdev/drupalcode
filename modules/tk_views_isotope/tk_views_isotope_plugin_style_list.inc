<?php

/**
 * Style plugin to render each item in a slideshow of an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class tk_views_isotope_plugin_style_list extends views_plugin_style {

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['width_item'] = array('default' => 320);
    $options['ul_class'] = array('default' => '');
    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // Add Class into List (ul tag)
    $form['ul_class'] = array(
      '#type' => 'textfield',
      '#title' => t('List class'),
      '#default_value' => $this->options['ul_class'],
    );

    // Add Width for each item content
    $form['width_item'] = array(
      '#type' => 'textfield',
      '#title' => t('Width Items'),
      '#default_value' => $this->options['width_item'],
      '#description' => t('Only enter numberic.')
    );
  }

  function options_validate(&$form, &$form_state) {
    $values = $form_state['values'];
    // Validate Width Item
    $width_item = $values['style_options']['width_item'];
    if (!is_numeric($width_item)) {
      form_error($form['width_item'], t('Enter numberic.'));
    }
  }
}
